#include "defines.h"
#include <math.h>
#include "EpConfiguration.hpp"
#include <assert.h>
#include "Crossover.hpp"
#include "Mutation.hpp"
#include "Selection.hpp"


// EvolutionaryProgramming
#include "EvolutionaryProgramming.hpp"


// Class EvolutionaryProgramming 



EvolutionaryProgramming::EvolutionaryProgramming()
{
}

EvolutionaryProgramming::EvolutionaryProgramming(const EvolutionaryProgramming &right)
{
}


EvolutionaryProgramming::~EvolutionaryProgramming()
{
}



// The setup trial method will need to be overwritten in the metaheuristic
// base class. Set-up will now largely focus on the set-up of the population
// based on parameters based in the configuration file
// setup should be able to take an initial population , this will probably be in a file
// the configuration file will contain the name of the file

int EvolutionaryProgramming::setup_trial()
{
  EpConfiguration * epc_ptr;
  assert(epc_ptr = static_cast< EpConfiguration *> (c_ptr));
  set_iterations(epc_ptr->iterations);
  search_progress_indicator = 0;
  current_genome.set_max_length(epc_ptr->maximum_genome_length);
  current_genome.set_max_gene_value(epc_ptr->max_gene_value);
  current_genome.create();     // a random genome
  current_genome.configure(epc_ptr->wrap,epc_ptr->ge_report,epc_ptr->mutation_selector,epc_ptr->mutation_rate,epc_ptr->style,epc_ptr->mutation_rate_range);

  best_genome.set_max_length(epc_ptr->maximum_genome_length);
  best_genome.set_max_gene_value(epc_ptr->max_gene_value);
  best_genome.configure(epc_ptr->wrap,epc_ptr->ge_report,epc_ptr->mutation_selector,epc_ptr->mutation_rate,epc_ptr->style,epc_ptr->mutation_rate_range);

  if(!epc_ptr->initial_length == 0) // if an initial length is supplied
    {
      parent_population.create(epc_ptr->parent_population_size,epc_ptr->maximum_genome_length,epc_ptr->max_gene_value,epc_ptr->initial_length,epc_ptr->initial_length_variation_range,epc_ptr->std_deviation);
    }
  else if(!strcmp(epc_ptr->initial_genome_value,"empty")==0) // if an initial genome value is supplied  
    {
      parent_population.create(epc_ptr->parent_population_size,epc_ptr->maximum_genome_length,epc_ptr->max_gene_value,epc_ptr->initial_genome_value);
    }
  else if(!strcmp(epc_ptr->initial_population_config,"empty")==0) // if an initial population file is supplied  
    {
      parent_population.create(epc_ptr->maximum_genome_length,epc_ptr->max_gene_value,epc_ptr->initial_population_config,epc_ptr->parent_population_size);
    }
  else                              // no explicit configuration given , generating
    {
      parent_population.create(epc_ptr->parent_population_size,epc_ptr->maximum_genome_length,epc_ptr->max_gene_value);
    }
  parent_population.configure(epc_ptr);
  parent_population.set_std_deviation(epc_ptr->std_deviation);

  return 1;
  
}


int EvolutionaryProgramming::run_trial(int trial_num)
{
  reset_results();
  EpConfiguration * epc_ptr;
  assert(epc_ptr = static_cast< EpConfiguration *> (c_ptr));
  set_trial_result(FAILURE);
  Selection s;
  if(epc_ptr->capture_status == 1)
    {
      if(check_capture(trial_num))
	epc_ptr->capture = 1;
      else
	epc_ptr->capture = 0;
    }
  bool done = false;
  capture_iterations = 0;
  best_genome = current_genome;  //this is not ideal , current genome is not relevant at this point
  for(int i = 1; i < iterations;i++)
    {
      if(c_ptr->capture == 1)
	{
	  report_search_data(capture_iterations); // this will need to be revised , suggest capture iteration, generation reference we will need to gather data from the population object , we will need to override the base class here, the new method will need to report each genome , its score , the parents of the individual as a genome string and an ID. a list of the operations that were performed o it, for example 
      // was it nutated , was it duplicated etc.
	}
      capture_iterations += 1; // this may need to change depending on the size of population

	    //if(r_ptr->get_objective_function_evaluations() > c_ptr->maximum_evaluations)
	    //{
      offspring_population = parent_population;
      
      offspring_population.mutate();
      if(c_ptr->ge_report == 3)
	{
	  cout << "Iteration " << i << "......................\n";
	  cout << "Parent Population  genomes" << endl;
	  cout  << parent_population << endl;
	  cout << "Parent Population Strategy Variables " << endl;
	  parent_population.show_stdev();
	  cout << "Offspring Population  " << endl;
	  cout <<  offspring_population << endl;
	  cout << "Offspring Population Strategy Variables " << endl;
	  offspring_population.show_stdev();
	  cout << " ------------- end of record ---------------------\n\n";
	}
      combined_population = parent_population + offspring_population;
      r_ptr->incr_objective_function_evaluations((epc_ptr->parent_population_size * 2));
      
      if(combined_population.evaluate(TARGET_SCORE))  // this should terminate on a success
	{
	  cout << "DEBUG: YAHOO!!!!!!!!";
	  set_trial_result(SUCCESS);
	  combined_population.get_statistics(r_ptr);
	  current_genome = combined_population.sort_descending(); // get the highest scoring genome
	  best_genome = current_genome;
	  done = true;
	  break;
	} 
      current_genome = combined_population.sort_descending(); // get the highest scoring genome
      if(current_genome > best_genome)
	{
	  best_genome = current_genome;
	  cout << "DEBUG: Best Genome : " << best_genome << "  " << best_genome.get_score() << endl;
	}
      
      // create a new parent population based on the first n genomes with the highest number of wins 
      parent_population = s.EP_selection(epc_ptr->parent_population_size,combined_population);  
      //parent_population.show();  
     //cout << "Terminating trial having reached maximum objective function evaluations of " << c_ptr->maximum_evaluations << endl;
     //}  // if maximum_iteration    
     
     
     //}  // generations loop
     
     
     
    }  // while !done
  r_ptr->set_average_stdev_value(0); 
  r_ptr->set_final_score(current_genome.get_score());
  current_genome.get_genome_value(r_ptr->final_genome_value);
  best_genome.get_genome_value(r_ptr->best_genome_value);  
  r_ptr->set_best_score(best_genome.get_score());
  return get_trial_result();
}


 


int EvolutionaryProgramming::selftest()
{
  return 1;
}

// overrides base class method
void EvolutionaryProgramming::report_search_data(int iteration_num)
{
  capture_data_file << "Iteration number: " << iteration_num << "   \n" ;
  capture_data_file << "Population:\n";
  capture_data_file << parent_population;
  capture_data_file << "Strategy Variables:\n";
  parent_population.stream_stdev(capture_data_file);
  capture_data_file << "Average Mutation Rate: "; 
  capture_data_file << parent_population.get_avg_mutation_rate() << "\n";
  capture_data_file << "Average Mutation Bias: "; 
  capture_data_file << parent_population.get_avg_mutation_bias() << "\n";

  capture_data_file << "----------------------------------------------------------------\n";
}



// Additional Declarations
























