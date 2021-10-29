/*******************************************************************/
/* FILE: GEtrail.cc                                                */
/* WRITTEN: 17 AUGUST 1998                                         */
/* AUTHOR: Michael O'Neill                                         */
/*          (michael.oneill@ul.ie|michael_o_neill@yahoo.com)       */
/* PURPOSE: Implements the GEtrail class as defined in GEtrail.hpp */
/* BUGS: Todate none                                               */
/* TODO:                                                           */
/*******************************************************************/
#include "GEtrail.hpp"
#include <fstream.h>

#include <iostream.h>

GEtrail::GEtrail()
{
  _current_X=0;
  _current_Y=0;
  _facing_current_X=1;
  _facing_current_Y=0;
}

int** GEtrail::trail()
{
return (int**)_working_trail;
}


// Read trail from file
void GEtrail::Readtrail (char* fname)
{
  int x=0, y=0;

  ifstream ifs (fname);
  if (!ifs) 
    cout << "GEtrail::Readtrail   " <<  "There is no trail data file" << endl;
  else
    {
      char ch='.';

      // Move to the correct position in the data file: The area below
      // hash.  The double '!' looks a bit odd, but is needed here as
      // one of it is an operator redefined by the stream class
      while (!(!ifs) && ch!='#') 
        ifs >> ch;
        
      while (y<GRID_HEIGHT)
        {
          // Read character and put it in the constant world member
          // variable
          ifs >> ch;
          if (ch!='.' && ch!='1' && ch!='0')
            cout << ch << "GEtrail::Readtrail    Wrong character in trail data file" << endl;
	  switch(ch)
	  {
	  case '.' :  
	  case '0' :_trail[x][y]=(int)0;_working_trail[x][y]=(int)0;break;
	  case '1' :_trail[x][y]=(int)1;_working_trail[x][y]=(int)1;break;
	  }
          // Increase index
          x++;
          if (x==GRID_WIDTH) 
            {
              y++;
              x=0;
            }
        }
      if (!ifs) 
        cout <<"GEtrail::Readtrail      Error reading trail data file" << endl;
    }

  // Count the number of available food.  Needed to evaluate the
  // standardised fitness.
  for (food=0, x=0; x<GRID_WIDTH; x++)
    for (y=0; y<GRID_HEIGHT; y++)
      food+=_trail[x][y]==FOOD;
}

GEant& GEtrail::getAnt()
{
  return ant;
}

// Reset ant and trail.
void GEtrail::reset (int e)
{
  for (int x=0; x<GRID_WIDTH; x++)
    for (int y=0; y<GRID_HEIGHT; y++)
      _working_trail[x][y]=_trail[x][y];

  ant.reset(e);

  _current_X=0; //Starting position
  _current_Y=0;
  _facing_current_X=1; //Set facing East
  _facing_current_Y=0;
}


void GEtrail::print_trail(ostream& os)
{
  for (int y=0; y<GRID_HEIGHT; y++)
    {
      for (int x=0; x<GRID_WIDTH; x++)
        {
          // Ant's current position?
          if (_current_X==x && _current_Y==y)
            os << 'A';
          else 
            os << _working_trail[x][y];
        }
      os << '\n';
    }
}


// Print the trail
ostream& operator << (ostream& os,GEtrail trail)
{
  for (int y=0; y<GRID_HEIGHT; y++)
    {
      for (int x=0; x<GRID_WIDTH; x++)
        {
          // Ant's current position?
          if (trail.current_X()==x && trail.current_Y()==y)
            os << 'A';
          else 
            os << trail.trail()[x][y];
        }
      os << '\n';
    }

  return os;
}

