while [ true ]
do
    RAND_HUMIDITY=$(shuf -i 0-35 -n 1)
    RAND_TEMPERATURE=$(shuf -i 0-35 -n 1)
    echo "Humidity (%): ${RAND_HUMIDITY}\n Temperature (°C): ${RAND_TEMPERATURE}"
    sleep 10
done