const spawn = require("child_process").spawn;
const proc = spawn("./test.sh");

function readTemperature(io) {
  console.log("Start reading light intensity...");
  proc.stdout.on("data", (data) => {
    io.emit('lightData', data.toString());
  });

  proc.stderr.on("data", (data) => {
    console.error(data.toString());
    io.emit('lightData', "error");
  });

  proc.on("close", (code) => {
    if (code !== 0) {
      console.log(`Light intensity reading process exited with code ${code}`);
    }
  });
}

module.exports = readTemperature;
