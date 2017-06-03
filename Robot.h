#include<iostream>
#include <list>
#include <queue>
#include <stack>
#include<forward_list>
using namespace std;
#pragma once


class Location{
private:
	int row;
	int column;
	char s; // location is (b)lank, g or r
	bool isPassed;
public:
	Location();
	Location(int r, int c, char s);
	int* getCoordinate();
	char getType();
	void passing();
	bool isPassedhuh();
	Location operator=(const Location& other);
};

class Maze{
private:
	list<Location> locs;
	int dim;
public:
	Maze();
	Maze(string locs, int squareDim);
	Location start();
	list<Location> aroundLoc(Location here);
	void outMaze();
	bool updateLocation(Location l);
	
};

class Robot
{
private:
	queue<Location> posSolver;
	stack<Location> passedWay; 
	Maze map;
public:
	Robot();
	Robot(Maze m);
	~Robot(void);
	void changeMaze(Maze m);
	Maze getMaze();
	 void forward(Location l); //if posSolver is empty, than here location should be passed.
	void run();

};