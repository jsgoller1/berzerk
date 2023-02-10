#include <iostream>

#include "CLI.hh"
#include "Game.hh"
#include "InputHandler.hh"
#include "Screen.hh"
#include "Time.hh"

int main(int argc, char* argv[]) {
  CLI args(argc, argv);
  if (args.shouldQuit()) {
    return args.getReturnCode();
  }
  InputHandler inputHandler = InputHandler();
  Screen screen = Screen(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
  Timer timer = Timer();

  Game game = Game(args, screen, inputHandler, timer);
  game.run();
}
