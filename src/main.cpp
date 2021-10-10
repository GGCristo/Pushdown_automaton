#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

std::string readLine(std::ifstream& inputF, std::string expectedToRead);
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
  std::ifstream inputF(argv[1], std::ifstream::in);
  if (inputF.fail()) {
    std::cerr << "The file could not be opened: " << argv[1] << '\n';
    throw;
  }
  std::string word;
  std::stringstream states(readLine(inputF, "States"));
  while (states >> word) {
    std::cout << "State: " << word << '\n';
  }
  std::stringstream alphabet(readLine(inputF, "Alphabet"));
  while (alphabet >> word) {
    std::cout << "Alphabet: " << word << '\n';
  }
  std::stringstream stackAlphabet(readLine(inputF, "Alphabet"));
  while (stackAlphabet >> word) {
    std::cout << "Stack alphabet: " << word << '\n';
  }
  std::stringstream initialState(readLine(inputF, "Initial State"));
  while (initialState >> word) {
    std::cout << "Initial State: " << word << '\n';
  }
  std::stringstream initialStackState(readLine(inputF, "Initial Stack state"));
  while (initialStackState >> word) {
    std::cout << "Initial stack state: " << word << '\n';
  }
  std::stringstream finalStates(readLine(inputF, "Final states"));
  while (finalStates >> word) {
    std::cout << "Final states: " << word << '\n';
  }
  std::vector<std::string> transitions;
  std::string transition;
  while (std::getline(inputF, transition)) {
    if (transition[0] == '#') {
      continue;
    }
    transitions.push_back(transition);
  }
  for (int i = 0; i < transitions.size(); i++) {
    std::cout << transitions[i] << '\n';
  }
  inputF.close();
}

std::string readLine(std::ifstream& inputF, std::string expectedToRead) {
  std::string line;
  bool error;
  do { // TODO explore error
    line.clear();
    error = !std::getline(inputF, line);
  } while (line[0] == '#' && !error); // If line is a comment read next
  if (error) {
    throw expectedToRead + " line is missing or is in a incorrect position in the input file.\n";
  }
  return line;
}
