#include <iostream>

#include "Game.h"

int main() {
  try {
    Game game;

    while (!game.isDone()) {
      game.handleInput();
      game.update();
      game.render();
      game.restartClock();
    }
  } catch (std::runtime_error &error) {
    std::cerr << error.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
