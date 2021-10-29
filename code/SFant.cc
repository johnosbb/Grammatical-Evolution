/*****************************************************************/
/* FILE: SFant.cc                                                */
/* WRITTEN: 17 AUGUST 1998                                       */
/* AUTHOR: Michael O'Neill                                       */
/*          (michael.oneill@ul.ie|michael_o_neill@hotmail.com)   */
/* PURPOSE: Test program for GEant and GEtrail classes defined   */
/*          in GEant.hpp and GEtrail.hpp                         */
/* BUGS: Todate none                                             */
/* TODO:                                                         */
/*****************************************************************/
#include <iostream.h>
#include "GEtrail.hpp"

//#define _KOZA
#define _MINE

int main(void)
{
  cout << "Creating Ant trail containg an ant" << endl;
  GEtrail trail;
  cout << "Reading trail from file" << endl;
  trail.Readtrail("santafe.trl");
  cout << "Printing trail" << endl;
  trail.print_trail(cout);
  //Do something with ant
  cout << "Doing Trail......" << endl;
  cout << trail.getAnt().energy() << endl;
  while(trail.getAnt().energy()>0)
    {
      #ifdef _MINE 
if(trail.food_ahead())  {trail.move(); } else  {trail.left(); }
if(trail.fo
od_ahead())  {trail.move(); } else  {trail.move(); }
if(trail.food_ahead())
  {trail.left(); } else  {trail.right(); } if(trail.food_ahead())
{trail.m
ove(); } else  {trail.right(); } if(trail.food_ahead())
{trail.move(); } e
lse  {trail.left(); } 
#endif
#if 0
      //Generation (21)||Fitness (0.988764)||Picked Up (88)||energy used(611)..gives fitness 1
      if(trail.food_ahead()) trail.move();
      else {trail.left();}
      if(trail.food_ahead()) trail.move();
      else {trail.move();}
      if(trail.food_ahead()) trail.left();
      else {trail.left();}
      if(trail.food_ahead()) trail.right();
      else {trail.left();}
      if(trail.food_ahead()) trail.right();
      else {trail.left();}
      #endif
      #ifdef _KOZA
      if(trail.food_ahead()) trail.move();
      else 
	{
	  trail.left();
	  if(trail.food_ahead()) trail.move();
	  else trail.right();
	  trail.right();
	  trail.left();
	  trail.right();
	  if(trail.food_ahead()) trail.move();
	  else trail.left();
	  trail.move();
	}
      #endif
    }
  cout << "Picked Up (" << trail.getAnt().picked_up() << ")" << endl;
  trail.print_trail(cout);
  cout << "Finished trail" << endl;
  cout << "==========================================" << endl;
  cout << "Reseting trail and ant" << endl;
  trail.reset(200);
  cout << "Printing trail" << endl;
  trail.print_trail(cout);
  cout << "Bye test program finished" << endl;
}
