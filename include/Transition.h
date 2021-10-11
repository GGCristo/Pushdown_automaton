#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <ostream>

class transition {
  private:
  std::string initialState_;
  std::string resultingState_;
  std::string symbolToConsume_;
  std::string stackSymbolToConsume_;
  std::vector<std::string> stackSymbolsToAdd_;
  public:
  transition(const std::string&, const std::string&, const std::string&, const std::string&, const std::vector<std::string>&);
  std::ostream& show(std::ostream& os);
};

class transitionMap {
  private:
  // Key: state, symbolToConsumed, stackSymbolToConsume;
  // Value: transition
  std::map<std::tuple<std::string, std::string, std::string>, transition> transitionMap_;
  public:
  void insert(std::stringstream line);
  std::ostream& show(std::ostream& os);
};
