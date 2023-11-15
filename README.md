# Aurum
[![LICENSE](https://img.shields.io/github/license/GinOwO/Aurum?color=blue)](LICENSE) ![Language](https://img.shields.io/badge/Language-C%2B%2B-brightgreen) ![Qt](https://img.shields.io/badge/Qt-6.5.0-brightgreen) ![GitHub csize](https://img.shields.io/github/languages/code-size/GinOwO/Aurum) [![Build Linux](https://github.com/GinOwO/Aurum/actions/workflows/c-cpp-build-linux.yaml/badge.svg?event=push)](https://github.com/GinOwO/Aurum/actions/workflows/c-cpp-build-linux.yaml) [![Build Windows](https://github.com/GinOwO/Aurum/actions/workflows/c-cpp-build-windows.yaml/badge.svg?event=push)](https://github.com/GinOwO/Aurum/actions/workflows/c-cpp-build-windows.yaml)

## Description
Aurum is a GUI application built with the Qt framework. It is a visualizer for various scheduling algorithms used in operating systems. It is built with the intention of being used as a teaching tool. The application provides a visual representation of the algorithms. The algorithms supported are:
1. First Come First Serve (FCFS)
2. Shortest Remaining Task First (SRTF)
3. Longest Remaining Task First (LRTF)
4. Round Robin (RR)
5. Priority Scheduling (PS)
6. MultiLevel Feedback Queue (MLFQ)

The implementation of the scheduler is on a tick based system. Each click on next moves 1 tick forward in time. What this means is that if say a process terminates before the end of the tick, it will still be shown as running for the entire tick and context switching will only happen at the end of the tick.

## Downloading

To use the pre-built binaries follow the steps below

### Linux

Download `Aurum_Linux_x86_64.tar.gz` from releases and extract the contents to a folder. Then run `Aurum-*.AppImage`

### Windows

Download `Aurum_Windows_x86_64.zip` from releases and extract the contents to a folder. Then run `Aurum.exe`

## Building From Source

### Prerequisites

To build Aurum, you require the following on your system:

- C++20 or above
- Qt framework 6.5.0+
- Qt Creator Community 10.0.0+
- (Optional: Linux only) AppImage-Builder

### Cloning 

Open a command line in your desired folder, clone the repo with the following command
```
git clone https://github.com/GinOwO/Aurum.git
```

## Building

### Windows
1. Open Qt Creator and load the project.
2. Switch to release and then build the project.
3. Copy the release exe from the build folder to your desired folder.
4. Open a command line in your bin folder in the Qt installation, ex: `"D:\Qt\6.5.*\mingw_64\bin"`
5. Use the `set PATH=<path_to_qt>;%PATH%` to use the Qt DLLs, ex:`set PATH=D:\Qt\Tools\mingw1120_64\bin;%PATH%`
6. Now run the `windeployqt6 "<path_to_exe>"` command to copy necessary DLLs to the exe folder, ex: `windeployqt6 "D:\Aurum\Aurum.exe"`

### Linux
1. Open Qt Creator and load the project.
2. Switch to release and then build the project.
3. Copy the release build from the build folder to your desired folder. Make the directory AppDir/usr/bin and copy the release build to it.
4. Open a terminal in the folder and run `appimage-builder --generate && appimage-builder` to generate the AppImage.

## Usage
1. Launch Aurum.
2. Enter the path to/use browse for finding the file containing the list of processes.
3. Select the undo/redo limit. (Optional, note that this feature is experimental and may cause crashes, recommended to keep it at 0)
4. Select the algorithm you want to visualize.
5. Click Ok.
6. Two windows will open, one for the visualization(MainWindow) and one for viewing the instructions in a process(Process View).
7. Click on next to move to the next tick. Click on Last to move to the last tick/end of visualization.

## Notes
- The input file should be a text file with the following format:
```
Input file must be of form:
STR_PROCESS "<string Name>" <int arrivalTime> <priority>
OP1 <resource taken>
OP2 <resource taken>
OP3 <resource taken>
..
..
..
OPn <resource taken>
END_PROCESS
PROCESS "<string Name>" <int arrivalTime> <priority>
OP1 <resource taken>
OP2 <resource taken>
..
..
..
etc
```
where
```
OPs         Resource Type(must be integer)
CPU         Cycles
IO          Time(in seconds)
WAIT        Time(in seconds)
PRIORITY    Optional, lower is higher priority
```

- The currently executing tab will show details like ticks elapsed, current process, etc.
- The Gantt chart tab will show the Gantt chart state at the current tick.
- The queue view tab will show in which queue the processes are in at the current tick.
- The log tab will show the log of things done so far.

- By default
    - 1 tick = 100 cycles, meaning 100 cycles will be executed in 1 tick.
    - 1 tick = 1 second, meaning 1 second will pass in 1 tick.
    This can be changed in `main.cpp` by passing the desired values to the `Scheduler` constructor.

- The visualization is not real time, it is a simulation. This means that the visualization will not be accurate to real life. The visualization is meant to be used as a teaching tool and not as a real world scheduler.

## Contributing
Please read [CONTRIBUTING.md](./.github/CONTRIBUTING.md) for details on contributing to this project.

## License

This project is licensed under [The Unlicense](LICENSE).
