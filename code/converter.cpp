// converter.c++   Implementation of a General Purpose Simulated Annealing Class
//                      (c) Copyright 2001, John O'Sullivan.
//                      Permission is granted by the author to use
//			this software for any application provided this
//			copyright notice is preserved.

#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <iostream.h>
#include "converter.hpp"
#include <assert.h>

converter::converter()
{
}


// takes an array of doubles and converts them to an int binary string 
// n is the number of genes
// binarystring must be n*8
void converter::process(double genes[] , int n , int binarystring[])
{
  int octave = 0;
  int tempbinary[8];
  for(int i = 0; i < n ; i ++)
    {
      assert(convertdoubleToByte(genes[i],tempbinary));
      for(int f=0;f < 8; f++)
	{
	  //cout << tempbinary[f] << " ";
	  binarystring[(f + octave)] = tempbinary[f];
	}
        octave += 8;
    }
}


int converter::convertdoubleToByte(double dd, int binarystring[])
{
  int  powerof2,p;
  powerof2 = 0;
  int i = 0;
  double d = round(dd);
  if (d > 255 || d < 0)
    {
      cout << "ERROR:  " << d << " is outside range \n";
    return 0;
    }
  
  p = 7;
  while(!(p < 0))
    {
        if( pow(2,p) < d || pow(2,p) == d)
	  {
	    binarystring[i++] = 1;
	    d = d - pow(2,p);
	  }
	else 
	  binarystring[i++] = 0;
	p = p - 1;
    }
  return 1;
  
}


// returns double rounded to the nearest whole number
double converter::round(double d)
{
  double integer_part;
  double fractional_part;
  fractional_part = modf(d,&integer_part);
  if(fractional_part > 0.50)
    integer_part += 1;
  //cout << "DEBUG: received " << d << "  split into " << integer_part << " and " << fractional_part << endl;
  return integer_part;
}
























































