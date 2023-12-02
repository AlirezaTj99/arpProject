clear
echo 'started compiling'

konsole  -e gcc src/inspection_console.c -o bin/inspection -lncurses -lm -lrt &&
# konsole  -e gcc src/inspection_console.c -lncurses -lm -o bin/inspection &&
# clear
echo '  1 - the inspection_console.c compiled successfully'
sleep 2

konsole  -e gcc src/master.c -o bin/master -lncurses -lm -lrt &&
#konsole  -e gcc src/master.c -o bin/master &&
# clear
echo '  2 - the src/master.c compiled successfully'
sleep 2

konsole  -e gcc src/watchDog.c -o bin/watchdog -lncurses -lm -lrt &&
# konsole  -e gcc src/watchDog.c -o bin/watchdog &&
# clear
echo '  3 - the src/watchDog.c compiled successfully'
sleep 2

for ((i=2 ; i>0 ; i--)); do
    clear
    echo "Running the code in $i seconds"
    sleep 1
done

clear

echo "Running the code ..."

konsole  -e ./bin/master
