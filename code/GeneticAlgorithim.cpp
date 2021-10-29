#include "defines.h"
#include <math.h>
#include "GaConfiguration.hpp"
#include <assert.h>


// GeneticAlgorithm
#include "GeneticAlgorithm.hpp"


// Class GeneticAlgorithm 



GeneticAlgorithm::GeneticAlgorithm()
      : num_of_accepts(0),
        num_of_rejects(0),
        min_temperature(0.01),
        current_temperature(0),
        temp_change_rate(0.95),
        init_temperature(0.7),
        probability_threshold(1),
        boltzman_constant(1)
{
}

GeneticAlgorithm::GeneticAlgorithm(const GeneticAlgorithm &right)
      : num_of_accepts(0),
        num_of_rejects(0),
        min_temperature(0.01),
        current_temperature(0),
        temp_change_rate(0.95),
        init_temperature(0.7),
        probability_threshold(1),
        boltzman_constant(1)
{
}


GeneticAlgorithm::~GeneticAlgorithm()
{
}



// The setup trial method will need to be overwritten in the metaheuristic
// base class. Set-up will now largely focus on the set-up of the population
// based on parameters based in the configuration file
// setup should be able to take an initial population , this will probably be in a file
// the configuration file will contain the name of the file


int GeneticAlgorithm::run_trial(int trial_num)
{
  reset_results();
  GaConfiguration * sac_ptr;
  assert(sac_ptr = static_cast< GaConfiguration *> (c_ptr));
  if(sac_ptr->get_init_temperature() != 0)
    set_init_temperature (sac_ptr->get_init_temperature());
  if(sac_ptr->get_temp_change_rate() != 0)
    set_temp_change_rate (sac_ptr->get_temp_change_rate());
  set_trial_result(FAILURE);
  if(c_ptr->capture_status == 1)
    {
      if(check_capture(trial_num))
	c_ptr->capture = 1;
      else
	c_ptr->capture = 0;
    }
  bool done = false;
  new_population.generate(); //calculates the fitness of all members of the population
  new_population.evaluate(); // this includes mutation , selection and crossover as defined in the config file
  r_ptr->incr_objective_function_evaluations(); // this should be incremented by the size of the population, need a new method here.
  capture_iterations = 0;
  while(!done)
    {
      for(int i = 1; i < generations;i++)
	{
	  new_population.evolve(); // evolving includes 
          if(new_population.evaluate(TARGET_SCORE))  // this should terminate on a success
	    {
	      cout << "DEBUG: YAHOO!!!!!!!!";
	      set_trial_result(SUCCESS);
	      done = true;
              break;
	    } 
     
	  if(c_ptr->capture == 1)
	    {
	      report_search_data(capture_iterations,current_temperature,random_probability,acceptance_probability); // this will need to be revised , suggest capture iteration, generation reference we will need to gather data from the population object , we will need to override the base class here, the new method will need to report each genome , its score , the parents of the individual as a genome string and an ID. a list of the operations that were performed o it, for example 
	      // was it nutated , was it duplicated etc.
	    }
          capture_iterations += 1; // this may need to change depending on the size of population
	  if(c_ptr->ge_report == 1)
	    {
	      cout << i << "  " << current_population << endl;
	      cout << " ------------- end of record ---------------------\n\n";
	    }
	  if(current_population.get_best_score() == TARGET_SCORE) // the population object will need to determine this
	    {
	      cout << "DEBUG: YAHOO!!!!!!!!";
	      set_trial_result(SUCCESS);
	      done = true;
              break;
	      
	    }      
      if(r_ptr->get_objective_function_evaluations() > c_ptr->maximum_evaluations)
	{
	  done = true;
	  cout << "Terminating trial having reached maximum objective function evaluations of " << c_ptr->maximum_evaluations << endl;
	  break;
	}  // if maximum_iteration    
	
	  
	}  // generations loop

  
      
    }  // while !done
  r_ptr->set_average_genome_size(accumulated_genome_size/capture_iterations); 
  r_ptr->set_final_score(current_genome.get_score());
  current_genome.get_genome_value(r_ptr->final_genome_value);
  best_genome.get_genome_value(r_ptr->best_genome_value);  
  r_ptr->set_best_score(best_genome.get_score());
  return get_trial_result();
}


void GeneticAlgorithm::conditionally_accept(void)
{
  double delta = current_genome.get_score() - new_genome.get_score();
  acceptance_probability  = exp( -delta/(boltzman_constant * current_temperature));
  Random r;
  random_probability = (double)(r.randomintrange(probability_threshold,101))/100;
  if( acceptance_probability >= random_probability)
    {
      current_genome = new_genome;
      num_of_accepts++;
    }
  else
    num_of_rejects++;
  
}
 




int GeneticAlgorithm::selftest()
{
  return 1;
}

// Additional Declarations
























