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

# Compile obstacle.c
gcc src/obstacle.c -o bin/obstacle -lncurses -lm -lrt
if [ $? -ne 0 ]; then
    echo 'Error compiling obstacle.c'
    exit 1
else
    echo '  2 - obstacle.c compiled successfully'
fi

# Compile client.c
gcc src/client.c -o bin/client -lncurses -lm -lrt
if [ $? -ne 0 ]; then
    echo 'Error compiling client.c'
    exit 1
else
    echo '  3 - client.c compiled successfully'
fi

# Compile Tclient.c
gcc src/Tclient.c -o bin/Tclient -lncurses -lm -lrt
if [ $? -ne 0 ]; then
    echo 'Error compiling Tclient.c'
    exit 1
else
    echo '  3 - Tclient.c compiled successfully'
fi

# Compile sMaster.c
gcc src/sMaster.c -o bin/sMaster -lncurses -lm -lrt
if [ $? -ne 0 ]; then
    echo 'Error compiling sMaster.c'
    exit 1
else
    echo '  4 - sMaster.c compiled successfully'
fi

# # Compile sWatchdog.c
# gcc src/sWatchdog.c -o bin/sWatchdog -lncurses -lm -lrt
# if [ $? -ne 0 ]; then
#     echo 'Error compiling sWatchdog.c'
#     exit 1
# else
#     echo '  5 - sWatchdog.c compiled successfully'
# fi

# # Countdown before running the code
# for ((i=2 ; i>0 ; i--)); do
#     clear
#     echo "Running the code in $i seconds"
#     sleep 1
# done

clear
echo "Running the code ..."

# Run the sMaster process
./bin/sMaster




# # Compile server.c
# gcc src/server.c -o bin/server -lncurses -lm -lrt
# if [ $? -ne 0 ]; then
#     echo 'Error compiling server.c'
#     exit 1
# else
#     echo '  7 - server.c compiled successfully'
# fi
# ./bin/server 12345


# # Compile client.c
# gcc src/client.c -o bin/client -lncurses -lm -lrt
# if [ $? -ne 0 ]; then
#     echo 'Error compiling client.c'
#     exit 1
# else
#     echo '  7 - client.c compiled successfully'
# fi
# ./bin/client localhost 12345


# ./bin/obstacle




# // Mahnaz Mohammad_Karimi   ********** s6212087
# // Alireza Tajabadi_Farahani    ****** s6212483