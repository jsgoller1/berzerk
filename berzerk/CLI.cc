#include "CLI.hh"

#include <iostream>

#include "Configs.hh"
#include "SDL2/SDL.h"

CLI::CLI(const int argc, const char* const argv[]) {
  if (argc != 2) {
    this->suggestHelp();
    this->_returnCode = -1;
    this->_quit = true;
    return;
  }
  if (shouldShowHelp(argc, argv)) {
    this->showHelp();
    this->_returnCode = 0;
    this->_quit = true;
    return;
  }

  this->_assetsDirPath = std::string(argv[1]);
  if (not confirmFileExists(argv[1])) {
    std::cout << "Error, quitting! Could not find assets directory at " << this->_assetsDirPath << std::endl;
    this->_returnCode = -1;
    this->_quit = true;
  }
}

int CLI::getReturnCode() const { return this->_returnCode; }

bool CLI::shouldQuit() const { return this->_quit; }

const std::string& CLI::getAssetsDirPath() const { return this->_assetsDirPath; }

bool CLI::confirmFileExists(const char* const path) {
  // TODO: Is there any other way to do a platform-independent stat? SDL doesn't seem to have one.
  // TODO: This is not platform independent and will break on non-POSIX systems; we can use Boost for
  // portable FS operations
  bool valid = true;
  SDL_RWops* ops = SDL_RWFromFile(path, "r");
  if (ops == nullptr) {
    std::cout << "berzerk: cannot find " << std::string(path) << std::endl;
    valid = false;
  }
  SDL_RWclose(ops);
  return valid;
}

bool CLI::shouldShowHelp(const int argc, const char* const argv[]) const {
  std::string argstring;
  for (int i = 0; i < argc; i++) {
    argstring = std::string(argv[i]);
    if (argstring == "-h" || argstring == "--help") {
      return true;
    }
  }
  return false;
}

void CLI::showHelp() const {
  std::cout << "Usage: berzerk <path to assets directory> " << std::endl;
  std::cout << "      --help     display this help and exit" << std::endl;
}

void CLI::suggestHelp() const { std::cout << "Try 'berzerk --help' for more information." << std::endl; }
