#include "../include/Transition.h"
#include <iterator>
#include <tuple>

transition::transition(int id, const std::string& initialState, const std::string& resultingState,
const std::string& symbolToConsume, const std::string& stackSymbolToConsume,
const std::vector<std::string>& stackSymbolsToAdd) :
oldState_(initialState), newState_(resultingState),
symbolToConsume_(symbolToConsume), stackSymbolToConsume_(stackSymbolToConsume),
stackSymbolsToAdd_(stackSymbolsToAdd)
{
  id_ = id;
}

int transition::getID() const {
  return id_;
}

std::string transition::getNewState() const {
  return newState_;
}

std::string transition::getSymbolToConsume() const {
  return symbolToConsume_;
}

std::vector<std::string> transition::getStackSymbolsToAdd() const {
  return stackSymbolsToAdd_;
}

std::ostream& transition::show(std::ostream& os) const {
  os << '\t' << id_ << ". { " << oldState_ << ", " << symbolToConsume_ << ", " << stackSymbolToConsume_ << ", " << newState_ << ", {";
  const char *padding = "";
  for (const auto& stackSymbolToAdd : stackSymbolsToAdd_) {
    os << padding << stackSymbolToAdd;
    padding = ", ";
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
  transition(transitionMap_.size() + 1, initialState, resultingState, symbolToConsume, stackSymbolToConsume, stackSymbolsToAdd));
}

std::queue<transition> transitionMap::find(const std::string& state,
const std::string& symbolToConsume, const std::string& stackSymbolToConsume) const {
  auto tuple = std::make_tuple(state, symbolToConsume, stackSymbolToConsume);
  auto range = transitionMap_.equal_range(tuple);
  std::queue<transition> posiblesTransitions;
  for (auto it = range.first; it != range.second; it++) {
    posiblesTransitions.push(it->second);
  }
  // Non-deterministic behaviour
  tuple = std::make_tuple(state, ".", stackSymbolToConsume);
  range = transitionMap_.equal_range(tuple);
  for (auto it = range.first; it != range.second; it++) {
    posiblesTransitions.push(it->second);
  }
  return posiblesTransitions;
}

std::ostream& transitionMap::show(std::ostream& os) const {
  for (auto it = transitionMap_.begin(); it != transitionMap_.end(); it++) {
    it->second.show(os);
  }
  return os;
}
