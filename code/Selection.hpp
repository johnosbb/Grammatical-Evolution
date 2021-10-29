
#ifndef Selection_h
#define Selection_h 1


#include <vector>
#include <list>
#include "Random.hpp"
#include "Configuration.hpp"
#include <iostream.h>
#include "defines.h"
#include "Genome.hpp"
#include "Results.hpp"
#include "Population.hpp"


typedef vector<double> gvector;



// The population object consists of a variable number of Genomes
// The size of the population can be set at runtime through a configuration file
// The object has the following  responsibilities
// crossover 
// Sorting itself into a required order and performing selection
// Any fitness scaling that is required
// we will need some method of allowing population pass back the necessary reporting parameters
// for now this may be the best genome and some indication of success
// When a population is initialised the operators it uses are defined
// This is preferable to having dedicated subclasses for ES, EP and GA populations
class Selection 
{
  
public:
  Selection();

  Selection(const Selection &right);

  ~Selection();
  
  Population select_first_n(int number,Population  & pop);
  Population  EP_selection(int number, Population &  pop);
  
  
protected:
  // Additional Protected Declarations
  
private:
  
  
  // Data Members for Associations
  
  // Additional Implementation Declarations
  
};


// Class Selection 





#endif
































