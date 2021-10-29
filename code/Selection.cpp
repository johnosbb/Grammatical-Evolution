// Genome
#include "Selection.hpp"
#include "defines.h"
#include "string.h"
#include "Random.hpp"
#include "converter.hpp"
#include "ge.hpp"
#include <string.h>
#include <stdio.h>
#include <iostream.h>
#include <vector>
#include <assert.h>
#include "Configuration.hpp"
#include "Results.hpp"
#include "Population.hpp"



// Class Selection 


Selection::Selection()
  
{
}

Selection::Selection(const Selection &right)
{
  
}

// creates a population of a given size. Genomes are created with the initial value supplied , the value of the individual genes are the values given




/*
void  Selection::clear(gvectorlist * g)
{
    g->erase(g->begin(),g->end());
    
}

*/


Selection::~Selection()
{
}

// selects the first n individuals from the population
// if the population has been sorted descending these will be the best n individuals
Population  Selection::select_first_n(int number, Population &  pop)
{
  Population p;
  int n = 0;
  genomelist::iterator iter;
  iter = pop.the_population.begin();
  if(number > pop.get_current_size())
    number = pop.get_current_size();
  while(n < number)
    {
      p.add_genome(*iter); 
      iter++;
      n++;
    }
  return p;
  
}

// returns a population of size number
// selection is based on q pairwise trials
// the number of wins for each individual is recorded
// the top number genomes with the highest wins are returned

Population  Selection::EP_selection(int number, Population &  pop)
{
  // for each member of the population
  Population p;
  
  genomelist::iterator iter;
  iter = pop.the_population.begin();
 while(iter !=  pop.the_population.end())
   {
     (*iter).set_number_of_wins (0);
     for(int i =0; i < 10; i++) // need to change this so that it can be set
       {
	 Genome opponent = pop.get_random_genome();
	 if((*iter).get_score() > opponent.get_score())
	   (*iter).incr_number_of_wins();
       }
     iter++;
     
   }
 pop.sort_using_wins();
 p = select_first_n(number,pop);
 return p;
 
}




































