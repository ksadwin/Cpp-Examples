//
//  Position.cpp
//  MazeProject
//
//  Created by Toby Dragon on 11/7/14.
//  Copyright (c) 2014 Toby Dragon. All rights reserved.
//
#include <stdio.h>

#include "Position.h"

Position::Position(){
    this->x = -1;
    this->y = -1;
}

Position::Position( int x, int y){
    this->x = x;
    this->y = y;
}

int Position::getX()const{
    return x;
}

int Position::getY()const{
    return y;
}

Position* Position::getNextMoves() const{
    Position* moves = new Position[4];
    moves[0] = Position(x, y+1);
    moves[1] = Position(x+1, y);
    moves[2] = Position(x-1, y);
    moves[3] = Position(x, y-1);
    return moves;
}

bool Position::isAdjacent(Position toCheck) const{
    Position* nextMoves = getNextMoves();
    for (int i=0; i<4; i++){
        if (nextMoves[i] == toCheck){
            delete nextMoves;
            nextMoves = nullptr;
            return true;
        }
    }
    delete nextMoves;
    nextMoves = nullptr;
    return false;
}

bool Position::operator==(const Position& otherPos) const{
    return x==otherPos.x && y==otherPos.y;
}

bool Position::operator!=(const Position& otherPos) const{
    return ! (x==otherPos.x && y==otherPos.y);
}

ostream& operator<< (ostream &out, const Position& pos){
    out << "(" << pos.x << ", " << pos.y << ")";
    return out;
}


