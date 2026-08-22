#include "Block.h"
#include <array>
#include <cstdio>
#include <iostream>
// stage: 0, 1, 2

static std::array<std::array<Block, 5>, 12> coordinate {{{Block(), Block(), Block({4, 5, 6}), Block({4, 5, 6}), Block()},
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

static std::array<std::array<int, 5>, 12> orgMarks {{{0, 0, 1, 1, 0}, 
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

void recurse(int xOld, int yOld, int choice, int stage, std::array<std::array<Block, 5>, 12> coordinateSystem) {
  if (stage == 0) {
    const Block tempBlock = coordinateSystem.at(xOld).at(yOld);

    if (tempBlock.get() != 0) {
      printf("there's already a value applied to (%d, %d)\n", xOld, yOld);
      return;
    }
    
    if (orgMarks.at(xOld).at(yOld) != 0) {
      coordinateSystem.at(xOld).at(yOld).setValue(choice);
      printf("Assigned value: [%d] to (%d, %d)\n", choice, xOld, yOld);
    }

    if (yOld == 4) {
      ++xOld;
      yOld = 0;
    } else {
      ++yOld;
    }

    if (xOld >= 12) {
      printf("you've finished stage 0 compute.\n");
      return;
    }


    for (int x = xOld; x < 12; ++x) {
      for (int y = yOld; y < 5; ++y) {
        if (x > static_cast<size_t>(std::numeric_limits<int>::max()) || y > static_cast<size_t>(std::numeric_limits<int>::max())) {
          printf("the value of x or y exceeds the integer range. continuing...");
          continue;
        }
        for (size_t i = 0; i < coordinateSystem.at(x).at(y).getLength(); ++i) {
          recurse(x, y, coordinateSystem.at(x).at(y).getPossibleValues().at(i), 0, coordinateSystem);
        }
      }
    }
  } else if (stage == 1) {
    
  } else if (stage == 2) {

  } else {
    printf("error stage\n");
  }
}

int main() {
  recurse(0, 0, 0, 0, coordinate);
  return 0;
}