#include "../include/Transition.h"
#include <tuple>

transition::transition(const std::string& initialState, const std::string& resultingState,
const std::string& symbolToConsume, const std::string& stackSymbolToConsume,
const std::vector<std::string>& stackSymbolsToAdd) :
initialState_(initialState), resultingState_(resultingState),
symbolToConsume_(symbolToConsume), stackSymbolToConsume_(stackSymbolToConsume),
stackSymbolsToAdd_(stackSymbolsToAdd)
{}

std::ostream& transition::show(std::ostream& os) {
  os << "\t{ " << initialState_ << ", " << symbolToConsume_ << ", " << stackSymbolToConsume_ << ", " << resultingState_ << ", {";
  const char *padding = "";
  for (const auto& stackSymbolToAdd : stackSymbolsToAdd_) {
    os << padding << stackSymbolToAdd;
    padding = " ,";
  }
  os << "}}\n";
  return os;
}

void transitionMap::insert(std::stringstream line) {
  std::string initialState;
  line >> initialState;
  std::string symbolToConsume;
  line >> symbolToConsume;
  std::string stackSymbolToConsume;
  line >> stackSymbolToConsume;
  std::string resultingState;
  line >> resultingState;
  std::vector<std::string> stackSymbolsToAdd;
  std::string stackSymbolToAdd;
  while (line >> stackSymbolToAdd) {
    stackSymbolsToAdd.emplace_back(stackSymbolToAdd);
  }
  transitionMap_.emplace(std::make_tuple(initialState, symbolToConsume, stackSymbolToConsume),
  transition(initialState, resultingState, symbolToConsume, stackSymbolToConsume, stackSymbolsToAdd));
}

std::ostream& transitionMap::show(std::ostream& os) {
  for (auto it = transitionMap_.begin(); it != transitionMap_.end(); it++) {
    it->second.show(os);
  }
  return os;
}
