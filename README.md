#NEVIL: Nurturing and EVolution of Intelligence and Learning [![Build Status](https://travis-ci.org/ou-real/nevil-base.svg?branch=master)](https://travis-ci.org/ou-real/nevil-base)
This the base project for light-switch based nurturing experiments. This project provides libraries and base classes for different experiments to be build upon.

This repository is meant to be forked and extended for different experiments.

##Usage
You can clone this repository by running:
```bash
git clone https://github.com/ou-real/nevil-base.git
```

###Compilation/Install
####Windows
* Someone please write this

####Unix
The binaries will be written to build folder.
```bash
cmake CMakeLists.txt <-DGUI=ON/OFF> # GUI is OFF by default
make
```

###Adding Experiments 

##Dependencies
* [GCC](https://gcc.gnu.org) or [clang](http://clang.llvm.org)
* [CMake](http://www.cmake.org)
* [ENKI](http://home.gna.org/enki/): Already included in the project.
* [QT4.8](http://qt-project.org/doc/qt-4.8/): Optional, to enable GUI.

###Install Dependencies

####Windows
* Someone please write this

####Unix
#####OS X
To install the required packages you need to have Xcode installed. For convenience, you also need to have either [HomeBrew](http://brew.sh) or [MacPorts](https://www.macports.org) installed.
To install the required packages run the following commands:
```bash
xcode-select --install
```
If you are using HomeBrew run the following commands:
```bash
brew install cmake
brew install qt
```
If you are using MacPorts run the following commands:
```bash
sudo port install cmake
sudo port install qt4-mac
```
#####Debian based Linux
To install the required packages run the following commands:
```bash
sudo apt-get install build-essential
sudo apt-get install cmake
sudo apt-get install git
sudo apt-get install libqt4-core libqt4-dev libqt4-gui qt4-dev-tools
sudo apt-get install freeglut3 freeglut3-dev #(Not sure these are necessary)
```
##Structure
    nevil-base
    ├── README.md                   - Description
    ├── .gitignore                  - Files ignore by Git
    ├── CMakeLists.txt              - Cmake file for this project
    ├── .travis.yml                 - Travis build and test file
    ├── include
    │    ├── Enki                   - The ENKI project code with some modification in CMakeFiles
    │    │    ├── enki              - Contains the ENKI library files and headers
    │    │    ├── viewer            - Contains the GUI library files and headers 
    │    │    └── ...
    │    ├── json                   - A library for reading JSON files.
    │    └── nevil                  - Contains Header files for the NEVIL project
    │         ├── arena             - Header files for simulation arena
    │         ├── gui               - Header files for GUI
    │         ├── parallel          - Header files for parallelization
    │         ├── robot-controller  - Header files for robot controllers (i.e ANN)
    │         ├── util              - Header files for utility modules
    │         └── *.hpp             - Other header files specific to the project
    └── src                         - Implementation files for the NEVIL project.
        ├── arena                   - Implementation files for simulation arena
        ├── gui                     - Implementation files for GUI
        ├── parallel                - Implementation files for parallelization
        ├── robot-controller        - Implementation files for robot controllers (i.e ANN)
        ├── util                    - Implementation files for utility modules
        └── *.cpp                   - Other implementation files specific to the project

##[Potential Bugs](https://github.com/ou-real/nevil-base/issues)

##[To do](https://github.com/ou-real/nevil-base/milestones)

##License
[MIT license](http://opensource.org/licenses/MIT)
