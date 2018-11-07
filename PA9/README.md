# PA9: Lighting

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
./BulletTutorial
```

### Run Instructions
After building the project, the executable can be ran.

## Ubuntu.cse.unr.edu
OpenGL 3.3 will run on the [ubuntu.cse.unr.edu](https://ubuntu.cse.unr.edu/) website. To do so follow the build instructions, but when running the Tutorial executable use this line to execute.
```bash
/usr/NX/scripts/vgl/vglrun ./BulletTutorial
```

## Keyboard/Mouse Input Guide
ESC - must be pressed to close the window (or right-click on the task bar and select close).

w - increase brightness

s - decrease brightness

Lshift - flip left flipper

Rshift - flip right flipper

SpaceBar - Toggle Lighting Mode (default is Vertex Based)



## Extra Credit

