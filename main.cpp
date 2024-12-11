
#include <iostream>
#include "robot.h"

int main(){
  std::cout << "Hello World!\n";

  Robot robot(20);

  for (int i = 0; i<10;i++) {
    robot.execute_action();
  }
  return 0;
}
