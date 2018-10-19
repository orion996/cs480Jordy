# PA7: Solar System

# Team Members
Nick Jordy  
Alex Kastanek  
Mari Trombley  

Use Alex's Repository for Grading, Located At: https://github.com/AlexKastanek/CS480Kastanek

# Dependencies, Building, and Running

## Dependency Instructions
For both of the operating systems to run this project installation of these five programs are required [GLEW](http://glew.sourceforge.net/), [GLM](http://glm.g-truc.net/0.9.7/index.html), [SDL2](https://wiki.libsdl.org/Tutorials), [assimp](http://www.assimp.org/index.php), and [ImageMagick++](http://www.imagemagick.org/Magick++/).  

To install assimp, the linux terminal command is 
```
sudo apt-get update
sudo apt-get install libassimp-dev
``` 

To install ImageMagick++, the linux terminal command is
```
sudo apt-get update
sudo apt-get install libmagick++-dev
```

This project uses OpenGL 3.3. Some computers, such as virtual machines in the ECC, can not run this version. In in order to run OpenGL 2.7 follow the instructions at [Using OpenGL 2.7](https://github.com/HPC-Vis/computer-graphics/wiki/Using-OpenGL-2.7)

## Building and Running
To build this project there are two options. One is to use CMake which makes including new libraries easier, and handles new files added automatically to the src and include directory. CMake is a small new learning curve but makes things easier in the future.
The second option is to use the provided Makefile which is used as usual.

Running the make in a separate directory will allow easy cleanup of the build data, and an easy way to prevent unnecessary data to be added to the git repository.  

### CMake Instructions
The building of the project is done using CMake, installation with apt-get or brew may be necessary. Later use with CMake and Shader files will be require the copy of a directory where those files are stored (ex. shaders). To do this in the ```add_custom_target``` function place 
```cmake
COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/shaders/ ${CMAKE_CURRENT_BINARY_DIR}/shaders
```

```bash
mkdir build
cd build
cmake ..
make
./SolarSystem
```

### Run Instructions
After building the project, the executable can be ran. This program requires a config file to run. The file must be placed in PA7/assets and must be named "planetData.txt"

#### Format of planetData.txt
all items in the config file must be formatted specifically for the program to run. 

The first line must read: Sun {scale of sun copared to earth}

The next 9 lines must be formatted as such: 
Name moonsNum orbitRadius(per 35mil miles) rotSpeed(in days) orbitSpeed(in years) planetScale(scale to earth)

These formatting rules are also described within "planetData.txt" included with the program

## Ubuntu.cse.unr.edu
OpenGL 3.3 will run on the [ubuntu.cse.unr.edu](https://ubuntu.cse.unr.edu/) website. To do so follow the build instructions, but when running the Tutorial executable use this line to execute.
```bash
/usr/NX/scripts/vgl/vglrun ./SolarSystem
```

## Keyboard/Mouse Input Guide
ESC - must be pressed to close the window (or right-click on the task bar and select close).

M - toggle camera mode (1. Focus Mode, 2. Free Mode, 3. Top-Down/Overview Mode)  
**Default is Focus Mode  

If in Focus Mode:  
F - Change currently focused planet  
W - Zoom in on currently focused planet  
S - Zoom out from currently foucsed planet  
UpArrow - tilt camera up  
DownArrow - tilt camera down  
  
If in Free Mode:  
W - Move forward  
S - Move back  
A - Move left  
D - Move right  
UpArrow - Look up (increase pitch)  
DownArrow - Look down (decrease pitch)  
LeftArrow - Look left (decrease yaw)  
RightArrow - Look right (increase yaw)  

If in Top-Down/Overview Mode:  
W - Zoom in  
S - Zoom out  

'+' - Increase simulation speed (no need to hold shift)
'-' - Decrease simulation speed

## Extra Credit
This program implements the extra credit portion of the assignment:  
-This program uses a config file called "planetData.txt" located in the assets folder to determine scales for the planets  
-This program allows the user to increase/decrease the simulation speed  
-This program has rings for all planets that have rings (Jupiter, Saturn, Uranus, and Neptune)  

Other items that could be considered for extra credit:  
-Advanced camera controls  
-Correct amount of satellites for each planet  
-Uranus and its rings are on their side  
