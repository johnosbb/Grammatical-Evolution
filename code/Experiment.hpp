
#ifndef Experiment_h
#define Experiment_h 1

#include "Metaheuristic.hpp"
#include "Results.hpp"
#include <fstream.h>

//	This class is responsible for the running of the
//	experiment. The object will load a configuration file
//	which selects the metaheuristic to use and sets many of
//	the options available in the genome object.
//
//	The run experiment method starts the trials.
//	The experiment object will pass a reference to a results
//	class or structure to the selected metaheuristic. This
//	is completed at the end of each trial.

class Experiment 
{

  public:
      Experiment();

      Experiment(const Experiment &right);

      ~Experiment();

      int selftest(void);
  
      int select (char m_type[],char filename[],int  num_of_trials);
      int run(char filename[],int  num_of_trials);
      int report_experiment_results(int trial_num);
      int report_trial_results(int trial_num);  
      int save_trial_results(int trial_num);
      int save_experiment_results(int trial_num);
      int open_data_files(char filename[]);
  
      Metaheuristic * m_ptr;     // pointer to a metaheuristic base class
      ofstream save_results_file;
      ofstream save_experiments_file;
  
    // Additional Public Declarations

  protected:
    // Additional Protected Declarations


  private:

      const int get_status () const;
      void set_status (int value);

      const int get_successes () const;
      void set_successes (int value);
      void incr_successes(void);
 
      const int get_failures () const;
      void set_failures (int value);
      void incr_failures(void);  

      const long get_total_objective_function_evaluations () const;
      void set_total_objective_function_evaluations (long value);

    // Additional Private Declarations

    // Data Members for Class Attributes

      int status;
      int failures;
      int successes;
      int experiment_accumulated_genome_size;
      long total_objective_function_evaluations;
    // Data Members for Associations

      Results r;
  

    // Additional Implementation Declarations

};


// Class Experiment 


inline const int Experiment::get_status () const
{
  return status;
}

inline void Experiment::set_status (int value)
{
  status = value;
}


inline const int Experiment::get_successes () const
{
  return successes;
}

inline void Experiment::set_successes (int value)
{
  successes = value;
}


inline void Experiment::incr_successes (void)
{
  successes+=1;
}

inline const int Experiment::get_failures () const
{
  return failures;
}

inline void Experiment::set_failures (int value)
{
  failures = value;
}


inline void Experiment::incr_failures (void)
{
  failures+=1;
}





inline const long Experiment::get_total_objective_function_evaluations () const
{
  return total_objective_function_evaluations;
}

inline void Experiment::set_total_objective_function_evaluations (long value)
{
  total_objective_function_evaluations = value;
}

#endif






