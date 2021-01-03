//------------------------------------------------------------------------------
// main.cpp
//------------------------------------------------------------------------------

#include <iostream>
#include <stdlib.h>
#include "Interface.hpp"
#include "Game.hpp"

namespace Oop
{
  static constexpr int RETURN_OK = 0;
  static constexpr int RETURN_ERROR_ALLOC = -1;
  static constexpr int RETURN_ERROR_ARGUMENT = -2;
  static constexpr int RETURN_ERROR_BAD_CONFIG = -3;
}

//------------------------------------------------------------------------------
// main function
// entry point for execution
// entry point for execution
// @param argc argument count
// @param **argv argument values
// @return return value for the OS
//------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  // check if argument count is valid
  if (argc != 2)
  {
		std::cout << Oop::Interface::ERROR_WRONG_ARGUMENTS << std::endl;
    return Oop::RETURN_ERROR_ARGUMENT;
  }

  // create game and interface and start the game
  try
  {
    Oop::Interface io;
    Oop::Game game(io);


    if (!game.loadConfig(std::string(argv[1])))
    {
      return Oop::RETURN_ERROR_BAD_CONFIG;
    }
    game.run();
  }
  catch (std::bad_alloc &e)
  {
    std::cout << "[ERROR] " << Oop::Interface::ERROR_BAD_ALLOC << std::endl;
    return Oop::RETURN_ERROR_ALLOC;
  }
  return Oop::RETURN_OK;
}
