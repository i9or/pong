#include <SFML/Graphics.hpp>

#include "Game.h"

int main() {
  Game game;

  while (!game.isDone()) {
    game.handleInput();
    game.update();
    game.render();
    game.restartClock();
  }

  return EXIT_SUCCESS;
}
