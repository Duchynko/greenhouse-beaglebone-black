/**
 * Reads light intensity data from the ldr sensor using the provided 
 * binary. On every read, it emits data to all connected client sockets.
 * 
 * Author: Jakub Duchon
 * Date: 23.11.2020 
 */

const spawn = require("child_process").spawn;

function readData(io) {
  try {
    const proc = spawn("./bin/ldr");
    console.log("Starting to read light intensity...");

    proc.stdout.on("data", (data) => {
      io.emit("lightData", data.toString());
    });

    proc.stderr.on("data", (data) => {
      console.error(data.toString());
      io.emit("lightData", "error");
    });

    proc.on("close", (code) => {
      if (code !== 0) {
        console.log(`ldr process exited with code ${code}`);
      }
    });
  } catch (error) {
    console.error(error);
    io.emit("lightData", "error");
  }
}

module.exports = readData;
