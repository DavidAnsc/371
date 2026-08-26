#include "Block.h"
#include <array>
#include <set>
#include <cstdio>
#include <iostream>


/*
C = 10
R = 24
*/


static std::array<std::array<Block, 5>, 12> coordinate {{
                                                  {Block(), Block(), Block({4, 5, 6}), Block({4, 5, 6}), Block()},
                                                  {Block(), Block(), Block({4, 5, 6}), Block(), Block()},
                                                  {Block(), Block(), Block(), Block(), Block()},
                                                  {Block(), Block(), Block(), Block(), Block()},
                                                  {Block({3, 7, 8}), Block(), Block(), Block(), Block()},
                                                  {Block({3, 7, 8}), Block({3, 7, 8}), Block(), Block(), Block()},
                                                  {Block(), Block(), Block(), Block(), Block()},
                                                  {Block(), Block(), Block(), Block(), Block()},
                                                  {Block(), Block(), Block(), Block(), Block()},
                                                  {Block(), Block({1, 3, 7}), Block({1, 3, 7}), Block(), Block()},
                                                  {Block(), Block(), Block({1, 3, 7}), Block(), Block()},
                                                  {Block(), Block(), Block(), Block(), Block()},
                                                }};

static std::array<std::array<int, 5>, 12> orgMarks {{
                                              {0, 0, 1, 1, 0}, 
                                              {0, 0, 1, 0, 0}, 
                                              {0, 0, 0, 0, 0}, 
                                              {0, 0, 0, 0, 0},
                                              {1, 0, 0, 0, 0},
                                              {1, 1, 0, 0, 0},
                                              {0, 0, 0, 0, 0},
                                              {0, 0, 0, 0, 0},
                                              {0, 0, 0, 0, 0},
                                              {0, 1, 1, 0, 0},
                                              {0, 0, 1, 0, 0},
                                              {0, 0, 0, 0, 0}}};

int count {0};
std::array<std::array<Block, 5>, 12> results {};

bool checkIsShaded(int x, int y) {
  static const std::set<std::pair<int, int>> shaded = {
    {0, 1}, {1, 1}, {1, 3}, {2, 3}, {4, 1},
    {4, 2}, {4, 3}, {6, 1}, {7, 1}, {7, 3},
    {8, 3}, {9, 3}, {10, 3}, {10, 1}, {11, 1}
  };
  return shaded.find({x, y}) != shaded.end();
}

bool checkHasDuplicates(int xAxis, int yAxis, const std::array<std::array<Block, 5>, 12>& coordinateSystem) {
  int tempNumCount {};
  std::set<int> tempNums {};
  for (int yI = 0; yI < 5; ++yI) {
    int val = coordinateSystem.at(xAxis).at(yI).get();
    if (val == 0) {
      continue;
    }
    ++tempNumCount;
    tempNums.insert(val);
  }
  
  if (tempNumCount != tempNums.size()) {
    return true;
  }

  tempNumCount = 0;
  tempNums = {};
  for (int xI = 0; xI < 12; ++xI) {
    int val = coordinateSystem.at(xI).at(yAxis).get();
    if (val == 0) {
      continue;
    }
    ++tempNumCount;
    tempNums.insert(val);
  }

  if (tempNumCount != tempNums.size()) {
    return true;
  }
  return false;
}

static bool checkHasRepeatWithinArea(const std::array<std::array<Block, 5>, 12>& system, const std::array<std::array<int, 2>, 3> areaDef) {
  int tempNumCount {0};
  std::set<int> tempNums {};

  for (int i = 0; i < 3; ++i) {
    const int currentValue = system.at(areaDef.at(i).at(0)).at(areaDef.at(i).at(1)).get();
    if (currentValue == 0) {
      continue;
    }
    ++tempNumCount;
    tempNums.insert(currentValue);
  }
  
  if (tempNumCount == static_cast<int>(tempNums.size())) {
    return false;
  }
  return true;
}
static bool checkHasRepeatWithinArea(const std::array<std::array<Block, 5>, 12>& system, const std::array<std::array<int, 2>, 4> areaDef) {
  int tempNumCount {0};
  std::set<int> tempNums {};

  for (int i = 0; i < 4; ++i) {
    if (areaDef.at(i).at(0) == 0 && areaDef.at(i).at(1) == 0) {
      continue;
    }

    const int currentValue = system.at(areaDef.at(i).at(0)).at(areaDef.at(i).at(1)).get();
    if (currentValue == 0) {
      continue;
    }
    ++tempNumCount;
    tempNums.insert(currentValue);
  }
  
  if (tempNumCount == static_cast<int>(tempNums.size())) {
    return false;
  }
  return true;
}

bool checkHasEmptyValueWithinArea(const std::array<std::array<Block, 5>, 12>& system, const std::array<std::array<int, 2>, 4> areaDef) {
  for (int i = 0; i < 4; ++i) {
    int xCoo = areaDef.at(i).at(0);
    int yCoo = areaDef.at(i).at(1);
    if (yCoo == 0 && xCoo == 0) {
      continue;
    }
    if (system.at(xCoo).at(yCoo).get() == 0) {
      return true;
    }
  }
  return false;
}

