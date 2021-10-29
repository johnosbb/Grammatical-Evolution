/*******************************************************************/
/* FILE: GEtrail.hpp                                               */
/* WRITTEN: 17 AUGUST 1998                                         */
/* AUTHOR: Michael O'Neill                                         */
/*          (michael.oneill@ul.ie|michael_o_neill@yahoo.com)       */
/* PURPOSE: Declares the GEtrail class as defined in GEtrail.cc    */
/*          Creates a trail (2D int array) containing an ant.      */
/*          At present the ant is set to be in the uppermost left  */
/*          corner of the grid ([0][0]) facing East.               */
/*          To change trail a new trail file must be made, and the */
/*          GRID_WIDTH and GRID_HEIGHT values below altered.       */
/* BUGS: Todate none                                               */
/* TODO: (1)Generalise the ant so it can start at a position specified*/
/*       (2)Declare the input trail file name as a const here         */
/*******************************************************************/

#ifndef _GEtrail_hpp
#define _GEtrail_hpp

#include "GEant.hpp"
#include <iostream.h>

const int GRID_WIDTH=32;
const int GRID_HEIGHT=32;

const int EMPTY=0;
const int FOOD=1;
const int ANT=8;

//const int TRUE=1;
//const int FALSE=0;

class GEtrail
{
public:
  GEtrail();
  void Readtrail (char* fname);
  int** trail(); //returns the trail
  void print_trail(ostream& os);
  void reset (int e); //resets all the ants and trail variables

  void right();//turn ant right 90 degrees
  void left(); //turn ant left 90 degrees
  void move(); //move ant forward one square
  int food_ahead(); //test if food in facing square

  //Accessors
  GEant& getAnt();
  int current_X();
  int current_Y();
  int facing_current_X();
  int facing_current_Y();

private:
  int _trail[GRID_WIDTH][GRID_HEIGHT];
  int _working_trail[GRID_WIDTH][GRID_HEIGHT];
  GEant ant; //trail contains an ant
  int food; //no. pieces of food in trail
  int _current_X, _current_Y, _facing_current_X, _facing_current_Y;
};

#endif
