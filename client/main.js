const io = require('socket.io-client');
const socket = io.connect('http://192.168.7.2:5500') 
console.log(socket)

const heatingOnButton = document.getElementById('heatingOn')
const heatingOffButton = document.getElementById('heatingOff')
const temperatureField = document.getElementById('temperatureValue')
const humidityField = document.getElementById('humidityValue')
const logConsole = document.getElementById('logOutput')
const heatingStateField = document.getElementById('heatingState')

heatingOnButton.onclick = (ev) => {
    socket.emit('heatingOn', (ack) => {
        if (ack === 'ok') {
            heatingStateField.innerHTML = 'On'
            writeLog(logConsole, `Heating turned on`)
        } else {
            writeLog(logConsole, `Error while turning on heating`)
        }
    })
}

heatingOffButton.onclick = (ev) => {
    socket.emit('heatingOff', (ack) => {
        if (ack === 'ok') {
            heatingStateField.innerHTML = 'Off'
            writeLog(logConsole, `Heating turned off`)
        } else {
            writeLog(logConsole, `Error while turning off heating`)
        }
    })
}

socket.on('temperatureData', (data) => {
    writeLog(logConsole, `Received temperature read - ${data}`)
    console.log()
    temperatureField.innerHTML = `${data.trim()}°C`
})

socket.on('humidityData', (data) => {
    writeLog(logConsole, `Received humidity read - ${data}`)
    humidityField.innerHTML = `${data.trim()}%`
})

function writeLog(logConsole, message) {
    const timesteamp = new Date().toLocaleString('en-GB')
    const log = `[${timesteamp}] ${message}`
    logConsole.innerHTML = log + '<br>' + logConsole.innerHTML
}