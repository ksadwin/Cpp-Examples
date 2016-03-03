//
//  main.cpp
//  Lab8_mazeWalkerLab
//
//  Created by S Cohen on 11/14/14.
//  Copyright (c) 2014 S Cohen. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "Maze.h"
#include "MazeWalker.h"
#include "Position.h"

using namespace std;

int main()
{
    srand(int(time(0)));
    Maze* myMaze = new Maze();
    MazeWalker* myMazeWalker = new MazeWalker(myMaze);
    myMazeWalker->toPrint();
    
    
    delete myMazeWalker;
    myMazeWalker = nullptr;
    return 0;
}

