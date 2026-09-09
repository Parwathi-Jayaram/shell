#include <iostream>
#include <string>
using namespace std;
int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // TODO: Uncomment the code below to pass the first stage
  while(true){
  std::cout << "$ ";
  std::string command;
  getline(cin, command);
  if(command=="exit"){
    break;
  }
  if(command.substr(0,5)=="type "){
    if(command.substr(5)=="echo"){
      cout<<"echo is a shell builtin"<<endl;
    }else if(command.substr(5)=="exit"){
      cout<<"exit is a shell builtin"<<endl;
    }else if(command.substr(5)=="type"){
      cout<<"type is a shell builtin"<<endl;
    }else{
      cout<<command.substr(5)<<": not found"<<endl;
    }
  }else if(command.substr(0,5)=="echo "){
    std::cout<<command.substr(5)<<endl;
  }else{
  std::cout<<command<<": command not found"<<endl;
  }
}
}