void GEtrail::right()
{ //turn ant right 90 degrees
  //cout << "ENTERING GEtrail::right()" << endl;
  getAnt().set_energy(getAnt().energy()-1);
  if(_facing_current_Y<0)
    {
      _facing_current_X=_current_X+1;
      _facing_current_Y=_current_Y;
    }
  else if(_facing_current_Y>GRID_HEIGHT)
    {
      _facing_current_X=_current_X-1;
      _facing_current_Y=_current_Y;
    }
  else if(_facing_current_X<0)
    {
      _facing_current_Y=_current_Y-1;
      _facing_current_X=_current_X;
    }
  else if(_facing_current_X>GRID_WIDTH)
    {
      _facing_current_Y=_current_Y+1;
      _facing_current_X=_current_X;
    }
  else if(_facing_current_Y<_current_Y)
    {
      _facing_current_X=_current_X+1;
      _facing_current_Y=_current_Y;
    }
  else if(_facing_current_Y>_current_Y)
    {
      _facing_current_X=_current_X-1;
      _facing_current_Y=_current_Y;
    }
  else if(_facing_current_X<_current_X)
    {
      _facing_current_X=_current_X;
      _facing_current_Y=_current_Y-1;
    }
  else if(_facing_current_X>_current_X)
    {
      _facing_current_X=_current_X;
      _facing_current_Y=_current_Y+1;
    }
  //cout << "LEAVING GEtrail::right()" << endl;
}

void GEtrail::left()
{ //turn ant left 90 degrees
  //cout << "ENTERING GEtrail::leftt()" << endl;
  getAnt().set_energy(getAnt().energy()-1); 
  if(_facing_current_Y<0)
    {
      _facing_current_X=_current_X-1;
      _facing_current_Y=_current_Y;
    }
  else if(_facing_current_Y>GRID_HEIGHT)
    {
      _facing_current_X=_current_X+1;
       _facing_current_Y=_current_Y;
    }
  else if(_facing_current_X<0)
    {
      _facing_current_Y=_current_Y+1;
       _facing_current_X=_current_X;
    }
  else if(_facing_current_X>GRID_WIDTH)
    {
      _facing_current_Y=_current_Y-1;
       _facing_current_X=_current_X;
    }
  else if(_facing_current_Y<_current_Y)
    {
      _facing_current_X=_current_X-1;
      _facing_current_Y=_current_Y;
    }
  else if(_facing_current_Y>_current_Y)
    {
      _facing_current_X=_current_X+1;
      _facing_current_Y=_current_Y;
    }
  else if(_facing_current_X<_current_X)
    {
      _facing_current_X=_current_X;
      _facing_current_Y=_current_Y+1;
    }
  else if(_facing_current_X>_current_X)
    {
      _facing_current_X=_current_X;
      _facing_current_Y=_current_Y-1;
    }
  //cout << "LEAVING GEtrail::left()" << endl;
}

