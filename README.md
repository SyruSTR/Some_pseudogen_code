# Some_pseudogen_kod

## Overview

In this system, each number in the gencode corresponds to a specific robot action.
After executing an action,
the gencode determines the next step by jumping to position X.
The value of X depends on the type of object located in the corresponding area:

    1. another robot
    2. food
    3. wall
    4. empty space
## Robot actions

The symbol '->' indicates the completion of an action.
After execution, the next robot proceeds with its own action.

### Move ->
Moves the robot to the specified position if the move is valid.

|   | 1 |   |
|:-:|:-:|:-:|
| 4 | @ | 2 |
|   | 3 |   |

### Look at
Determines the robot's next action based on what it sees in its surroundings.

| 12 | 5 | 6 |
|:--:|:-:|:-:|
| 11 | @ | 7 |
| 10 | 9 | 8 |
### Kick at ->

Kicks the object in the target area, with effects varying based on the object's type:

    wall -5 -> 0
    robot 0 -> -5
    food 0 -> destroy food

| 20 | 13 | 14 |
|:--:|:--:|:--:|
| 19 | @  | 15 |
| 18 | 17 | 16 |
### Eat ->

Consumes an object in the target area:

    robot +5 -> -5
    food +5 -> destroy food

| 28 | 21 | 22 |
|:--:|:--:|:--:|
| 27 | @  | 23 |
| 26 | 25 | 24 |
### Rotate?
### Jump for non-programmable number
Numbers outside the predefined actions act as jump commands to a specific position in the gencode.