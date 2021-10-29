/*****************************************************************/
/* FILE: GEant.hpp                                               */
/* WRITTEN: 17 AUGUST 1998                                       */
/* AUTHOR: Michael O'Neill                                       */
/*          (michael.oneill@ul.ie|michael_o_neill@yahoo.com)     */
/* PURPOSE: Declares the GEant class as defined in GEant.cc      */
/*          Creates an ant which knows how much "energy" it has  */
/*          before it must pick up more food or it dies.         */
/*          GEant class is used in conjunction with the GEtrail  */
/*          class declared in GEtrail.hpp                        */
/* BUGS: Todate none                                             */
/* TODO:                                                         */
/*****************************************************************/

#ifndef _GEant_hpp
#define _GEant_hpp

class GEant
{
public:
  GEant();

  //Accessors
  int picked_up();
  int energy();
  void set_picked_up(int p);
  void set_energy(int e);
  void reset(int e);
private:
  int _energy; //time steps ant can move before dying
  int _picked_up; //pieces of food eaten
};

#endif