void GEtrail::move()
{ //move ant forward one square
  //cout << "ENTERING GEtrail::move()" << endl;
  int old_current_X=0,old_current_Y=0;
  old_current_X=_current_X;
  old_current_Y=_current_Y;
  //cout << "Energy before move " << getAnt().energy() << endl;
  getAnt().set_energy(getAnt().energy()-1);
  //cout << "Energy after move " << getAnt().energy() << endl;
  //cout << "picked_up before move " << getAnt().picked_up() << endl;
  /*if a move is allowed then.....*/
  if( (_facing_current_X<GRID_WIDTH) && !(_facing_current_X<0) 
       && (_facing_current_Y<GRID_HEIGHT) && !(_facing_current_Y<0))
    { 
      //cout << "MOVE ALLOWED" << endl;
      _current_X=_facing_current_X;
      _current_Y=_facing_current_Y;
      // cout << "New position contains " << _working_trail[_current_X][_current_Y] << endl;
      if(_working_trail[_current_X][_current_Y]==1) 
	{
	  getAnt().set_picked_up(getAnt().picked_up()+1); 
	  _working_trail[_current_X][_current_Y]=0;
	  //cout << "picked_up " << getAnt().picked_up() << endl;
	  //cout << "New position now contains " << _working_trail[_current_X][_current_Y] << endl;
	}
      /*Increment _facing_current*/
      if(old_current_X<_current_X)
	{
	  _facing_current_X=_current_X+1;
	  _facing_current_Y=_current_Y;
	}
      if(old_current_X>_current_X)
	{
	  _facing_current_X=_current_X-1;
	  _facing_current_Y=_current_Y;
	}
      if(old_current_Y<_current_Y)
	{
	  _facing_current_Y=_current_Y+1;
	  _facing_current_X=_current_X;
	}
      if(old_current_Y>_current_Y)
	{
	  _facing_current_Y=_current_Y-1;
	  _facing_current_X=_current_X;
	}
      //      _working_trail[_current_X][_current_Y]=8;/*Plot ants course*/
    } 
  else
    {
      //#if 0
      //Cross to other side of grid...i.e. world becomes a sphere.
      //cout << "Crossing to other side...." << endl;
      //cout << "facing_X (" << _facing_current_X << ")" << endl;
      //cout << "facing_Y (" << _facing_current_Y << ")" << endl;
      //cout << "current_X (" << _current_X << ")" << endl;
      //cout << "current_Y (" << _current_Y << ")" << endl;
      if(_facing_current_X>GRID_WIDTH-1)
	{
	  //cout << "_facing_current_X>GRID_WIDTH" << endl;
	  _current_X=0;
	  _facing_current_X=1;
	}
      else if(_facing_current_X<0)
	{
	  //cout << "_facing_current_X<0" << endl;
	  _current_X=GRID_WIDTH-1;
	  _facing_current_X=GRID_WIDTH-2;
	}
      else
	{
	  //cout << "top to bottom or v.v." << endl;
	  if(_facing_current_Y>GRID_HEIGHT-1)
	    {
	      //cout << "_facing_current_Y>GRID_HEIGHT" << endl;
	      _current_Y=0;
	      _facing_current_Y=1;
	    }
	  else if(_facing_current_Y<0)
	    {
	      //cout << "_facing_current_Y<0" << endl;
	      _current_Y=GRID_HEIGHT-1;
	      _facing_current_Y=GRID_HEIGHT-2;
	    }
	}
      //cout << "New facing_X (" << _facing_current_X << ")" << endl;
      //cout << "New facing_Y (" << _facing_current_Y << ")" << endl;
      //cout << "New current_X (" << _current_X << ")" << endl;
      //cout << "New current_Y (" << _current_Y << ")" << endl;
      //cout << "New position contains " << _working_trail[_current_X][_current_Y] << endl;
      if(_working_trail[_current_X][_current_Y]==1) 
	{
	  getAnt().set_picked_up(getAnt().picked_up()+1); 
	  _working_trail[_current_X][_current_Y]=0;
	  //cout << "picked_up " << getAnt().picked_up() << endl;
	  //cout << "New position now contains " << _working_trail[_current_X][_current_Y] << endl;
	}
      //#endif
    }
  _working_trail[_current_X][_current_Y]=8;/*Plot ants course*/
  //cout << "picked_up after move " << getAnt().picked_up() << endl;
  //cout << "LEAVING GEtrail::move()" << endl;
}

int GEtrail::food_ahead()
{ //test if food in _facing square
  //cout << "ENTERING GEtrail::food_ahead()" << endl;
  int is_there=0;
  switch(_working_trail[_facing_current_X][_facing_current_Y])
    {
    case 0 :
      {
	//cout << "CASE 0" << endl;
	is_there=0;
	break;
      }
    case 1 :
      {
	//cout << "CASE 1" << endl;
	is_there=1;
	break;
      }
    case 8 :
      {
	//cout << "CASE 8" << endl;
	is_there=0;
	break;
      }
    default :
      {
	//#if 0
	//cout << "CASE DEFAULT--edge of grid" << endl;
	if(_facing_current_X>GRID_WIDTH-1)
	  {
	    //_current_X=0;
	    if(_working_trail[0][_current_Y]==1) is_there=1;
	    else is_there=0;
	  }
	else if(_facing_current_X<0)
	  {
	    //_current_X=GRID_WIDTH;
	    if(_working_trail[GRID_WIDTH-1][_current_Y]==1) is_there=1;
	    else is_there=0;
	  }
	else
	  {
	    if(_facing_current_Y>GRID_HEIGHT-1)
	      {
		//_current_Y=0;
		if(_working_trail[_current_X][0]==1) is_there=1;
		else is_there=0;
	      }
	    else if(_facing_current_Y<0)
	      {
		//_current_Y=GRID_HEIGHT;
		if(_working_trail[_current_X][GRID_HEIGHT-1]==1) is_there=1;
		else is_there=0;
	      }
	  }
	//#endif
	break;
      }
    }
  //cout << "LEAVING GEtrail::food_ahead() " << is_there << endl;
  return is_there;
}



int GEtrail::current_X()
{
  return _current_X;
}

int GEtrail::current_Y()
{
  return _current_Y;
}

int GEtrail::facing_current_X()
{
  return _facing_current_X;
}

int GEtrail::facing_current_Y()
{
  return _facing_current_Y;
}
