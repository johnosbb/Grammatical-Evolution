// Genome
#include "Crossover.hpp"
#include "defines.h"
#include "string.h"
#include "Random.hpp"
#include "converter.hpp"
#include "Population.hpp"
#include "ge.hpp"
#include <string.h>
#include <stdio.h>
#include <iostream.h>
#include <vector>
#include <assert.h>
#include "Configuration.hpp"


// Class Crossover 


Crossover::Crossover()
  
{
}

Crossover::Crossover(const Crossover &right)
{

  
}

void Crossover::run(Population & parent_pop, Population & offspring_pop, int type)
{

  cout << "------------------------------------------------\n";
  cout << "Crossover type " << type << " \n";
  parent_pop.show();
  offspring_pop.show();
  if(type == 1)
    discrete_recombination(parent_pop, offspring_pop);
  
}



Crossover::~Crossover()
{
}





Crossover & Crossover::operator=(const Crossover &right)
{
  return *this;  
}



void  Crossover::discrete_recombination(Population & parent_pop, Population & offspring_pop)
{

  
}




















































