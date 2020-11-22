while [ true ]
do
    RAND_LIGHT=$(shuf -i 300-3000 -n 1)
    echo $RAND_LIGHT
    sleep 10
done