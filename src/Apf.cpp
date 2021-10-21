#include "../include/Apf.h"
#include <sstream>

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
  auto check = [](const std::string& word, const std::unordered_set<std::string>& set) {
    if (word == EPSILON) {
      return;
    }
    if (set.find(word) == set.end()) {
      throw word + " doesn't belong to this automaton.\n";
    }
  };
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
  check(initialState_, states_);
  initialStackSymbol_ = readLine(inputF, "Initial Stack state");
  check(initialStackSymbol_, stackAlphabet_);
  std::stringstream finalStatesS(readLine(inputF, "Final states"));
  while (finalStatesS >> word) {
    finalStates_.emplace(word);
    check(word, states_);
  }
  // Transitions
  std::string lineString;
  int transitionID = 1;
  while (std::getline(inputF, lineString)) {
    if (lineString[0] == '#') {
      continue;
    }
    std::stringstream line(lineString);
    std::string initialState;
    line >> initialState;
    check(initialState_, states_);
    std::string symbolToConsume;
    line >> symbolToConsume;
    check(symbolToConsume, alphabet_);
    std::string stackSymbolToConsume;
    line >> stackSymbolToConsume;
    check(stackSymbolToConsume, stackAlphabet_);
    std::string resultingState;
    line >> resultingState;
    check(resultingState, states_);
    std::vector<std::string> stackSymbolsToAdd;
    std::string stackSymbolToAdd;
    while (line >> stackSymbolToAdd) {
      stackSymbolsToAdd.emplace_back(stackSymbolToAdd);
      check(stackSymbolToAdd, stackAlphabet_);
    }
    transitions_.insert(Transition(transitionID, initialState, resultingState, symbolToConsume, stackSymbolToConsume, stackSymbolsToAdd));
    transitionID++;
  }
  stack_.push(initialStackSymbol_);
}

bool Apf::run(const std::string& tape) {
  std::stack<std::string> stack;
  stack.push(initialStackSymbol_);
  if (trace) {
    std::cout << "State\tTape\tStack\tTransitions\n";
  }
  return recursiveRun(initialState_, tape, stack);
}

bool Apf::recursiveRun(const std::string& state, const std::string& tape, const std::stack<std::string>& stack) {
  std::queue<Transition> posibleTransitions = transitions_.find(state, getSymbol(tape), stack.top());
  if (trace) {
    showTrace(state, tape, stack, posibleTransitions);
  }
  if (tape.empty() && isFinalState(state)) {
    return true;
  }
  while (!posibleTransitions.empty()) {
    auto newResults = transit(tape, stack, posibleTransitions.front());
    posibleTransitions.pop();
    if (recursiveRun(std::get<0>(newResults), std::get<1>(newResults), std::get<2>(newResults))) {
      return true;
    }
  }
  return false;
}

void Apf::removeSymbol(std::string& from, const std::string& symbolToRemove) {
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

std::tuple<std::string, std::string, std::stack<std::string>> Apf::transit(const std::string& tape, const std::stack<std::string>& stack, const Transition& result) {
  if (stack.empty()) {
    std::string error = "You have tried to transit when the stack was empty.\n";
    error += "Debug Info: oldstate: " + result.getOldState() + " oldtape " + tape + '\n';
    error += "newstate: " + result.getNewState() + '\n';
    throw error;
  }
  std::string newState = result.getNewState();
  std::string newTape = tape;
  removeSymbol(newTape, result.getSymbolToConsume());
  std::stack<std::string> newStack(stack);
  newStack.pop();
  std::vector<std::string> stackSymbolsToAdd = result.getStackSymbolsToAdd();
  for (auto it = stackSymbolsToAdd.rbegin(); it != stackSymbolsToAdd.rend(); it++) {
    if (*it == EPSILON) {
      break;
    }
    newStack.push(*it);
  }
  return std::make_tuple(newState, newTape, newStack);
}

std::string Apf::getSymbol(const std::string& tape) const {
  std::string symbol;
  for (char c : tape) {
    symbol += c;
    if (alphabet_.find(symbol) == alphabet_.end()) {
      symbol.pop_back();
      return symbol;
    }
  }
  return symbol;
}

bool Apf::isFinalState(const std::string& currentState) const {
  return (finalStates_.find(currentState) != finalStates_.end());
}

void Apf::showTrace(const std::string& state, const std::string& tape, std::stack<std::string> stack, std::queue<Transition> transitions) {
  std::cout << state << '\t';
  if (tape.empty()) {
    std::cout << "-\t";
  } else {
    std::cout << tape << '\t';
  }
  while (!stack.empty()) {
    std::cout << stack.top();
    stack.pop();
  }
  std::cout << '\t';
  if (transitions.empty()) {
    std::cout << "No transitions";
  }
  while (!transitions.empty()) {
    std::cout << transitions.front().getID() << ' ';
    transitions.pop();
  }
  std::cout << '\n';
}

std::ostream& Apf::show(std::ostream& os) { // TODO sort
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
