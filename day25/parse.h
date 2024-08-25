#pragma once

#include <string>
#include <vector>

static std::vector<int> stoi_vector(std::vector<std::string> strings) {

  std::vector<int> ints;

  for (std::string str : strings) {
    ints.push_back(stoi(str));
  }

  return ints;
}

static std::vector<std::string> splitString(std::string str, char delimiter) {

  std::vector<std::string> toReturn;
  std::string st = "";

  for (char c : str) {
    if (c == delimiter) {
      toReturn.push_back(st);
      st = "";
    } else {
      st += c;
    }
  }

  toReturn.push_back(st);

  return toReturn;
}
