const http = require("http").createServer();
const io = require("socket.io", {transports: ['websocket']})(http);
const readHumidityAndTemperature = require("./sensors/hih8120");
const readLightIntensity = require('./sensors/light');
const { spawn, exec } = require('child_process')

const PORT = 5500
const HEATER_BIN = './bin/heater'
const HIH8120_BIN = './bin/hih8120'
const ldr_BIN = './bin/ldr'
const SG90_BIN = './bin/sg90'
const LEDs_BIN = './bin/pwmlight'

http.listen(PORT, () => {
  /**
   * Configure PIN moodes of P9_21 and P9_22 to pwm. These two PINs are 
   * used to adjust brightness on the LED and to manipulate the servo. 
   * 
   * P9_21 - Used to manipulate the SG90 servo
   * P9_22 - Used to adjust brightness on the LED strip
   */
  exec('config-pin P9_21 pwm')
  exec('config-pin P9_22 pwm')

  console.log("Server is listening on port", PORT);
});

io.on("connect", (socket) => {
  const now = new Date().toLocaleTimeString('en-GB')
  console.log(`[${now}] Socket ${socket.id} has connected.`);

  /**
   * On heatingOn and heatingOff events, execute the provided binary
   * which writes value to the underlying GPIO. After successfull write
   * sends an acknowledgment back to the client. 
   * 
   * The binary takes a numeric argument `value` in a range from 0 to 1.
   */
  socket.on('heatingOn', (ack) => {
    console.log("Turning heating on");
    const proc = spawn(HEATER_BIN, ['0'])
    proc.stdout.on("data", (_) => {
      ack('ok')
    })
  });

  socket.on('heatingOff', (ack) => {
    console.log("Turning heating off");
    const proc = spawn(HEATER_BIN, ['1'])
    proc.stdout.on("data", (_) => {
      ack('ok')
    })
  });

  
  /**
   * On windowOpen and windowClosed events, execute the provided binary
   * which writes value to the underlying GPIO. After successfull write
   * sends an acknowledgment back to the client.
   * 
   * The binary takes a numeric argument `angle` in a range from 0 to 180.
   */
  socket.on('windowOpen', (ack) => {
    const proc = spawn(SG90_BIN, ['0'])
    proc.stdout.on("data", (_) => {
      ack('ok')
    })
  });

  socket.on('windowClose', (ack) => {
    const proc = spawn(SG90_BIN, ['180'])
    proc.stdout.on("data", (_) => {
      ack('ok')
    })
  });

  /**
   * On brightnesSet event, execute the provided binary which writes value 
   * to the underlying GPIO.
   * 
   * The binary takes a numeric argument `brightness` in a range from 0 to 100.
   */
  socket.on('brightnesSet', (brightness) => {
    console.log("Set brightness to " + brightness);
    const proc = spawn(LEDs_BIN, [brightness])
    proc.stdout.on("data", (_) => {
      // ack('ok') Not supported in socket.io@2.x
    })
  });
});

readHumidityAndTemperature(io);
readLightIntensity(io);
