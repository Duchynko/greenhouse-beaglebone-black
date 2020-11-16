const http = require("http").createServer();
const io = require("socket.io")(http);
const readHumidityAndTemperature = require("./sensors/hih8120");

const PORT = 5500

http.listen(PORT, () => {
  console.log("Server is listening on port", PORT);
});

io.on("connect", (socket) => {
  const currentTime = new Date().toLocaleTimeString('en-GB')
  console.log(`[${currentTime}] Socket ${socket.id} has connected.`);

  socket.on('heatingOn', (ack) => {
    console.log("Socket - Heating On");
    ack('ok')
  });

  socket.on('heatingOff', (ack) => {
    console.log("Socket - Heating Off");
    ack('ok')
  });
});

readHumidityAndTemperature(io);
