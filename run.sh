clear
echo 'started compiling'

konsole  -e gcc src/court.c -o bin/court -lncurses -lm -lrt &&
echo '  1 - the court.c compiled successfully'
# sleep 1

konsole  -e gcc src/drone.c -o bin/drone -lncurses -lm -lrt &&
echo '  2 - the drone.c compiled successfully'
# sleep 1

konsole  -e gcc src/input.c -o bin/input -lncurses -lm -lrt &&
echo '  3 - the input.c compiled successfully'
# sleep 1

konsole  -e gcc src/master.c -o bin/master -lncurses -lm -lrt &&
echo '  4 - the src/master.c compiled successfully'
# sleep 1

konsole  -e gcc src/watchdog.c -o bin/watchdog -lncurses -lm -lrt &&
echo '  5 - the src/watchDog.c compiled successfully'
# sleep 1

for ((i=2 ; i>0 ; i--)); do
    clear
    echo "Running the code in $i seconds"
    sleep 1
done

clear

echo "Running the code ..."

konsole  -e ./bin/master