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
  std::ostream& show(std::ostream& os) const;
};

class transitionMap {
  private:
  // Key: state, symbolToConsumed, stackSymbolToConsume;
  // Value: transition
  std::multimap<std::tuple<std::string, std::string, std::string>, transition> transitionMap_;
  public:
  void insert(std::stringstream line);
  std::vector<transition> find(const std::string& state, const std::string& symbolToConsume, const std::string& stackSymbolToConsume);
  std::ostream& show(std::ostream& os) const;
};
