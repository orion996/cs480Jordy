#include <iostream>

#include "engine.h"


int main(int argc, char **argv)
{
  // Check for valid number of command line arguments (must be 1 for PA4)
//   if (argc != 2)
//   {
//     cout << "ERROR: Invalid number of command line arguments. "
//          << "Did you specify a single .obj file that is contained in "
//          << "the assets directory?" << endl;
//     return 1;
//   }

  // Start an engine
  Engine *engine = new Engine("Jordy Kastanek and Trombley PA7", 1600, 900);

//   // Get the object file name and send to the engine
//   string objectFilename = argv[1];
//   cout  << "using object file: " << objectFilename << endl;
//   engine->SetObjectFilename(objectFilename);

  if(!engine->Initialize())
  {
    printf("The engine failed to start.\n");
    delete engine;
    engine = NULL;
    return 1;
  }

  // Run the engine and cleanup after
  engine->Run();
  delete engine;
  engine = NULL;
  return 0;
}
