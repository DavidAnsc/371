#pragma once
#include <array>

class Block {
  int value;
  int length;
  std::array<int, 10> possibleValues;

 public:
  inline Block(): value(0), length(10), possibleValues{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}} {}
  // length's default value is 1 since it always has the choice to be 0 and we skipped the first 0 in the
  inline Block(std::array<int, 10> possibleValues): value(0), length(0), possibleValues(possibleValues) {
    // since 0 could be in the first place. and we want to skip that specific 0 and actually count it.
    for (size_t i = 0; i < 10; ++i) {
      if (i != 0 && possibleValues.at(i) == 0) {
        break;
      }
      ++length;
    }
  }

  
  inline void setValue(int nw) {
    value = nw;
  }
  inline void setLength(int nw) {
    length = nw;
  }
  inline void setPossibleValues(std::array<int, 10> nw) {
    possibleValues = nw;
  }

  inline const int& get() const {
    return value;
  }
  inline const int& getLength() const {
    return length;
  }
  inline const std::array<int, 10>& getPossibleValues() const {
    return possibleValues;
  }
};