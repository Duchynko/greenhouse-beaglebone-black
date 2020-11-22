const http = require("http").createServer();
const io = require("socket.io", {transports: ['websocket']})(http);
const readHumidityAndTemperature = require("./sensors/hih8120");
const readLightIntensity = require('./sensors/light');
const { spawn } = require('child_process')

const PORT = 5500

http.listen(PORT, () => {
  console.log("Server is listening on port", PORT);
});

io.on("connect", (socket) => {
  const currentTime = new Date().toLocaleTimeString('en-GB')
  console.log(`[${currentTime}] Socket ${socket.id} has connected.`);

  socket.on('heatingOn', (ack) => {
    console.log("Heating On");
    const proc = spawn('./bin/heater', ['1'])
    proc.stdout.on("data", (data) => {
      console.log(data.toString())
    })
    ack('ok')
  });

  socket.on('heatingOff', (ack) => {
    console.log("Heating Off");
    const proc = spawn('./bin/heater', ['0'])
    proc.stdout.on("data", (data) => {
      console.log(data.toString())
    })
    ack('ok')
  });

  socket.on('windowOpen', (ack) => {
    const proc = spawn('./bin/sg90', ['0'])
    proc.stdout.on("data", (data) => {
      console.log(data.toString())
    })
    ack('ok')
  });

  socket.on('windowClose', (ack) => {
    const proc = spawn('./bin/sg90', ['180'])
    proc.stdout.on("data", (data) => {
      console.log(data.toString())
    })
    ack('ok')
  });

  socket.on('brightnesSet', (brightness) => {
    console.log("Set brightness to " + brightness);
    const proc = spawn('./bin/pwmlight', [brightness])
    proc.stdout.on("data", (data) => {
      console.log(data.toString())
    })
  });
});

readHumidityAndTemperature(io);
readLightIntensity(io);
