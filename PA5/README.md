# PA5: Assimp and Model Loading

# Team Members
Nick Jordy  
Alex Kastanek  
Mari Trombley  

# Dependencies, Building, and Running

## Dependency Instructions
For both of the operating systems to run this project installation of these three programs are required [GLEW](http://glew.sourceforge.net/), [GLM](http://glm.g-truc.net/0.9.7/index.html), and [SDL2](https://wiki.libsdl.org/Tutorials).

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
After building the project, the executable can be ran. The program requires a single command-line argument that is the name of the .obj it needs to load. The program will not accept no command-line arguments or more than one command-line argument. The location of this .obj file must be placed in the PA4/objects/OBJS directory. Any .mtl files associated with this .obj file must be placed in the PA4/objects/MTLS directory. For example, if you want to load an object called "dragon.obj" and a material file associated with that file called "dragon.mtl", you would place the "dragon.obj" file in the PA4/objects/OBJS directory, and you would place the "dragon.mtl" file in the PA4/objects/MTLS directory. Then, you would run the program using the command "./Tutorial dragon.obj" in the build directory you created. 

## Ubuntu.cse.unr.edu
OpenGL 3.3 will run on the [ubuntu.cse.unr.edu](https://ubuntu.cse.unr.edu/) website. To do so follow the build instructions, but when running the Tutorial executable use this line to execute.
```bash
/usr/NX/scripts/vgl/vglrun ./Tutorial objectfilename.obj
```

## Keyboard/Mouse Input Guide
ESC - must be pressed to close the window (or right-click on the task bar and select close).

## Extra Credit
This program implements the extra credit portion of the assignment. Please see "Run Instructions" on how to use the .mtl file associated with the .obj file.