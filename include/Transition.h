#pragma once
#include <cwchar>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <ostream>
#include <queue>

//{oldstate, currentSymbol, stackSymbolToConsume};
typedef std::tuple<std::string, std::string, std::string> transitInput;

// {newState, symbolToConsume, stackSymbolsToAdd}
/* typedef std::tuple<std::string, std::string, std::vector<std::string>> transitOutput; */

class transition {
  private:
  int id_;
  std::string oldState_;
  std::string newState_;
  std::string symbolToConsume_;
  std::string stackSymbolToConsume_;
  std::vector<std::string> stackSymbolsToAdd_;
  public:
  transition(int, const std::string&, const std::string&, const std::string&, const std::string&, const std::vector<std::string>&);
  int getID() const;
  std::string getNewState() const;
  std::string getSymbolToConsume() const;
  std::vector<std::string> getStackSymbolsToAdd() const;
  std::ostream& show(std::ostream& os) const;
};

class transitionMap {
  private:
  std::multimap<transitInput, transition> transitionMap_;
  public:
  void insert(std::stringstream line);
  std::queue<transition> find(const std::string& state, const std::string& symbolToConsume, const std::string& stackSymbolToConsume) const;
  std::ostream& show(std::ostream& os) const;
};
