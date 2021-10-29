/*****************************************************************/
/* FILE: GEant.cc                                              */
/* WRITTEN: 17 AUGUST 1998                                       */
/* AUTHOR: Michael O'Neill                                       */
/*          (michael.oneill@ul.ie|michael_o_neill@yahoo.com)   */
/* PURPOSE: Implements the GEant class as defined in GEant.hpp */
/* BUGS: Todate none                                             */
/* TODO:                                                         */
/*****************************************************************/
#include "GEant.hpp"

GEant::GEant()
{
  set_energy(600);
  set_picked_up(0);
}

int GEant::picked_up()
{
  return _picked_up;
}

int GEant::energy()
{
  return _energy;
}

void GEant::set_energy(int e)
{
  _energy=e;
}

void GEant::set_picked_up(int p)
{
  _picked_up=p;
}

void GEant::reset(int e)
{
  set_energy(e);
  set_picked_up(0);
}







