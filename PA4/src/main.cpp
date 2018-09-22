#include <iostream>
#include <string>

#include "engine.h"


int main(int argc, char **argv)
{
 //get fileName
 if(argc != 2)
 {
	std::cerr << "Improper Call, Use: ./Tutorial <filename of .obj>" << std::endl; 
	return 0;
 }
 string fileName = argv[1]; 
 if(fileName.find(".obj") == string::npos)
 {
	std::cerr << "File must be of type .obj" << std::endl; 
	return 0;
 }
 
  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("PA4 Nick Jordy", 800, 600);
  if(!engine->Initialize(fileName))
  {
    printf("The engine failed to start.\n");
    delete engine;
    engine = NULL;
    return 1;
  }
  engine->Run();
  delete engine;
  engine = NULL;
  return 0;
}
