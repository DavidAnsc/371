#include "Block.h"
#include <array>
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
std::array<std::array<std::array<Block, 5>, 12>, 1000> results {};

bool checkIsShaded(int x, int y) {
  if (
    (x != 0 && y != 1) &&
    (x != 1 && y != 1) &&
    (x != 1 && y != 3) &&
    (x != 2 && y != 3) &&
    (x != 4 && y != 1) &&
    (x != 4 && y != 2) &&
    (x != 4 && y != 3) &&
    (x != 6 && y != 1) &&
    (x != 7 && y != 1) &&
    (x != 7 && y != 3) &&
    (x != 8 && y != 3) &&
    (x != 9 && y != 3) &&
    (x != 10 && y != 3) &&
    (x != 10 && y != 1) &&
    (x != 11 && y != 1)
  ) {
    return false;
  }
  return true;
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
      printf("you've finished stage 0 compute.\n");
      // if (count == 1000) {
      //   printf("ERR\n");
      //   return;
      // }
      // results[count] = coordinateSystem;
      // ++count;
      return;
    }
    const int oldBlockValue = coordinateSystem.at(xOld).at(yOld).get();
    if (orgMarks.at(xOld).at(yOld) == 1 && checkIsShaded(xOld, yOld) == false) {
      coordinateSystem.at(xOld).at(yOld).setValue(choice);
      printf("Assigned value: [%d] to (%d, %d)\n", choice, xOld, yOld);
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
  recurse(0, 0, 0, 0, coordinate);
  return 0;
}