#include <iostream>

#include "engine.h"


int main(int argc, char **argv)
{

  // Start an engine
  Engine *engine = new Engine("Jordy Kastanek and Trombley PA8", 960, 540);

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
