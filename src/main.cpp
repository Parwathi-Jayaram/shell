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

    else if (command == "echo") {
      std::cout << "\n";
    }

    else if (command.rfind("type ", 0) == 0) {
      std::string cmd = command.substr(5);

      if (cmd == "echo" || cmd == "exit" || cmd == "type") {
        std::cout << cmd << " is a shell builtin\n";
      } else {
        const char *path_env = std::getenv("PATH");

        if (path_env != nullptr) {
          std::istringstream path_stream(path_env);
          std::string dir;

          while (std::getline(path_stream, dir, ':')) {
            std::string filepath = dir + "/" + cmd;

            if (access(filepath.c_str(), X_OK) == 0) {
              std::cout << cmd << " is " << filepath << "\n";
              goto done;
            }
          }
        }

        std::cout << cmd << ": not found\n";
      }
    done:;
    }

    else {
      std::cout << command << ": command not found\n";
    }
  }

  return 0;
}