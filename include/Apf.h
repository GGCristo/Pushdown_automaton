#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <vector>
#include <ostream>
#include <fstream>

class Apf {
  private:
  std::unordered_set<std::string> states_;
  std::unordered_set<std::string> alphabet_;
  std::unordered_set<std::string> stackAlphabet_;
  std::string initialState_;
  std::string initialStackSymbol_;
  std::vector<std::string> transitions_; // Create class
  std::unordered_set<std::string> finalStates_;
  public:
  Apf(std::ifstream& inputF);
  /* Apf(std::vector<std::string> states, std::vector<std::string> alphabet, */
  /*     std::vector<std::string> stackAlphabet, std::string initialState, std::string initialStackSymbol, */
  /*     std::vector<std::string> transitions, std::vector<std::string> finalStates); */
  std::ostream& show(std::ostream& os);
};

