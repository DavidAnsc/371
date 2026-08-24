#include "Block.h"
#include <array>
#include <set>
#include <cstdio>
#include <iostream>
// stage: 0, 1, 2

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
std::array<std::array<std::array<Block, 5>, 12>, 50000> results {};

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

bool checkHasRepeatWithinDefinedAreas(const std::array<std::array<Block, 5>, 12>& system) {
  std::array<std::array<int, 2>, 3> area1 {{{0, 2}, {0, 3}, {1, 2}}};
  std::array<std::array<int, 2>, 3> area2 {{{4, 0}, {5, 0}, {5, 1}}};
  std::array<std::array<int, 2>, 3> area3 {{{9, 1}, {9, 2}, {10, 2}}};
  if (checkHasRepeatWithinArea(system, area1) || checkHasRepeatWithinArea(system, area2) || checkHasRepeatWithinArea(system, area3)) {
    return true;
  }
  return false;
}

bool checkSums(const int xAxis, const int yAxis, const std::array<std::array<Block, 5>, 12>& system) {
  const int otherY = (yAxis == 4) ? 3 : yAxis + 1;
  const int otherX = (xAxis == 11) ? 10 : xAxis + 1;

  int xAxisSum {};
  int xAxisSumOther {};
  int yAxisSum {};
  int yAxisSumOther {};

  for (int xA = 0; xA < 12; ++xA) {
    xAxisSum += system.at(xA).at(yAxis).get();
    xAxisSumOther += system.at(xA).at(otherY).get();
  }

  for (int yA = 0; yA < 5; ++yA) {
    yAxisSum += system.at(xAxis).at(yA).get();
    yAxisSumOther += system.at(otherX).at(yA).get();
  }

  return xAxisSum == xAxisSumOther && yAxisSum == yAxisSumOther;
}

void recurse(int xOld, int yOld, int choice, int stage, std::array<std::array<Block, 5>, 12>& coordinateSystem) {
  if (stage == 0) {
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
      if (checkSums(xOld, yOld, coordinateSystem) == false) {
        printf("the row/col sums don't add up. DELETED BOARD\n");
        return;
      }

      results[count] = coordinateSystem;
      ++count;
      printf("finished stage 0 compute num: [%d].\n", count);

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
      recurse(nextX, nextY, newBlock.getPossibleValues().at(i), 0, coordinateSystem);
    }
    coordinateSystem.at(xOld).at(yOld).setValue(oldBlockValue);
  } else if (stage == 1) {
    
  } else if (stage == 2) {

  } else {
    printf("error stage\n");
  }
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
  recurse(0, 0, 0, 0, newCoordinate);

  for (int i = 0; i < 5; ++i) {
    printBoard(results[i]);
  }
  return 0;
}