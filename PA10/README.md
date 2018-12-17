# PA10: Pinball

# Team Members
Nick Jordy  
Alex Kastanek  
Mari Trombley  

Use Alex's Repository for Grading, Located At: https://github.com/AlexKastanek/CS480Kastanek

# Dependencies, Building, and Running

## Dependency Instructions
For both of the operating systems to run this project installation of these five programs are required [GLEW](http://glew.sourceforge.net/), [GLM](http://glm.g-truc.net/0.9.7/index.html), [SDL2](https://wiki.libsdl.org/Tutorials), [assimp](http://www.assimp.org/index.php), [ImageMagick++](http://www.imagemagick.org/Magick++/), and [Bullet](https://pybullet.org/Bullet/BulletFull/index.html)

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

To install Bullet, the linux terminal command is
```
sudo apt-get update
sudo apt-get install libbullet-dev
```

This project uses OpenGL 3.3. Some computers, such as virtual machines in the ECC, can not run this version. In in order to run OpenGL 2.7 follow the instructions at [Using OpenGL 2.7](https://github.com/HPC-Vis/computer-graphics/wiki/Using-OpenGL-2.7)

## Building and Running
To build this project we use CMake which makes including new libraries easier, and handles new files added automatically to the src and include directory. CMake is a small new learning curve but makes things easier in the future.

To install Cmake, the linux terminal command is
```
sudo apt-get update
sudo apt-get install cmake
```

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
./Pinball
```

### Run Instructions
After building the project, the executable can be ran.

## Ubuntu.cse.unr.edu
OpenGL 3.3 will run on the [ubuntu.cse.unr.edu](https://ubuntu.cse.unr.edu/) website. To do so follow the build instructions, but when running the Tutorial executable use this line to execute.
```bash
/usr/NX/scripts/vgl/vglrun ./Pinball
```

## Keyboard/Mouse Input Guide
ESC - must be pressed to close the window (or right-click on the task bar and select close).  

TAB - change selected light  

1 - decrease specular brightness of board with selected light  
2 - increase specular brightness of board with selected light  

3 - decrease specular brightness of ball with selected light  
4 - increase specular brightness of ball with selected light  

5 - decrease specular brightness of flippers with selected light  
6 - increase specular brightness of flippers with selected light  

7 - decrease specular brightness of cylinder obstacle with selected light  
8 - increase specular brightness of cylinder obstacle with selected light  

9 - decrease specular brightness of plunger with selected light  
0 - increase specular brightness of plunger with selected light  

'-' - decrease ambient brightness of selected light  
'=' - increase ambient brightness of selected light  

‘]’ - increase diffuse brightness of selected light  
‘[‘ - decrease diffuse brightness of selected light  

'.' - increase spotlight angle (radius) of the spotlight following the ball  
',' - decrease spotlight angle (radius) of the spotlight following the ball  

M - change camera mode  

W - move camera forward  
A - move camera to the left  
S - move camera back  
D - move camera to the right  
Up Arrow - if in game mode, move up. If in free mode, tilt camera up  
Down Arrow - if in game mode, move down. If in free mode, tilt camera down  
Left Arrow - if in free mode, tilt camera left  
Right Arrow - if in free mode, tilt camera right  

Lshift - flip left flipper  
Rshift - flip right flipper  
Enter - use the plunger (hold to pull, let go to release)  

SpaceBar - Toggle Lighting Mode (default is Vertex Based)  

## Extra Credit
Rubric Defined Extra Credit:  
This program allows the user to use varying plunger speeds based on how long the key is held  
This program has a spotlight on the ball with radius and intensity adjustments  
This program keeps track of the top 10 scores  
This program has bumpers that bounce but they do not light up.  

Considerations:  
This program has the ability for the user to use a free camera  
This program uses custom fonts  
This program has an advanced game over menu system  
This program's gui is repositioned with window size  
This program has a leaderboard system that prompts the user for a name before playing  
This program uses a trigger system that allows the ball to go back into the launch area and be constrained to one axis while in the launch area  