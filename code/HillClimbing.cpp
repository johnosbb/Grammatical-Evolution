



// HillClimbing
#include "HillClimbing.hpp"
#include "HcConfiguration.hpp"
#include "assert.h"




// Class HillClimbing 


HillClimbing::HillClimbing()
      : dwell_time(100)
{
  //c_ptr = &c;
  
}

HillClimbing::HillClimbing(const HillClimbing &right)
      : dwell_time(100)
{
}


HillClimbing::~HillClimbing()
{
}


int HillClimbing::run_trial(int trial_num)
{
  reset_results();
  set_trial_result(FAILURE);
  HcConfiguration * hcc_ptr;
  assert(hcc_ptr = static_cast< HcConfiguration *> (c_ptr));
  if(hcc_ptr->get_dwell_time() != 0)
    set_dwell_time (hcc_ptr->get_dwell_time());
  if(c_ptr->capture_status == 1)
    {
      if(check_capture(trial_num))
	c_ptr->capture = 1;
      else
	c_ptr->capture = 0;
    }
  current_genome.evaluate();
  new_genome = current_genome;
  r_ptr->incr_objective_function_evaluations();
  for(int i = 1; i < iterations;i++)
    {      
      new_genome.create(current_genome.get_neighbour_genome());
      new_genome.evaluate();
      accumulated_genome_size += new_genome.get_current_length();   
      r_ptr->incr_objective_function_evaluations();

      if(c_ptr->capture == 1)
	report_search_data(i);
      if(c_ptr->ge_report == 1)
	{
	  cout << i << "  " << current_genome << "  " << current_genome.get_score() << "  " << new_genome << "  " << new_genome.get_score() << endl;
	  cout << " ------------- end of record ---------------------\n\n";

	  	  
	}

      if(c_ptr->zero_improvement_accept == 1)
	{
	  if(new_genome >= current_genome)
	    {
	      current_genome = new_genome;
	    }
	}
      else
	{
	  if(new_genome > current_genome)
	    {	  
	      current_genome = new_genome;
	    }
	}
      
      if(current_genome.get_score() == TARGET_SCORE)
	{
	  cout << "DEBUG: YAHOO!!!!!!!!";
	  set_trial_result(SUCCESS);
	  break;
	}      

    }  // for iterations
  r_ptr->set_average_genome_size(accumulated_genome_size/iterations);
  r_ptr->set_final_score(current_genome.get_score());
  current_genome.get_genome_value(r_ptr->final_genome_value);
  current_genome.get_genome_value(r_ptr->best_genome_value);  
  return get_trial_result();
}


int HillClimbing::selftest()
{
  return 1;
}


// Additional Declarations


















