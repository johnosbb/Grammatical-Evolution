// RandomSearchFD
#include "RandomSearchFD.hpp"
#include "defines.h"
#include "Genome.hpp"
#include "FrequencyDistribution.hpp"


// Class RandomSearchFD 

RandomSearchFD::RandomSearchFD()
{
}

RandomSearchFD::RandomSearchFD(const RandomSearchFD &right)
{
}


RandomSearchFD::~RandomSearchFD()
{
}


// this contains the main algorithm for random search
int RandomSearchFD::run_trial(int trial_num)
{
  reset_results();
  set_trial_result(FAILURE);
  if(c_ptr->capture_status == 1)
    {
      if(check_capture(trial_num))
	c_ptr->capture = 1;
      else
	c_ptr->capture = 0;
    }
  current_genome.evaluate();
  r_ptr->incr_objective_function_evaluations();
  for(int i = 1; i < iterations;i++)
    {
      new_genome.create();
      new_genome.evaluate();
      fd.evaluate(new_genome.get_score());
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

    } // for iterations

  r_ptr->set_average_genome_size(accumulated_genome_size/iterations);
  r_ptr->set_final_score(current_genome.get_score());
  current_genome.get_genome_value(r_ptr->final_genome_value);
  current_genome.get_genome_value(r_ptr->best_genome_value);  
  cout << " Fitness Distribution " << endl;
  fd.show();
  fd.save();
  return get_trial_result();
  
}


int RandomSearchFD::selftest()
{
   cout << "Running selftest on configuration object : ";
  if(c_ptr->selftest())
    cout << "Passes\n";
  else
    cout << "Failed\n";
  return 1;
}


// Additional Declarations























