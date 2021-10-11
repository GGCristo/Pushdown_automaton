#include "../include/Apf.h"

std::string readLine(std::ifstream& inputF, const std::string& expectedToRead) {
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

Apf::Apf(std::ifstream& inputF) {
  std::string word;
  std::stringstream statesS(readLine(inputF, "States"));
  while (statesS >> word) {
    states_.emplace(word);
  }
  std::stringstream alphabetS(readLine(inputF, "Alphabet"));
  while (alphabetS >> word) {
    alphabet_.emplace(word);
  }
  std::stringstream stackAlphabetS(readLine(inputF, "Alphabet"));
  while (stackAlphabetS >> word) {
    stackAlphabet_.emplace(word);
  }
  initialState_ = readLine(inputF, "Initial State");
  initialStackSymbol_ = readLine(inputF, "Initial Stack state");
  std::stringstream finalStatesS(readLine(inputF, "Final states"));
  while (finalStatesS >> word) {
    finalStates_.emplace(word);
  }
  std::string transition;
  while (std::getline(inputF, transition)) {
    if (transition[0] == '#') {
      continue;
    }
    transitions_.insert(std::stringstream(transition));
  }
}

std::ostream& Apf::show(std::ostream& os) {
  os << "Pushdown automaton (7-tuple)\n";
  const char *padding = "";
  os << "1. States\n\t";
  for (const auto& state : states_) {
    os << padding << state;
    padding = ", ";
  }
  padding = "";
  os << "\n2. Alphabet\n\t";
  for (const auto& character : alphabet_) {
    os << padding << character;
    padding = ", ";
  }
  padding = "";
  os << "\n3. StackAlphabet\n\t";
  for (const auto& character : stackAlphabet_) {
    os << padding << character;
    padding = ", ";
  }
  os << "\n4. InitialState: " << initialState_;
  os << "\n5. InitialStackSymbol: " << initialStackSymbol_;
  os << "\n6. Transitions\n";
  transitions_.show(os);
  padding = "";
  os << "\n7. FinalStates\n\t";
  for (const auto& finalState : finalStates_) {
    os << padding << finalState; 
    padding = ", ";
  }
  os << '\n';
  return os;
}
