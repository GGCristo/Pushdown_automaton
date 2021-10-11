#include "../include/Apf.h"

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
    transitions_.push_back(transition);
  }
}

std::ostream& Apf::show(std::ostream& os) { // TODO Improve
  os << "Pushdown automaton (7-tuple)\n";
  os << "1. States\n\t";
  for (auto it = states_.begin(); it != states_.end(); it++) {
    os << *it << ", ";
  }
  os << "\n2. Alphabet\n\t";
  for (auto it = alphabet_.begin(); it != alphabet_.end(); it++) {
    os << *it << ", ";
  }
  os << "\n3. StackAlphabet\n\t";
  for (auto it = alphabet_.begin(); it != alphabet_.end(); it++) {
    os << *it << ", ";
  }
  os << "\n4. InitialState: " << initialState_;
  os << "\n5. InitialStackSymbol: " << initialStackSymbol_;
  os << "\n6. Transitions\n\t";
  for (int i = 0; i < transitions_.size(); i++) {
    os << transitions_[i] << ", ";
  }
  os << "\n7. FinalStates\n\t";
  for (auto it = finalStates_.begin(); it != finalStates_.end(); it++) {
    os << *it << ", ";
  }
  os << '\n';
  return os;
}

/* Apf::Apf(std::vector<std::string> states, std::vector<std::string> alphabet, */
/* std::vector<std::string> stackAlphabet, std::string initialState, */
/* std::string initialStackSymbol,std::vector<std::string> transitions, */
/* std::vector<std::string> finalStates) { */
/*   for (int i = 0; i < states.size(); i++) { */
/*     states_.emplace(states[i]); */
/*   } */
/*   for (int i = 0; i < alphabet.size(); i++) { */
/*     alphabet_.emplace(alphabet[i]); */
/*   } */
/*   for (int i = 0; i < stackAlphabet.size(); i++) { */
/*     stackAlphabet_.emplace(stackAlphabet[i]); */
/*   } */
/*   initialState_ = initialState; */
/*   initialStackSymbol_ = initialState; */
/*   for (int i = 0; i < transitions.size(); i++) { */
/*     transitions_.emplace_back(transitions[i]); */
/*   } */
/*   for (int i = 0; i < finalStates.size(); i++) { */
/*     finalStates_.emplace(finalStates[i]); */
/*   } */
/* } */
