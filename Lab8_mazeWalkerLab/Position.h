//
//  Position.h
//  MazeProject
//
//  Created by Toby Dragon on 11/6/14.
//  Copyright (c) 2014 Toby Dragon. All rights reserved.
//
#ifndef __MazeProject__Position__
#define __MazeProject__Position__

#include <stdio.h>
#include <iostream>

using namespace std;

class Position{
private:
    int x;
    int y;
    
    
public:
    
    Position();
    Position( int x, int y);
    
    int getX() const;
    int getY() const;
    
    //returns an array of all 4 moves that might be next
    //allocates array that needs to be deleted by user
    Position* getNextMoves() const;
    
    //returns true if the position parameter is "touching"
    //this position (could be reached in 1 move), otherwise false
    bool isAdjacent(Position toCheck) const;
    
    bool operator==(const Position& otherPos) const;
    bool operator!=(const Position& otherPos) const;
    
    friend ostream& operator<< (ostream &out, const Position& pos);
};

#endif /* defined(__MazeProject__Position__) */
