#!/bin/bash

clear
echo 'Started compiling'

# Compile goal.c
gcc src/goal.c -o bin/goal -lncurses -lm -lrt
if [ $? -ne 0 ]; then
    echo 'Error compiling goal.c'
    exit 1
else
    echo '  1 - goal.c compiled successfully'
fi

# Compile inspection.c
gcc src/inspection.c -o bin/inspection -lncurses -lm -lrt
if [ $? -ne 0 ]; then
    echo 'Error compiling inspection.c'
    exit 1
else
    echo '  2 - inspection.c compiled successfully'
fi

# # Compile drone.c
# gcc src/drone.c -o bin/drone -lncurses -lm -lrt
# if [ $? -ne 0 ]; then
#     echo 'Error compiling drone.c'
#     exit 1
# else
#     echo '  3 - drone.c compiled successfully'
# fi

# Compile input.c
gcc src/input.c -o bin/input -lncurses -lm -lrt
if [ $? -ne 0 ]; then
    echo 'Error compiling input.c'
    exit 1
else
    echo '  3 - input.c compiled successfully'
fi

# Compile force.c
gcc src/force.c -o bin/force -lncurses -lm -lrt
if [ $? -ne 0 ]; then
    echo 'Error compiling force.c'
    exit 1
else
    echo '  4 - force.c compiled successfully'
fi

# Compile obstacle.c
gcc src/obstacle.c -o bin/obstacle -lncurses -lm -lrt
if [ $? -ne 0 ]; then
    echo 'Error compiling obstacle.c'
    exit 1
else
    echo '  5 - obstacle.c compiled successfully'
fi

# Compile master.c
gcc src/master.c -o bin/master -lncurses -lm -lrt
if [ $? -ne 0 ]; then
    echo 'Error compiling master.c'
    exit 1
else
    echo '  6 - master.c compiled successfully'
fi

# Compile watchdog.c
gcc src/watchdog.c -o bin/watchdog -lncurses -lm -lrt
if [ $? -ne 0 ]; then
    echo 'Error compiling watchdog.c'
    exit 1
else
    echo '  7 - watchdog.c compiled successfully'
fi

# Countdown before running the code
for ((i=2 ; i>0 ; i--)); do
    clear
    echo "Running the code in $i seconds"
    sleep 1
done

clear
echo "Running the code ..."

# Run the master process
./bin/master



# // Mahnaz Mohammad_Karimi   ********** s6212087
# // Alireza Tajabadi_Farahani    ****** s6212483