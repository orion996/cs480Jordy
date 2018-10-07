# PA6: Assimp and Texture Loading

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
./Tutorial objectfilename.obj
```

### Makefile Instructions 
The makefile works as expected and must be updated with new files added in.

```bash
mkdir build
cd build
cp ../makefile .
make
./Tutorial objectfilename.obj
```

### Run Instructions
After building the project, the executable can be ran. The program requires a single command-line argument that is the name of the .obj it needs to load. The program will not accept no command-line arguments or more than one command-line argument. The location of this .obj file must be placed in the PA5/assets directory along with .mtl files and image files associated with the .obj file. For this project to load, it is required that .mtl files and image files are used and place in this directory. For example, if you want to load an object called "dragon.obj" and a material file associated with that file called "dragon.mtl" which depends on an image file "dragon.jpg", you would place all of these files in the PA5/assets directory. Then, you would run the program using the command "./Tutorial dragon.obj" in the build directory you created. 

## Ubuntu.cse.unr.edu
OpenGL 3.3 will run on the [ubuntu.cse.unr.edu](https://ubuntu.cse.unr.edu/) website. To do so follow the build instructions, but when running the Tutorial executable use this line to execute.
```bash
/usr/NX/scripts/vgl/vglrun ./Tutorial objectfilename.obj
```

## Keyboard/Mouse Input Guide
ESC - must be pressed to close the window (or right-click on the task bar and select close).

## Extra Credit
This program implements the extra credit portion of the assignment. Please see "Run Instructions" on how to use the .mtl file associated with the .obj file.
