#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>

int main() {
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  while (true) {
    std::cout << "$ ";

    std::string command;
    std::getline(std::cin, command);

    if (command == "exit 0") {
      break;
    }

    if (command.rfind("echo ", 0) == 0) {
      std::cout << command.substr(5) << "\n";
    }

    else if (command.rfind("type ", 0) == 0) {
      std::string cmd = command.substr(5);

      if (cmd == "echo" || cmd == "exit" || cmd == "type") {
        std::cout << cmd << " is a shell builtin\n";
      } else {
        std::string pathvar = std::getenv("PATH");
        std::istringstream path_stream(pathvar);
        std::string dir;
        bool found = false;

        while (std::getline(path_stream, dir, ':')) {
          std::string filepath = dir + "/" + cmd;

          if (access(filepath.c_str(), X_OK) == 0) {
            std::cout << cmd << " is " << filepath << "\n";
            found = true;
            break;
          }
        }

        if (!found) {
          std::cout << cmd << ": not found\n";
        }
      }
    }

    else {
      std::istringstream iss(command);
      std::string cmd;
      iss >> cmd;

      std::string pathvar = std::getenv("PATH");
      std::istringstream path_stream(pathvar);
      std::string dir;
      bool found = false;

      while (std::getline(path_stream, dir, ':')) {
        std::string filepath = dir + "/" + cmd;

        if (access(filepath.c_str(), X_OK) == 0) {
          found = true;
          std::system(command.c_str());
          break;
        }
      }

      if (!found) {
        std::cout << cmd << ": command not found\n";
      }
    }
  }

  return 0;
}