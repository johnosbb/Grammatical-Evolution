// converter.hpp	A general purpose Simulated Annealing Class
//	                This version allows vector data

//                      (c) Copyright 2001, John O'Sullivan.
//                      Permission is granted by the author to use
//			this software for any application provided this
//			copyright notice is preserved.



#ifndef CONVERTER_HPP_
#define CONVERTER_HPP_ 1.4


#include <iostream.h>
#include <vector>



class converter
{
private:
  
  

public:
  converter(void);
  void process(double genes[] , int n, int binarystring[]);
  int convertdoubleToByte(double d, int binarystring[]);
  double round(double d);
  
};

#endif
