bool checkHasSpecificValuesWithinArea(const std::array<std::array<Block, 5>, 12>& system, const std::array<std::array<int, 2>, 4> areaDef, const std::set<int> vals) {
  std::set<int> tempSet {};
  for (int i = 0; i < 4; ++i) {
    if (areaDef.at(i).at(0) == 0 && areaDef.at(i).at(1) == 0) {
      continue;
    }
    
    int currentVal = system.at(areaDef.at(i).at(0)).at(areaDef.at(i).at(1)).get();
    if (currentVal == 0) {
      continue;
    }
    tempSet.insert(currentVal);
  }
  if (std::includes(tempSet.begin(), tempSet.end(), vals.begin(), vals.end())) {
    return true;
  }
  return false;
}

bool checkIsValidForRestrictedArea(const int num, const std::array<std::array<Block, 5>, 12>& system) {
  if (num == 1) {
    std::array<std::array<int, 2>, 4> area1 {{{1, 4}, {2, 4}}};
    std::set<int> area1Vals {1};

    bool empty1 = checkHasEmptyValueWithinArea(system, area1);
    bool repeat1 = checkHasRepeatWithinArea(system, area1);
    bool hasVal1 = checkHasSpecificValuesWithinArea(system, area1, area1Vals);

    if (empty1) {
      return false;
    }
    if (repeat1) {
      return false;
    }
    if (!hasVal1) {
      return false;
    }
    return true;
  } else if (num == 2) {
    std::array<std::array<int, 2>, 4> area2 {{{2, 1}, {2, 2}, {3, 1}, {3, 2}}};
    std::set<int> area2Vals {1, 3, 9};

    bool empty2 = checkHasEmptyValueWithinArea(system, area2);
    bool repeat2 = checkHasRepeatWithinArea(system, area2);
    bool hasVal2 = checkHasSpecificValuesWithinArea(system, area2, area2Vals);

    if (empty2) {
      return false;
    }
    if (repeat2) {
      return false;
    }
    if (!hasVal2) {
      return false;
    }
    return true;
  } else if (num == 3) {
    std::array<std::array<int, 2>, 4> area3 {{{6, 3}, {6, 4}, {7, 4}}};
    std::set<int> area3Vals {8, 9};

    bool empty3 = checkHasEmptyValueWithinArea(system, area3);
    bool repeat3 = checkHasRepeatWithinArea(system, area3);
    bool hasVal3 = checkHasSpecificValuesWithinArea(system, area3, area3Vals);

    if (empty3) {
      return false;
    }
    if (repeat3) {
      return false;
    }
    if (!hasVal3) {
      return false;
    }
    return true;
  } else if (num == 4) {
    std::array<std::array<int, 2>, 4> area4 {{{7, 2}, {8, 1}, {8, 2}}};
    std::set<int> area4Vals {2, 4};
    
    bool empty4 = checkHasEmptyValueWithinArea(system, area4);
    bool repeat4 = checkHasRepeatWithinArea(system, area4);
    bool hasVal4 = checkHasSpecificValuesWithinArea(system, area4, area4Vals);

    if (empty4) {
      return false;
    }
    if (repeat4) {
      return false;
    }
    if (!hasVal4) {
      return false;
    }
    return true;
  } else if (num == 5) {
    std::array<std::array<int, 2>, 4> area5 {{{9, 4}, {10, 4}}};
    std::set<int> area5Vals {3, 6};
    
    bool empty5 = checkHasEmptyValueWithinArea(system, area5);
    bool repeat5 = checkHasRepeatWithinArea(system, area5);
    bool hasVal5 = checkHasSpecificValuesWithinArea(system, area5, area5Vals);

    if (empty5) {
      return false;
    }
    if (repeat5) {
      return false;
    }
    if (!hasVal5) {
      return false;
    }
    return true;
  } else {
    abort();
  }
}

bool checkHasRepeatWithinDefinedAreas(const std::array<std::array<Block, 5>, 12>& system) {
  std::array<std::array<int, 2>, 3> area1 {{{0, 2}, {0, 3}, {1, 2}}};
  std::array<std::array<int, 2>, 3> area2 {{{4, 0}, {5, 0}, {5, 1}}};
  std::array<std::array<int, 2>, 3> area3 {{{9, 1}, {9, 2}, {10, 2}}};
  if (checkHasRepeatWithinArea(system, area1) || checkHasRepeatWithinArea(system, area2) || checkHasRepeatWithinArea(system, area3)) {
    return true;
  }
  return false;
}

bool checkSums(const std::array<std::array<Block, 5>, 12>& system) {
  for (int yI = 0; yI < 5; ++yI) {
    int tempSum {};
    for (int xA = 0; xA < 12; ++xA) {
      tempSum += system.at(xA).at(yI).get();
    }
    if (tempSum != 24) {
      return false;
    }
  }

  for (int xA = 0; xA < 12; ++xA) {
    int tempSum {};
    for (int yI = 0; yI < 5; ++yI) {
      tempSum += system.at(xA).at(yI).get();
    }
    if (tempSum != 10) {
      return false;
    }
  }
  return true;
}

