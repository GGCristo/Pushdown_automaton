#include "../include/Transition.h"
#include <iterator>
#include <tuple>

transition::transition(const std::string& initialState, const std::string& resultingState,
const std::string& symbolToConsume, const std::string& stackSymbolToConsume,
const std::vector<std::string>& stackSymbolsToAdd) :
initialState_(initialState), resultingState_(resultingState),
symbolToConsume_(symbolToConsume), stackSymbolToConsume_(stackSymbolToConsume),
stackSymbolsToAdd_(stackSymbolsToAdd)
{}

std::ostream& transition::show(std::ostream& os) const {
  os << "\t{ " << initialState_ << ", " << symbolToConsume_ << ", " << stackSymbolToConsume_ << ", " << resultingState_ << ", {";
  const char *padding = "";
  for (const auto& stackSymbolToAdd : stackSymbolsToAdd_) {
    os << padding << stackSymbolToAdd;
    padding = " ,";
  }
  os << "}}\n";
  return os;
}

////////////////////////////////////////////////////////////////////////////

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

std::vector<transition> transitionMap::find(const std::string& state,
const std::string& symbolToConsume, const std::string& stackSymbolToConsume) {
  auto tuple = std::make_tuple(state, symbolToConsume, stackSymbolToConsume);
  auto range = transitionMap_.equal_range(tuple);
  std::vector<transition> posiblesTransitions;
  posiblesTransitions.reserve(std::distance(range.first, range.second));
  for (auto it = range.first; it != range.second; it++) {
    posiblesTransitions.emplace_back(it->second);
  }
  // Non-deterministic behaviour
  tuple = std::make_tuple(state, ".", stackSymbolToConsume);
  range = transitionMap_.equal_range(tuple);
  posiblesTransitions.reserve(posiblesTransitions.capacity() + std::distance(range.first, range.second));
  for (auto it = range.first; it != range.second; it++) {
    posiblesTransitions.emplace_back(it->second);
  }
  return posiblesTransitions;
}

std::ostream& transitionMap::show(std::ostream& os) const {
  for (auto it = transitionMap_.begin(); it != transitionMap_.end(); it++) {
    it->second.show(os);
  }
  return os;
}
