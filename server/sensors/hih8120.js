const spawn = require("child_process").spawn;

function readData(io) {
  try {
    const proc = spawn("./bin/hih8120");
    // const proc = spawn("./bin/test.sh");
    console.log("Starting to read humidity and temperature...");

    proc.stdout.on("data", (data) => {
      console.log(data.toString())
      const humidity = getHumidityFromRead(data);
      const temperature = getTemperatureFromRead(data);
      io.emit("humidityData", humidity);
      io.emit("temperatureData", temperature);
    });

    proc.stderr.on("data", (data) => {
      console.error(data.toString());
      io.emit("humidityData", "error");
      io.emit("temperatureData", "error");
    });

    proc.on("close", (code) => {
      if (code !== 0) {
        console.log(`hih8120 process exited with code ${code}`);
      }
    });
  } catch (error) {
    console.error(error);
    io.emit("humidityData", "error");
    io.emit("temperatureData", "error");
  }
}

function getHumidityFromRead(data) {
  const results = data.toString().split("\n");
  const humidityValue = results[0].split(":")[1];
  return humidityValue;
}

function getTemperatureFromRead(data) {
  const results = data.toString().split("\n");
  const temperatureValue = results[1].split(":")[1];
  return temperatureValue;
}

module.exports = readData;
