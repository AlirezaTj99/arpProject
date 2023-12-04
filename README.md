# ARP-Drone-Assignment_1
Base project structure for the first *Advanced and Robot Programming* (ARP) assignment.
The project provides the basic functionalities for the **Command** and **Inspection processes**, both of which are implemented through the *ncurses library* as simple GUIs. In particular, the repository is organized as follows:
- The `src` folder contains the source code for the Command, Inspection and Master processes.
- The `include` folder contains all the data structures and methods used within the ncurses framework to build the two GUIs. Unless you want to expand the graphical capabilities of the UIs (which requires understanding how ncurses works), you can ignore the content of this folder, as it already provides you with all the necessary functionalities.
- The `bin` folder is where the executable files are expected to be after compilation

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
The processes depend on the ncurses library, which needs to be linked during the compilation step. Furthermore, the Inspection process also uses the mathematical library for some additional computation. Therefore the steps to compile are included in **run.sh** file, after compiling, **assuming you have Konsole installed in your system** as per the professor's indications, you can **simply run the Master executable**, which will be responsible of spawning the two GUIs this step is also included in **run.sh** file; all you have to do is to simply run this code as followed:
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

## Troubleshooting

Should you experience some weird behavior after launching the application simply try to resize the terminal window, it should solve the bug.
