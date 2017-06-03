#include "Robot.h"
#include<iostream>
#include <sstream>
#include <fstream>
#include <list>
#include<queue>
using namespace std;

//<-- !! <--

//-->Location Class implementations
Location::Location(){
row = -1;
column=-1;
isPassed = false;
}
Location::Location(int r, int c, char se){
row = r;
column=c;
s = se;
isPassed = false;
}
int* Location::getCoordinate()
{
	int coordinate[2] = {row,column};
	return coordinate;
}
char Location::getType()
{
	return s;
}
void Location::passing(){
isPassed=true;	
}
bool Location::isPassedhuh(){
	return isPassed;
}
Location Location::operator=(const Location& other){
	this->column = other.column;
	this->row = other.row;
	this->isPassed = other.isPassed;
	this->s = other.s;
	return *this;
	}
//<-- !! <--

//-->Maze Class implementations
Maze::Maze(){
}
Maze::Maze(string loocs, int squareDim)
{
	//locs'u tek tek oku, her boþluk, R veya G gördüðünde Locationýn coordinatlarýný hesapla, Location oluþtur , listeye at
	dim = squareDim;
	int size =dim*dim;
	
	for(int i=0;i<loocs.size();i++)
	{
		if(loocs.at(i) == 'B'){
			Location l = Location((i/squareDim), (i%squareDim),'b');
			locs.push_front(l);
		}
		else if(loocs.at(i) == 'R' ||loocs.at(i) == 'r')
		{
			Location l = Location((i/squareDim), (i%squareDim),'r');
			locs.push_front(l);
		}
		else if(loocs.at(i) == 'G' ||loocs.at(i) == 'g')
		{
			Location l = Location((i/squareDim),( i%squareDim),'g');
			locs.push_front(l);
		}
	}
}
Location Maze::start()
{
	Location r;
	for (std::list<Location>::iterator it=locs.begin(); it != locs.end(); ++it)
		{if((*it).getType() =='r')
		{
			r = (*it);
			return r;
		}//if else not found, throw exception
	}
	//throw exception("r yok");
}
list<Location> Maze::aroundLoc(Location l)
{
	list<Location> loc;
	Location ttt;
	int r, c , i=0;
	r = l.getCoordinate()[0];
	c = l.getCoordinate()[1];
	for (std::list<Location>::iterator it=locs.begin(); it != locs.end(); ++it)
		{
			int itr =(*it).getCoordinate()[0], itc =(*it).getCoordinate()[1];
			if(itr == r  )
			{
				if(itc == c-1 || itc==c+1){
				ttt = (*it);
				loc.push_front(ttt);

				}
			}
			else if( itc == c)
			{
				if(itr == r-1 || itr==r+1)
				{
				ttt = (*it);
				loc.push_front(ttt);

				}
			}
		}
	return loc;
}
bool Maze::updateLocation(Location l)
{
	std::list<Location>::iterator it = locs.begin();
	Location mine;
	while( it != locs.end()){
		mine = (*it);
		int r = mine.getCoordinate()[0], c = mine.getCoordinate()[1];
		int rl = l.getCoordinate()[0], cl = l.getCoordinate()[1];
		if(rl == r && cl == c){
			*it = l;
			return true;
			}
	it++;
	}
	return false;
}
void Maze::outMaze()
{
	ofstream output;
	output.open("MazeOut.txt");
	string str = "", nwS ="";
	int r,c,pos;
	Location l;
	for(int i=0;i<dim*dim;i++)
		 str+= "X";
	for(std::list<Location>::iterator it = locs.begin(); it !=locs.end();it++){
		l = (*it);
		r = l.getCoordinate()[0];
		c = l.getCoordinate()[1];
		pos = r*dim +c;
		switch (l.getType())
		{
		case 'b':
			if(l.isPassedhuh()) nwS = "*";
			else nwS=" ";
			break;
		case 'g':
			nwS = "G";
			break;
		case 'r':
			nwS="R";
			break;
		default:
			break;
		}
		str.replace(pos,1,nwS);
	}
	for (int var = 0; var < dim; ++var) {
				string token = str.substr(var*dim, dim);
				output<<token<<endl;
	}
    output.close();

}
//<-- !! <--
//-->  Robot class implementations
Robot::Robot()
{
}
Robot::Robot(Maze m)
{
	map = m;
}
Robot::~Robot(void)
{
}
void Robot::changeMaze(Maze m){
	map = m;
}
Maze Robot::getMaze(){

	return map;
}
 void Robot::forward(Location l)
{
	if(posSolver.empty() ){
		l.passing();
		map.updateLocation(l);
	 }
}
 //main algorithm that you want, sir
void Robot::run()
{
//maze den start ý alacak, forward edecek, komsularýný alacak, queue ye atacak, queue dekini alacak forward edecek, komsularýný alacak queue ye atacak,...  
	Location here = map.start();
	list<Location> ls;
	while(here.getType() != 'g'){
	forward(here);
	ls  = map.aroundLoc(here);
	int i = 0;
	while(ls.size()>0){
		Location l = ls.front();
		ls.pop_front();
		if(!(l.isPassedhuh()))
		posSolver.push(l);
		
	}
	here = posSolver.front();
	posSolver.pop();
	}

	map.outMaze();
	cout<<"Dosya çiktisi alinmistir"<<endl;
}

int main(){

	int request=0;
   ifstream input;
   string mazeTest, maze;
   mazeTest="";
   maze ="";

   int squareDim;
   

          input.open("Maze.txt");
          string str;
          while(true){
          input>>str;
          if(input.eof())
          {
          break;}
          mazeTest=mazeTest+str;
          }
          input.close();
		  stringstream(mazeTest.substr(0,1))>>squareDim;
		  maze=mazeTest.substr(1,squareDim*squareDim);
		  cout<<maze<<endl;

		  Maze map = Maze(maze,squareDim);
		  Robot rob = Robot(map);
		  rob.run();
     

	system("pause");
	return(0);
}

