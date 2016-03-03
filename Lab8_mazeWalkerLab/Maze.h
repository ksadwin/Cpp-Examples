//
//  Maze.h
//  MazeProject
//
//  Created by Toby Dragon on 10/30/14.
//  Copyright (c) 2014 Toby Dragon. All rights reserved.
//

#ifndef __MazeProject__Maze__
#define __MazeProject__Maze__

#include <iostream>
#include <vector>
#include "Position.h"

using namespace std;

class Maze{
private:
    int maze_size_x;
    int maze_size_y;
    bool** maze;
    Position start;
    Position end;
    vector<Position> morePotMoves;
    
    void makePaths(Position startPos);
    bool validNewLocation(Position oldLoc, Position newLoc);
    Position chooseMove(Position oldPos);
    
public:
    //create a new random maze
    //must seed the random generator before calling
    //to get a random maze
    Maze();
    
    ~Maze();
    
    Position getStart();
    Position getEnd();
    int getWidth();
    int getHeight();
    
    //checks if any given position is valid
    bool isValidLocation(Position toCheck);
    
    friend ostream& operator<< (ostream &out, Maze &toPrint);
};

#endif /* defined(__MazeProject__Maze__) */
