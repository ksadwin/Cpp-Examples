//
//  Maze.cpp
//  MazeProject
//
//  Created by Toby Dragon on 10/30/14.
//  Copyright (c) 2014 Toby Dragon. All rights reserved.
//
#include <stdio.h>
#include <iostream>
#include "Maze.h"

Maze::Maze(){
    this->maze_size_x = 40;
    this->maze_size_y = 25;
    start = Position(maze_size_x/2,maze_size_y/2);
    end = Position(maze_size_x-1, maze_size_y-3);
    morePotMoves = vector<Position>();
    
    maze = new bool*[maze_size_y];
    for (int y=0; y<maze_size_y; y++){
        maze[y] = new bool[maze_size_x];
        for (int x=0; x<maze_size_x; x++){
            maze[y][x] = false;
        }
    }
    makePaths(start);
}

Maze::~Maze(){
    for (int y=0; y<maze_size_y; y++){
        delete maze[y];
        maze[y] = nullptr;
    }
    delete maze;
    maze = nullptr;
}

Position Maze::getStart(){
    return start;
}

Position Maze::getEnd(){
    return end;
}

bool Maze::isValidLocation(Position toCheck){
    if (toCheck.getX()>0 && toCheck.getX()< maze_size_x && toCheck.getY()>0 && toCheck.getY()< maze_size_y){
        return maze[toCheck.getY()][toCheck.getX()];
    }
    else {
        return false;
    }
}

int Maze::getWidth(){
    return maze_size_x;
}

int Maze::getHeight(){
    return maze_size_y;
}

////////////////////  Private functions for creating the maze  /////////////////////////////

bool Maze::validNewLocation(Position oldLoc, Position newLoc){
    if ( (newLoc.getX() <=1 || newLoc.getX() >=maze_size_x-1 || newLoc.getY() <=1 || newLoc.getY() >=maze_size_y-1) && (newLoc.getX() != end.getX() && newLoc.getY() != end.getY()) ){
        return false;
    }
    else if (maze[newLoc.getY()][newLoc.getX()]){
        return false;
    }
    //if you're moving horizontally, you can't remove something that opens connections vertically
    else if (oldLoc.getX() != newLoc.getX()){
        int diff = (newLoc.getX() - oldLoc.getX())/2;
        int midX = oldLoc.getX()+diff;
        if (maze[oldLoc.getY()-1][midX] || maze[oldLoc.getY()+1][midX]){
            return false;
        }
        else {
            maze[oldLoc.getY()][midX] = true;
            return true;
        }
    }
    //if you're moving vertically, you can't remove something that opens connections horizontally
    else {
        int diff = (newLoc.getY() - oldLoc.getY())/2;
        int midY = oldLoc.getY()+diff;
        if (maze[midY][oldLoc.getX()-1] || maze[midY][oldLoc.getX()+1]){
            return false;
        }
        else {
            maze[midY][oldLoc.getX()] = true;
            return true;
        }
    }
}

Position Maze::chooseMove(Position oldPos){
    int direction = rand()%4;
    int tryCount=0;
    Position newLoc = Position(-1, -1);
    while (tryCount <4 && !validNewLocation(oldPos, newLoc)){
        if (direction == 0){
            newLoc =  Position(oldPos.getX()+2, oldPos.getY());
        }
        else if (direction == 1){
            newLoc = Position(oldPos.getX()-2, oldPos.getY());
        }
        else if (direction == 2){
            newLoc =  Position(oldPos.getX(), oldPos.getY()+2);
        }
        else {
            newLoc =  Position(oldPos.getX(), oldPos.getY()-2);
        }
        tryCount++;
        direction = (++direction)%4;
    }
    if (tryCount >=4){
        newLoc = Position(-1, -1);
    }
    else {
        morePotMoves.push_back(Position(newLoc.getX(), newLoc.getY()));
    }
    return newLoc;
}

void Maze::makePaths(Position startPos){
    Position oldLoc = startPos;
    maze[oldLoc.getY()][oldLoc.getX()] = true;
    
    Position newLoc = chooseMove(oldLoc);
    while(newLoc.getX() != -1){
        maze[newLoc.getY()][newLoc.getX()] = true;
        oldLoc = newLoc;
        newLoc = chooseMove(oldLoc);
    }
    if (!(maze[end.getY()][end.getX()]) && morePotMoves.size() > 0){
        int randomIndex = rand() % morePotMoves.size();
        Position randPos = morePotMoves[randomIndex];
        morePotMoves.erase(morePotMoves.begin()+randomIndex);
        makePaths(randPos);
    }
}

ostream& operator<< (ostream &out, Maze &toPrint){
    for (int y=0; y<toPrint.maze_size_y; y++){
        for (int x=0; x<toPrint.maze_size_x; x++){
            if (x == toPrint.start.getX() && y == toPrint.start.getY()){
                out << "S";
            }
            else if (x == toPrint.end.getX() && y == toPrint.end.getY() && toPrint.maze[y][x]){
                out << "E";
            }
            else if (toPrint.maze[y][x]){
                out << " ";
            }
            else {
                out << "#";
            }
        }
        out << endl;
    }
    out << endl;
    return out;
}
