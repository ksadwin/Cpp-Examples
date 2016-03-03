//
//  MazeWalker.h
//  MazeProject
//
//  Created by Kelly Sadwin and Shelby Cohen on 10/30/14.
//  Copyright (c) 2014 Kelly Sadwin and Shelby Cohen. All rights reserved.
//
//The purpose of this project is to construct a maze solver that finds the exit of a maze, and also tracks the unnecessary steps it took while finding this path.

#ifndef MAZE_WALKER_H
#define MAZE_WALKER_H

#include "Maze.h"
#include "Position.h"
#include <stack>
#include <vector>

class MazeWalker {
private:
    //creates a pointer to a Maze object named myMaze
    Maze* myMaze;
    stack<Position>* path;
    vector<Position>* badSteps;
    
public:
    //constructor
    MazeWalker(Maze* mazeIn);
    //destructor
    ~MazeWalker();
    
    bool walk();
    void toPrint();
};

#endif