/**
 * Reads humidity and temperature data from the hih8120 sensor, 
 * using the provided binary. On every read, it emits data to all 
 * connected client sockets. Data are emited to clients separately
 * for both humidity and temperature.
 * 
 * Author: Jakub Duchon
 * Date: 23.11.2020 
 */

const spawn = require("child_process").spawn;

function readData(io) {
  try {
    const proc = spawn("./bin/hih8120");
    console.log("Starting to read humidity and temperature...");

    proc.stdout.on("data", (data) => {
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

/**
 * Takes raw sensor output in bytes, and returns a humidity value as string. 
 * 
 * @param {any} data Bytes represntation of sensor output in the specific format
 * 
 * The sensor output format:
 * Humidity     (%): 45
 * Temperature (°C): 21
 */
function getHumidityFromRead(data) {
  const results = data.toString().split("\n");
  const humidityValue = results[0].split(":")[1];
  return humidityValue;
}

/**
 * Takes raw sensor output in bytes, and returns a temperature value as string. 
 * 
 * @param {any} data Bytes represntation of sensor output in the specific format
 * 
 * The sensor output format:
 * Humidity     (%): 45
 * Temperature (°C): 21
 */
function getTemperatureFromRead(data) {
  const results = data.toString().split("\n");
  const temperatureValue = results[1].split(":")[1];
  return temperatureValue;
}

module.exports = readData;
