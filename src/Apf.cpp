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

Apf::Apf(std::ifstream& inputF) { // TODO check is a correct automaton
  std::string word;
  std::stringstream statesS(readLine(inputF, "States"));
  while (statesS >> word) {
    states_.emplace(word);
  }
  std::stringstream alphabetS(readLine(inputF, "Alphabet"));
  while (alphabetS >> word) {
    alphabet_.emplace(word);
  }
  std::stringstream stackAlphabetS(readLine(inputF, "Stack alphabet"));
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

  stack_.push(initialStackSymbol_);
}

bool Apf::run(std::string tape) {
  std::stack<std::string> stack;
  stack.push(initialStackSymbol_);
  std::cout << "State\tTape\tStack\tTransitions\n";
  return recursiveRun(initialState_, tape, stack);
}

bool Apf::recursiveRun(std::string state, std::string tape, std::stack<std::string> stack) {
  std::queue<transition> posibleTransitions = transitions_.find(state, getSymbol(tape), stack.top());
  showTrace(state, tape, stack, posibleTransitions);
  if (posibleTransitions.empty() || stack.empty()) { // TODO ask this
    if (isFinalState(state) && tape.empty()) {
      return true;
    }
    return false;
  }
  while (!posibleTransitions.empty()) {
    transition transition = posibleTransitions.front();
    posibleTransitions.pop();
    transit(state, tape, stack, transition);
    if (recursiveRun(state, tape, stack)) {
      return true;
    }
  }
  return false;
}

void removeSymbol(std::string& from, const std::string& symbolToRemove) {
  if (symbolToRemove == EPSILON) {
    return;
  }
  auto pos = from.find(symbolToRemove);
  if (pos == std::string::npos) {
    throw "Symbol to remove not found. Trying to delete the symbol " + symbolToRemove + " from " + from + '\n';
  }
  if (pos != 0) {
    throw "Triying to remove wrong symbol. Trying to delete the symbol " + symbolToRemove + " from " + from + '\n';
  }
  from.erase(pos, symbolToRemove.length());
}

void transit(std::string& state, std::string& tape, std::stack<std::string>& stack, const transition& result) {
  if (stack.empty()) {
    std::string error = "You have tried to transit when the stack was empty.\n";
    error += "Debug Info: oldstate: " + state + " oldtape " + tape + '\n';
    error += "newstate: " + result.getNewState() + '\n';
    throw error;
  }
  stack.pop();
  state = result.getNewState();
  removeSymbol(tape, result.getSymbolToConsume());
  std::vector<std::string> stackSymbolsToAdd = result.getStackSymbolsToAdd();
  for (int i = stackSymbolsToAdd.size() - 1; i >= 0; i--) {
    if (stackSymbolsToAdd[i] == EPSILON) {
      break;
    }
    stack.push(stackSymbolsToAdd[i]);
  }
}

std::string Apf::getSymbol(const std::string& string) const {
  std::string symbol;
  for (int i = 0; i < string.size(); i++) {
    symbol += string[i];
    if (alphabet_.find(symbol) == alphabet_.end()) {
      symbol.pop_back();
      return symbol;
    }
  }
  return symbol;
}

bool Apf::isFinalState(const std::string& currentState) const {
  if (finalStates_.find(currentState) != finalStates_.end()) {
    return true;
  }
  return false;
}

void showTrace(const std::string& state, const std::string& tape, std::stack<std::string> stack, std::queue<transition> transitions) {
  std::cout << state << '\t' << tape << '\t';
  while (!stack.empty()) {
    std::cout << stack.top();
    stack.pop();
  }
  std::cout << '\t';
  while (!transitions.empty()) {
    std::cout << transitions.front().getID() << ' ';
    transitions.pop();
  }
  std::cout << '\n';
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
  os << "\n7. Final States\n\t";
  for (const auto& finalState : finalStates_) {
    os << padding << finalState; 
    padding = ", ";
  }
  os << '\n';
  return os;
}
