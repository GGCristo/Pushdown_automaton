#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <vector>
#include <ostream>
#include <fstream>

#include "Transition.h"

class Apf {
  private:
  std::unordered_set<std::string> states_;
  std::unordered_set<std::string> alphabet_;
  std::unordered_set<std::string> stackAlphabet_;
  std::string initialState_;
  std::string initialStackSymbol_;
  transitionMap transitions_;
  std::unordered_set<std::string> finalStates_;
  public:
  explicit Apf(std::ifstream& inputF);
  std::ostream& show(std::ostream& os);
};

