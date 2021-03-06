#include "../include/Transition.h"
#include <iterator>
#include <tuple>

Transition::Transition(size_t id, std::string initialState, std::string resultingState,
std::string symbolToConsume, std::string stackSymbolToConsume,
std::vector<std::string> stackSymbolsToAdd) :
oldState_(std::move(initialState)), newState_(std::move(resultingState)),
symbolToConsume_(std::move(symbolToConsume)), stackSymbolToConsume_(std::move(stackSymbolToConsume)),
stackSymbolsToAdd_(std::move(stackSymbolsToAdd))
{
  id_ = id;
}

size_t Transition::getID() const {
  return id_;
}

std::string Transition::getNewState() const {
  return newState_;
}

std::string Transition::getOldState() const {
  return oldState_;
}

std::string Transition::getSymbolToConsume() const {
  return symbolToConsume_;
}

std::string Transition::getStackSymbolsToConsume() const {
  return stackSymbolToConsume_;
}

std::vector<std::string> Transition::getStackSymbolsToAdd() const {
  return stackSymbolsToAdd_;
}

std::ostream& Transition::show(std::ostream& os) const {
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

void TransitionMap::insert(const Transition& transition) {
  transitionMap_.emplace(std::make_tuple(transition.getOldState(), transition.getSymbolToConsume(), transition.getStackSymbolsToConsume()), transition);
}

std::queue<Transition> TransitionMap::find(const std::string& state,
const std::string& symbolToConsume, const std::string& stackSymbolToConsume) const {
  auto tuple = std::make_tuple(state, symbolToConsume, stackSymbolToConsume);
  auto range = transitionMap_.equal_range(tuple);
  std::queue<Transition> posiblesTransitions;
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

std::ostream& TransitionMap::show(std::ostream& os) const {
for (const auto& it : transitionMap_) {
    it.second.show(os);
  }
  return os;
}
