#pragma once

#include <string>

class CLI {
 public:
  CLI(const int argc, const char* const argv[]);
  bool shouldQuit() const;
  int getReturnCode() const;

  const std::string& getAssetsDirPath() const;

 private:
  bool _quit = false;
  int _returnCode = 0;
  std::string _assetsDirPath;

  bool confirmFileExists(const char* const path);
  bool shouldShowHelp(const int argc, const char* const argv[]) const;
  void suggestHelp() const;
  void showHelp() const;
};
