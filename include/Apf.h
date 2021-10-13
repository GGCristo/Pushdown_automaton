#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <vector>
#include <ostream>
#include <fstream>
#include <stack>
#include <queue>

#include "Transition.h"

static bool trace;
const std::string EPSILON = ".";

class Apf {
  private:
  std::unordered_set<std::string> states_;
  std::unordered_set<std::string> alphabet_;
  std::unordered_set<std::string> stackAlphabet_;
  std::string initialState_;
  std::string initialStackSymbol_;
  TransitionMap transitions_;
  std::unordered_set<std::string> finalStates_;

  std::stack<std::string> stack_;

  bool isFinalState(const std::string& currentState) const;
  std::string getSymbol(const std::string& tape) const;
  static void transit(std::string& state, std::string& tape, std::stack<std::string>& stack, const Transition& result);
  static void removeSymbol(std::string& from, const std::string& symbolToRemove);
  bool recursiveRun(std::string state, std::string tape, std::stack<std::string> stack);
  static void showTrace(const std::string& state, const std::string& tape, std::stack<std::string> stack, std::queue<Transition> transitions);

  public:
  explicit Apf(std::ifstream& inputF);
  bool run(const std::string& tape);
  std::ostream& show(std::ostream& os);
};

std::string readLine(std::ifstream& inputF, const std::string& expectedToRead);
