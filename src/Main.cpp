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
      results[count] = coordinateSystem;
      ++count;
      printf("finished stage 0 compute num: [%d].\n", count);

      return;
    }
    const int oldBlockValue = coordinateSystem.at(xOld).at(yOld).get();

    
    if (orgMarks.at(xOld).at(yOld) == 1 && checkIsShaded(xOld, yOld) == false) {
      coordinateSystem.at(xOld).at(yOld).setValue(choice);
      printf("Assigned value: [%d] to (%d, %d)\n", choice, xOld, yOld);
    }
    if (checkHasDuplicates(xOld, yOld, coordinateSystem) == true) {
      coordinateSystem.at(xOld).at(yOld).setValue(oldBlockValue);
      printf("found duplicates in the same row/column.\n");
      return;
    }
    
    const auto newBlock = coordinateSystem.at(nextX).at(nextY);
    if (newBlock.getLength() == 10) {
      recurse(nextX, nextY, 0, 0, coordinateSystem);
      return;
    }
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

int main() {
  auto newCoordinate = coordinate;
  recurse(0, 0, 0, 0, newCoordinate);
  return 0;
}