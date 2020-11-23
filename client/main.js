const io = require('socket.io-client');
const socket = io.connect('http://192.168.7.2:5500', {transports: ['websocket']}) 

const heatingOnButton = document.getElementById('heatingOn')
const heatingOffButton = document.getElementById('heatingOff')
const heatingStateField = document.getElementById('heatingState')
const windowOpenButton = document.getElementById('windowOpen')
const windowCloseButton = document.getElementById('windowClose')
const windowStateField = document.getElementById('windowState')
const ledBritghtnessSetButton = document.getElementById('ledBrightnessSet')
const ledBrightnessInputField = document.getElementById('ledBrightnessInput')
const ledBrightnessStateField = document.getElementById('ledBrightnessState')
const temperatureField = document.getElementById('temperatureValue')
const humidityField = document.getElementById('humidityValue')
const lightIntensityField = document.getElementById('lightIntensity')
const logConsole = document.getElementById('logOutput')

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

windowOpenButton.onclick = (ev) => {
    socket.emit('windowOpen', (ack) => {
        if (ack === 'ok') {
            windowStateField.innerHTML = 'Open'
            writeLog(logConsole, `Window opened`)
        } else {
            writeLog(logConsole, `Error while opening the window`)
        }
    })
}

windowCloseButton.onclick = (ev) => {
    socket.emit('windowClose', (ack) => {
        if (ack === 'ok') {
            windowStateField.innerHTML = 'Closed'
            writeLog(logConsole, `Window closed`)
        } else {
            writeLog(logConsole, `Error while closing the window`)
        }
    })
}

ledBritghtnessSetButton.onclick = (ev) => {
    const newBrightness = ledBrightnessInputField.value
    socket.emit('brightnesSet', newBrightness, (ack) => {
        // if (ack === 'ok') { -> Sending data + ack doesn't work in version 2.x 
        ledBrightnessStateField.innerHTML = newBrightness + '%'
        writeLog(logConsole, `LED's brightness set to ${newBrightness}%.`)
        // } else {
        //     writeLog(logConsole, `Error while changing the LED's brightness`)
        // }
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

socket.on('lightData', (data) => {
    writeLog(logConsole, `Received light intensity read - ${data}`)
    lightIntensityField.innerHTML = data.trim()
})

function writeLog(logConsole, message) {
    const timesteamp = new Date().toLocaleString('en-GB')
    const log = `[${timesteamp}] ${message}`
    logConsole.innerHTML = log + '<br>' + logConsole.innerHTML
}