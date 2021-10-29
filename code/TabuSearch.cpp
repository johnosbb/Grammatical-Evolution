
// TabuSearch
#include "TabuSearch.hpp"
#include <iostream.h>
#include "defines.h"
#include <stdio.h>
#include "TabuConfiguration.hpp"
#include "TabuList.hpp"
#include <assert.h>
#include <algorithm>

typedef vector<double> gvector;
typedef vector<gvector> gvectorlist;

#ifndef DEBUG_
  #define DEBUG_
#endif




// Class TabuSearch 

TabuSearch::TabuSearch()
{
}

TabuSearch::TabuSearch(const TabuSearch &right)
{
}


TabuSearch::~TabuSearch()
{
}

// this contains the main algorithm for tabu  search
int TabuSearch::run_trial(int trial_num)
{
  reset_results();
  set_trial_result(FAILURE);
  TabuConfiguration * tabu_ptr;
  assert(tabu_ptr = static_cast< TabuConfiguration *> (c_ptr));
  if(tabu_ptr->get_tabu_tenure() != 0)
    tabu_list.set_default_tenure (tabu_ptr->get_tabu_tenure()); 
  
  capture_iterations = 0;
  if(c_ptr->capture_status == 1)
    {
      if(check_capture(trial_num))
	c_ptr->capture = 1;
      else
	c_ptr->capture = 0;
    }
  current_genome.evaluate(); 
  r_ptr->incr_objective_function_evaluations();
#ifdef DEBUG_ 
    cout << "DEBUG: current_genome: " << current_genome << " score " << current_genome.get_score() << endl;
#endif
  for(int i = 0; i < iterations;i++)
    { 
      if(get_trial_result() == SUCCESS)
	break;
      
      new_genome = current_genome;
      new_genome.generate_neighbourhood_genomes(&all_neighbour_genomes); // generate a neighbourhood for current genome
#ifdef DEBUG_ 
      cout << "\nDEBUG: Start of Iteration--------------------------------------- \n";
      cout << "DEBUG: current_genome " << current_genome << " score " << current_genome.get_score() << endl;
#endif
      create_neighbourhood(); // create a neighbourhood of Genome objects
#ifdef DEBUG_ 
      show_genome_neighbourhood();   // DEBUG
#endif
      // select the best Genome
      bool done = false;
      while(!done)
	{
	  best_genome = select_best_neighbour();
	  if(best_genome.get_score() == TARGET_SCORE)
	    {
	      cout << "DEBUG: YAHOO!!!!!!!!";
	      set_trial_result(SUCCESS);
	      done = true;
	    }
#ifdef DEBUG_              
          cout << "DEBUG: Initial best_genome selected: " << best_genome << " score " << best_genome.get_score() << endl;
	  // check his tabu status
          tabu_list.show_contents(); // DEBUG
#endif
	  if(tabu_list.check(best_genome))
	    {
#ifdef DEBUG_ 
	      cout << "DEBUG: best_genome was on tabulist\n";
#endif	      
	      if(best_genome >  current_genome)  // is he better than the current?
		{
		  current_genome = best_genome; // if he is make him the current
		  done = true;
#ifdef DEBUG_
		  cout << "DEBUG: Selected best_genome " << endl;
#endif
		}
	      else
		{
		  remove_best_neighbour();   // otherwise remove him from the neighbouurhood
#ifdef DEBUG_
		  cout << "DEBUG: removed best_neighbour from the neighbourhood " <<endl;
		  show_genome_neighbourhood(); // DEBUG
#endif
		}
	      
	    }
	  else
	    {
	      current_genome = best_genome;   // he is not tabu so accept him
	      tabu_list.add_genome(best_genome);  // add him to the tabu list
#ifdef DEBUG_
	      cout << "DEBUG: best_genome was not tabu we accepted him and added him to tabulist\n";
	      tabu_list.show_contents();  // DEBUG
#endif
	      done = true;
	    }
	} // while !done
      tabu_list.dcr_tabu_tenure();
#ifdef DEBUG_
      cout << "DEBUG: After decrement :";
      tabu_list.show_contents();
#endif
      tabu_list.purge();
#ifdef DEBUG_
      cout << "DEBUG: After purge :";
      tabu_list.show_contents();
#endif
      if(r_ptr->get_objective_function_evaluations() > c_ptr->maximum_evaluations)
	{
	  i = iterations;
	  cout << "Terminating trial having reached maximum evaluations of " << c_ptr->maximum_evaluations << endl;
	}  // if maximum_iterations
      
    }  // for iterations

#ifdef DEBUG_
  tabu_list.show_contents();
#endif

  r_ptr->set_final_score(current_genome.get_score());
  current_genome.get_genome_value(r_ptr->final_genome_value);
  current_genome.get_genome_value(r_ptr->best_genome_value);  
  return get_trial_result();
}
// Additional Declarations



int TabuSearch::selftest()
{
  return 1;
}

int TabuSearch::show_neighbourhood()
{
  gvectorlist::iterator iterl;
  iterl = all_neighbour_genomes.begin();

  while(iterl!= all_neighbour_genomes.end())
    {
      gvector::iterator iterv;
      iterv = (*iterl).begin();
      while(iterv!= (*iterl).end())
	{
	  cout << "," << *iterv;
	  iterv++;
        }
      cout << endl;
      iterl++;
    }
  return OKAY;
  
}


int TabuSearch::show_genome_neighbourhood()
{
  genomelist::iterator iterl;
  iterl = genome_neighbourhood.begin();
  cout << "Genome Neighbourhood:__________Delta_______Score_\n";
  while(iterl!= genome_neighbourhood.end())
    {
      cout <<  *(iterl) << "  " << (*iterl).get_score_delta() <<  "  " << (*iterl).get_score() << endl;
      iterl++;
    }
    cout << endl;
  return OKAY;
}


// creates a neighbourhood of Genomes, evaluates them and calculates the score delta 
int TabuSearch::create_neighbourhood()
{
  gvectorlist::iterator iterl;
  iterl = all_neighbour_genomes.begin();
  clear(&genome_neighbourhood);
  while(iterl!= all_neighbour_genomes.end())
    {
        new_genome.create(*iterl);
	new_genome.evaluate();
        r_ptr->incr_objective_function_evaluations();	
	if(c_ptr->capture == 1)
	    {
	      report_search_data(capture_iterations);
	    }
        capture_iterations+=1;
        new_genome.set_score_delta(current_genome.get_score());
        //cout << new_genome << " " << new_genome.get_score() << "  " << new_genome.get_score_delta() << endl;
	genome_neighbourhood.push_back(new_genome);
	iterl++;
    }
  //  sort(genome_neighbourhood.begin(),genome_neighbourhood.end(),scorecomp);
  sort(genome_neighbourhood.begin(),genome_neighbourhood.end());
  reverse(genome_neighbourhood.begin(),genome_neighbourhood.end());

  return OKAY;
  
}


Genome  TabuSearch::select_best_neighbour()
{
  genomelist::iterator iter;
  iter = genome_neighbourhood.begin();
  return *iter;
  
}



void TabuSearch::remove_best_neighbour()
{
  genomelist::iterator iter;
  iter = genome_neighbourhood.begin();
  genome_neighbourhood.erase(iter);
}



void  TabuSearch::clear(genomelist * g)
{
    g->erase(g->begin(),g->end());
    
}






