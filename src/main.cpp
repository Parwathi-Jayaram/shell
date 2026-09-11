#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // TODO: Uncomment the code below to pass the first stage
  while (true) {
    std::cout << "$ ";
    std::string command;
    std::getline(std::cin, command);
    if (command == "exit") {
      break;
    }
    if (command.rfind("echo ", 0) == 0) {
      std::cout << command.substr(5) << "\n";
    } else if (command.rfind("type ", 0) == 0) {
      if (command.substr(5) == "echo" || command.substr(5) == "exit" ||
          command.substr(5) == "type") {
        std::cout << command.substr(5) << " is a shell builtin\n";
      } else {
        std::string pathvar = std::getenv("PATH");
        std::istringstream path_stream(pathvar);
        std::string pathsplit;
        int found = 0;
        while (std::getline(path_stream, pathsplit, ':')) {
          std::string filepath = pathsplit + '/' + command.substr(5);
          if (access(filepath.c_str(), X_OK) == 0) {
            std::cout << command.substr(5) << " is " << filepath << std::endl;
            found = 1;
            break;
          }
        }
        if (found == 0) {
          std::cout << command.substr(5) << ": not found\n";
        }
      }
    } else {
      std::cout << command << ": command not found\n";
    }
  }
  return 0;
}