int getColSum(const int xAxis, const std::array<std::array<Block, 5>, 12>& system) {
  int tempSum {};
  for (int yI = 0; yI < 5; ++yI) {
    tempSum += system.at(xAxis).at(yI).get();
  }
  return tempSum;
}

void recurse(int& xOld, int& yOld, int choice, std::array<std::array<Block, 5>, 12>& coordinateSystem) {
  const Block tempBlock = coordinateSystem.at(xOld).at(yOld);
  
  int nextY = yOld;
  int nextX = xOld;

  if (nextY == 4) {
    ++nextX;
    nextY = 0;
  } else {
    ++nextY;
  }

  if (nextX >= 12) {
    if (checkSums(coordinateSystem) == false) {
      printf("the row/col sums don't add up. DELETED BOARD\n");
      return;
    }

    results = coordinateSystem;
    ++count;
    printf("finished compute num: [%d].\n", count);
    exit(0);

    return;
  }
  const int oldBlockValue = coordinateSystem.at(xOld).at(yOld).get();
  
  coordinateSystem.at(xOld).at(yOld).setValue(choice);
  printf("Assigned value: [%d] to (%d, %d)\n", choice, xOld, yOld);

  bool skip {false};

  if (checkIsShaded(xOld, yOld) == true) {
    skip = true;
  }

  if (skip == false) {
    // check for the restricted areas
    if (xOld == 2 && yOld == 4) {
      if (!checkIsValidForRestrictedArea(1, coordinateSystem)) {
        coordinateSystem.at(xOld).at(yOld).setValue(oldBlockValue);
        printf("the restricted area is not valid.\n");
        return;
      }
    } else if (xOld == 3 && yOld == 2) {
      if (!checkIsValidForRestrictedArea(2, coordinateSystem)) {
        coordinateSystem.at(xOld).at(yOld).setValue(oldBlockValue);
        printf("the restricted area is not valid.\n");
        return;
      }
    } else if (xOld == 7 && yOld == 4) {
      if (!checkIsValidForRestrictedArea(3, coordinateSystem)) {
        coordinateSystem.at(xOld).at(yOld).setValue(oldBlockValue);
        printf("the restricted area is not valid.\n");
        return;
      }
    } else if (xOld == 8 && yOld == 2) {
      if (!checkIsValidForRestrictedArea(4, coordinateSystem)) {
        coordinateSystem.at(xOld).at(yOld).setValue(oldBlockValue);
        printf("the restricted area is not valid.\n");
        return;
      }
    } else if (xOld == 10 && yOld == 4) {
      if (!checkIsValidForRestrictedArea(5, coordinateSystem)) {
        coordinateSystem.at(xOld).at(yOld).setValue(oldBlockValue);
        printf("the restricted area is not valid.\n");
        return;
      }
    }
    
    if (yOld == 4) {
      // this means it just finished a col
      int colSum = getColSum(xOld, coordinateSystem);
      if (colSum != 10) {
        coordinateSystem.at(xOld).at(yOld).setValue(oldBlockValue);
        printf("the col that just got finished doesn't have a col sum of 10.\n");
        return;
      }
    }
    if (checkHasDuplicates(xOld, yOld, coordinateSystem) == true) {
      coordinateSystem.at(xOld).at(yOld).setValue(oldBlockValue);
      printf("found duplicates in the same row/column.\n");
      return;
    }
    if (checkHasRepeatWithinDefinedAreas(coordinateSystem) == true) {
      coordinateSystem.at(xOld).at(yOld).setValue(oldBlockValue);
      printf("found duplicates in the areas that it shouldn't be found.\n");
      return;
    }
  }
  
  const auto newBlock = coordinateSystem.at(nextX).at(nextY);
  for (int i = 0; i < newBlock.getLength(); ++i) {
    recurse(nextX, nextY, newBlock.getPossibleValues().at(i), coordinateSystem);
  }
  coordinateSystem.at(xOld).at(yOld).setValue(oldBlockValue);
}

void printBoard(const std::array<std::array<Block, 5>, 12>& system) {
  printf("\n");
  for (int i = 0; i < 4*12; ++i) {
    printf("-");
  }
  printf("\n");
  for (int y = 0; y < 5; ++y) {
    for (int x = 0; x < 12; ++x) {
      if (checkIsShaded(x, y) == true) {
        printf(" \033[47m \033[0m |");
      } else if (system.at(x).at(y).get() == 0) {
        printf("   |");
      } else {
        printf(" %d |", system.at(x).at(y).get());
      }
    }
    printf("\n");
    for (int i = 0; i < 4*12; ++i) {
      printf("-");
    }
    printf("\n");
  }
}

int main() {
  auto newCoordinate = coordinate;

  int xOld = 0;
  int yOld = 0;
  int initChoice = 0;

  recurse(xOld, yOld, initChoice, newCoordinate);

    printBoard(results);
  return 0;
}