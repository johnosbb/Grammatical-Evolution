
// Results
#include "Results.hpp"
#include "string.h"


// Class Results 



Results::Results()
      : best_score(0),
        run_status(0),
        result_status(0),
        final_score(0),
	objective_function_evaluations(0),
	average_genome_size(0),
	average_stdev_value(0)
{
}

Results::Results(const Results &right)
      : best_score(0),
        run_status(0),
        result_status(0),
        final_score(0),
	objective_function_evaluations(0),
	average_genome_size(0),
	average_stdev_value(0)
{
}

void Results::reset(void)
{
  set_objective_function_evaluations(0);
  set_final_score (0);
  set_best_score (0);
  
  set_run_status(0);
  
  set_result_status(0);
  
  strcpy(best_genome_value,"");
  strcpy(final_genome_value,"");
}






Results::~Results()
{
}




















