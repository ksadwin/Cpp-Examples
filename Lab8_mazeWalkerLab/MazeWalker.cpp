//
//  MazeWalker.cpp
//  MazeProject
//
//  Created by Kelly Sadwin and Shelby Cohen on 10/30/14.
//  Copyright (c) 2014 Kelly Sadwin and Shelby Cohen. All rights reserved.
//
//The purpose of this project is to construct a maze solver that finds the exit of a maze, and also tracks the unnecessary steps it took while finding this path.

#include <stdio.h>
#include <iostream>
#include "MazeWalker.h"

MazeWalker::MazeWalker(Maze* mazeIn) {
    //implements all of the data members
    myMaze = mazeIn;
    path = new stack < Position > ;
    //uses getStart function in Maze to insert item in our stack(named path)
    path->push(myMaze->getStart());
    //initializes vector badSteps
    badSteps = new vector < Position > ;
}

MazeWalker::~MazeWalker() {
    //cleans up memory for both our stack and vector used
    //need to clean up because both use dynamic memory
    delete path;
    path = nullptr;
    delete badSteps;
    badSteps = nullptr;
}


bool MazeWalker::walk() {
    //accesses next element and uses the array that getNextMoves() returns to loop
    Position* moves = path->top().getNextMoves();
    for (int i = 0; i < 4; i++) {
        bool dontGoBackwards = true;
        //uses a copy of a stack of Positions that has a pointer to the already created stack
        stack<Position> copyPath = *path;
        //when the copy of the stack is not empty and dontGoBackwards is true...
        //access the next element of the copied stack and set dontGoBackwards to false
        while (!copyPath.empty() && dontGoBackwards) {
            if (moves[i] == copyPath.top()) {
                dontGoBackwards = false;
            }
            //remove top element of the copied stack
            copyPath.pop();
        }
        //if that spot is the end off the maze then clean up memory and leave function with value true
        if (moves[i] == myMaze->getEnd()) {
            delete[] moves;
            return true;
        }
        //if spot is not the end then check if its a validlocation
        //and use iterator to beginning and to end with creates vector badSteps
        //and dontGoBackwards is true
        else if (myMaze->isValidLocation(moves[i]) && find(badSteps->begin(), badSteps->end(), moves[i]) == badSteps->end() && dontGoBackwards) {
            //inserts spot to stack
            path->push(moves[i]);
            //if the maze is not solved
            //push back the top element of the stack to the vector badSteps
            //remove top element of the stack with pop
            if (!walk()){
                badSteps->push_back(path->top());
                path->pop();
            }
            else {
                return walk();
            }
        }
    }
    //clean up memory
    delete[] moves;
    //return false if maze is not solved
    return false;
}

void MazeWalker::toPrint() {
    if (walk()){
        cout << "Maze solved!" << endl << endl;
    }
    else {
        cout << "Maze could not be solved :(" << endl << endl;
    }
    for (int y = 0; y<myMaze->getHeight(); y++){
        for (int x = 0; x<myMaze->getWidth(); x++){
            Position p = Position(x, y);
            if (p == myMaze->getStart()){
                printf("S");
            }
            else if (p == myMaze->getEnd()){
                printf("E");
            }
            else if (myMaze->isValidLocation(p)){
                //to find position in stack
                bool found = false;
                stack<Position> copyPath = *path;
                while (!copyPath.empty() && !found) {
                    if (p == copyPath.top()) {
                        found = true;
                    }
                    copyPath.pop();
                }
                if (found){
                    cout << ".";
                }
                else if (find(badSteps->begin(), badSteps->end(), p) != badSteps->end()){
                    cout << "x";
                }
                else{
                    cout << " ";
                }
            }
            else {
                cout << "#";
            }
        }
        cout << endl;
    }
    cout << endl << endl;
}