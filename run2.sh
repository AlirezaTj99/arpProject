#!/bin/bash
clear
echo 'Started compiling'

# Array of source files to compile
source_files=("court.c" "drone.c" "input.c" "force.c" "obstacle.c" "master.c" "watchdog.c")

# Compile all source files
for source_file in "${source_files[@]}"; do
    if gcc "src/$source_file" -o "bin/${source_file%.c}" -lncurses -lm -lrt; then
        echo "  Successfully compiled $source_file"
    else
        echo "  Error compiling $source_file"
        exit 1
    fi
done

sleep 1

# Countdown
for ((i=5; i>0; i--)); do
    clear
    echo "Running the code in $i seconds"
    sleep 1
done

clear

echo "Running the code ..."

# Run the master program
./bin/master