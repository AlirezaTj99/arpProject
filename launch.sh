#!/bin/bash

# Countdown before running the serverSide
for ((i=2 ; i>0 ; i--)); do
    clear
    echo "Running the serverSide in $i seconds"
    sleep 1
done

# Check if 'serverSide' directory exists
if [ -d "serverSide" ]; then
    echo "Executing 'run.sh' in 'serverSide' directory..."
    # # Open new terminal and execute 'run.sh' in 'serverSide' directory
    # gnome-terminal -- ./serverSide/run.sh
    # Change directory to 'serverSide' and execute 'run.sh'
    (cd serverSide && ./run.sh &)
else
    echo "Error: 'serverSide' directory not found."
fi

# Countdown before running the clientSide
for ((i=5 ; i>0 ; i--)); do
    clear
    echo "Running the clientSide in $i seconds"
    sleep 1
done

# Check if 'clientSide' directory exists
if [ -d "clientSide" ]; then
    echo "Executing 'run.sh' in 'clientSide' directory..."
    # # Open new terminal and execute 'run.sh' in 'clientSide' directory
    # gnome-terminal -- ./clientSide/run.sh
    # Change directory to 'clientSide' and execute 'run.sh'
    (cd clientSide && ./run.sh &)
else
    echo "Error: 'clientSide' directory not found."
fi





# // Mahnaz Mohammad_Karimi   ********** s6212087
# // Alireza Tajabadi_Farahani    ****** s6212483