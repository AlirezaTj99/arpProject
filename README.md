# ARP-Drone-Assignment
This project is part of the *Advanced and Robot Programming* (ARP) assignment. It simulates a drone navigation system with various interconnected processes, each performing specific tasks. The project is structured to use the *ncurses library* for graphical interfaces, the socket and inter-process communication via FIFOs (named pipes). The organization of the repository is as follows: the serverSide and clientSide
- In serverSide we have:
    - The `src` folder contains the source code for all the processes including sMaster, Goal, Obstacle, and server.
    - The `include` folder holds the headers and data structures used within the ncurses framework and other functionalities. This folder provides necessary utilities for the project and generally does not require modification.
    - The `bin` folder is designated for the compiled executable files.
- In clientSide we have:
    - The `src` folder contains the source code for all the processes including Command (Input), Force, Master, Watchdog, client, and Inspection.
    - The `include` folder holds the headers and data structures used within the ncurses framework and other functionalities. This folder provides necessary utilities for the project and generally does not require modification.
    - The `bin` folder is designated for the compiled executable files.

## Processes Overview
- **Client Processor:** Handles the connection with server, it acts as a terminal for communication between other processors and obstacle and goal.
- **Input Processor:** Handles user inputs, renders the drone, court, obstacles, and goals on the screen.
- **Force Processor:** Calculates forces, velocities, and drone positions. Communicates with the Input, Goal, and Obstacle processors.
- **Master Processor:** Responsible for spawning and terminating other processors inside clientSide folder based on signals from the user or the Watchdog.
- **Watchdog Processor:** Monitors other processors, especially the Force processor. It terminates the network if no movement signal is received from the drone.
- **Inspection Processor:** Displays running and stopped processors. It remains open -for 10 seconds- post-termination of other processors to provide an overview of the process flow.
- **Goal Processor:** Generates goal coordinates and communicates them to relevant processors.
- **Obstacle Processor:** Manages the spawning of obstacles on the court.
- **Server Processor:** Handles the connection with client, it acts as a terminal for communication between obstacle and goal and other processors.
- **sMaster Processor:** Responsible for spawning and terminating other processors inside clientSide folder based on signals from the server.

## Gameplay and Mechanics
- The system will respawn obstacles and goals at new positions once all goals are reached.
- Use the Input window for gameplay. If you encounter any display issues (missing drone, court, or obstacles), resize the window manually (dragging the corners) to refresh the display.

## ncurses Installation
Install the ncurses library using:
```console
sudo apt-get install libncurses-dev


## ncurses installation
To install the ncurses library, simply open a terminal and type the following commands:
```console
sudo apt-get install libncurses-dev
```
or
```console
sudo apt-get install libncurses5-dev libncursesw5-dev
```

## Compiling and running the code
The processes depend on the ncurses library, which needs to be linked during the compilation step. Furthermore, the Inspection process also uses the mathematical library for some additional computation. Therefore the steps to compile are included in both **run.sh** files inside the serverSide folder and clientSide, after compiling, **assuming you have Konsole installed in your system** as per the professor's indications, you can **simply run the Master executables**, which will be responsible of spawning the GUIs, this step is also included in **run.sh** files; all you have to do is to simply run this code as followed in both pc's:
```console
./run.sh
```

The keys available for the user are:
```

                 speed up to sky
 
     up and left                 up and right
                  -------------
                  | 7 | 8 | 9 |
                  |---|---|---|
speed up to left  | 4 | 5 | 6 |  speed up to right
                  |---|---|---|
                  | 1 | 2 | 3 |
                  -------------
     down & left                 down & right
 
                speed up to ground

```

The key '5' is used to stop the drone and key 'Q' to terminate the master prosessor.

If you're drone stops for 25 seconds you will loose and the watchdog will close all the processors.

## Troubleshooting

Should you experience some weird behavior after launching the application simply try to resize the terminal window, it should solve the bug.


## Master processor pseudocode
```
FUNCTION main
    Initialize ncurses window
    Create and open FIFOs for communication

    WHILE TRUE
        Read user input
        Open and write to FIFO based on input
        Read from FIFOs to get drone and environment data
        Update the UI with the new data
        Sleep for a short duration
    END WHILE

    Cleanup and close ncurses window
END FUNCTION
```

## client processor pseudocode
```
FUNCTION main
    Initialize ncurses window
    Create and open SOCKET and FIFOs for communication

    WHILE TRUE
        Read user input
        write massage to server
        read the recieved data from server
        Open and write to FIFO based on recieved massage
    END WHILE

    Cleanup and close ncurses window
END FUNCTION
```

## Input processor pseudocode

```
FUNCTION main
    Initialize ncurses window
    Create and open FIFOs for communication

    WHILE TRUE
        Read user input
        Open and write to FIFO based on input
        Read from FIFOs to get drone and environment data
        Update the UI with the new data
        Sleep for a short duration
    END WHILE

    Cleanup and close ncurses window
END FUNCTION

```

## force processor pseudocode

```
FUNCTION main
    Create and open FIFOs for communication

    WHILE TRUE
        Read key signals and environment data from FIFOs
        Calculate forces and update drone's position and velocity
        Write updated drone data to FIFOs
        Sleep for a short duration
    END WHILE
END FUNCTION

```

## Watchdog processor pseudocode

```
FUNCTION main
    Create and open FIFOs for communication

    WHILE TRUE
        Read drone activity status from FIFO
        IF no activity for a threshold duration THEN
            Send termination signal to master processor
            Exit program
        END IF
        Sleep for a short duration
    END WHILE
END FUNCTION

```

## Inspection processor pseudocode

```
FUNCTION main
    Create and open FIFOs for communication

    WHILE TRUE
        Read PIDs of other processes from FIFO
        Check if each process is running
        Update the UI with process status
        Sleep for a short duration
    END WHILE
END FUNCTION

```

## sMaster processor pseudocode
```
FUNCTION main
    Initialize ncurses window
    Create and open FIFOs for communication

    WHILE TRUE
        Read user input
        Open and write to FIFO based on input
        Read from FIFOs to get drone and environment data
        Update the UI with the new data
        Sleep for a short duration
    END WHILE

    Cleanup and close ncurses window
END FUNCTION
```

## server processor pseudocode
```
FUNCTION main
    Initialize ncurses window
    Create and open FIFOs AND SOCKET for communication

    WHILE TRUE
        Read client massage
        Open and write to FIFO based on input
        Read from FIFOs to get obstacle and goals data
        write the recieved data to client
    END WHILE

    Cleanup and close ncurses window
END FUNCTION
```

## obstacle processor pseudocode

```
FUNCTION main
    Create and open FIFOs for communication

    WHILE TRUE
        IF all goals are reached THEN
            Generate new obstacle positions
        END IF
        Write obstacle positions to FIFOs
        Sleep for a short duration
    END WHILE
END FUNCTION

```

## goal processor pseudocode

```
FUNCTION main
    Create and open FIFOs for communication

    WHILE TRUE
        IF all goals are reached THEN
            Generate new goal positions
        END IF
        Write goal positions to FIFOs
        Sleep for a short duration
    END WHILE
END FUNCTION

```



// Mahnaz Mohammad_Karimi   ********** s6212087
// Alireza Tajabadi_Farahani    ****** s6212483