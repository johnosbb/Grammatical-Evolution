
#ifndef Crossover_h
#define Crossover_h 1


#include <vector>
#include <list>
#include "Random.hpp"
#include "Configuration.hpp"
#include "Population.hpp"
#include <iostream.h>
#include "defines.h"
#include "Genome.hpp"

typedef vector<double> gvector;




// This class implements various forms crossover
// the main interface to the class takes a parent population object
// this is an initialised object and an offspring population
// which may be empty
// A crossover type specifier is loaded from the configuration file

class Crossover 
{
  
public:
  Crossover();
  
  Crossover(const Crossover &right);
  
  ~Crossover();
  Crossover & operator=(const Crossover &right);
  void discrete_recombination(Population & parent_pop, Population & offspring_po);
  void run(Population & parent_pop, Population & offspring_pop, int type);
  
protected:
  // Additional Protected Declarations
  
private:
  
  // Data Members for Associations


  
};


// Class Crossover 








#endif
































