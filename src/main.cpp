#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../include/Apf.h"

void realMain(int argc, char **argv);

int main(int argc, char **argv) {
  try {
    realMain(argc, argv);
  } catch (const std::string& ex){
    std::cerr << ex << '\n';
    return -1;
  }
}

void realMain(int argc, char **argv) {
  std::ifstream inputF(argv[1], std::ifstream::in); // TODO, bad call
  if (inputF.fail()) {
    throw "The file could not be opened: " + std::string(argv[1]) + '\n';
  }
  Apf Apf_(inputF);
  inputF.close();
  Apf_.show(std::cout);
  std::cout << "How many strings are you going to check?\n";
  int numberOfStrings;
  std::string string;
  std::cin >> numberOfStrings;
  for (int i = 0; i < numberOfStrings; i++) {
    std::cout << "Introduce a string: ";
    std::cin >> string;
    if (Apf_.run(string)) {
      std::cout << "It belongs to the language\n";
    } else {
      std::cout << "Does not belongs to the language\n";
    }
  }
}
