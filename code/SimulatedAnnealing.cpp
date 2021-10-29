#include "defines.h"
#include <math.h>
#include "SaConfiguration.hpp"
#include <assert.h>


// SimulatedAnnealing
#include "SimulatedAnnealing.hpp"


// Class SimulatedAnnealing 



SimulatedAnnealing::SimulatedAnnealing()
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

SimulatedAnnealing::SimulatedAnnealing(const SimulatedAnnealing &right)
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


SimulatedAnnealing::~SimulatedAnnealing()
{
}


int SimulatedAnnealing::run_trial(int trial_num)
{
  reset_results();
  SaConfiguration * sac_ptr;
  assert(sac_ptr = static_cast< SaConfiguration *> (c_ptr));
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
  current_temperature = init_temperature;
  num_of_accepts = 0;
  num_of_rejects = 0;
  current_genome.evaluate();
  best_genome = current_genome;
  r_ptr->incr_objective_function_evaluations();
  capture_iterations = 0;
  while(!done)
    {
      for(int i = 1; i < iterations;i++)
	{
	  new_genome.create(current_genome.get_neighbour_genome());
	  new_genome.evaluate();
          accumulated_genome_size += new_genome.get_current_length();
	  r_ptr->incr_objective_function_evaluations();
	  
	  if(c_ptr->capture == 1)
	    {
	      report_search_data(capture_iterations,current_temperature,random_probability,acceptance_probability);
	    }
          capture_iterations += 1;

	  if(c_ptr->ge_report == 1)
	    {
	      cout << i << "  " << current_genome << "  " << current_genome.get_score() << "  " << new_genome << "  " << new_genome.get_score() << " accepts " << num_of_accepts << " rejects " << num_of_rejects << endl;
	      cout << " ------------- end of record ---------------------\n\n";

	  	  
	    }
	  if(c_ptr->zero_improvement_accept == 1)
	    {
	      if(new_genome >= current_genome)
		{
		  current_genome = new_genome;
		  random_probability = -1; 
		  acceptance_probability = -1;
		  
		  
		}
	      else
		conditionally_accept();

	    }
	  else
	    {
	      if(new_genome > current_genome)
		{	  
		  current_genome = new_genome;
		  random_probability = -1; 
		  acceptance_probability = -1;
		}
	      else
		conditionally_accept();
	      
	    }



	  if(current_genome > best_genome)      
	    best_genome = current_genome;
	  if(current_genome.get_score() == TARGET_SCORE)
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
	
	  
	}  // iterations loop

      current_temperature = current_temperature * temp_change_rate;
      if(current_temperature < min_temperature)
	done = true;
  
      
    }  // while !done
  r_ptr->set_average_genome_size(accumulated_genome_size/capture_iterations); 
  r_ptr->set_final_score(current_genome.get_score());
  current_genome.get_genome_value(r_ptr->final_genome_value);
  best_genome.get_genome_value(r_ptr->best_genome_value);  
  r_ptr->set_best_score(best_genome.get_score());
  return get_trial_result();
}


void SimulatedAnnealing::conditionally_accept(void)
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
 




int SimulatedAnnealing::selftest()
{
  return 1;
}

// Additional Declarations
























