
#ifndef Metaheuristic_h
#define Metaheuristic_h 1


#include <iostream.h>
#include "Configuration.hpp"
#include "SaConfiguration.hpp"
#include "HcConfiguration.hpp"
#include "Genome.hpp"
#include "Results.hpp"
#include <fstream.h>
#include "defines.h"

//	This is a base class for all metaheuristics. The methods
//	associated with the class  generate
//	neighbours or neighbourhoods and set the zero_
//	improvement_accept option. If this is set then
//	neighbours that generate zero improvement to the current
//	fitness will be accepted.
//
//	The run-trial operation runs a single instance of the
//	associated metaheuristic algorithim.
//	At the end of the trial the results structure is
//	populated.


class Metaheuristic 
{

  public:
      Metaheuristic();

      Metaheuristic(const Metaheuristic &right);

      virtual ~Metaheuristic();
      virtual int setup_trial (void);
      virtual int configure(char filename[],Results * results);
      void set_the_configuration(Configuration * ptr);  
      virtual int run_trial (int); 
      virtual int selftest(void);
      void reset_results(void);
      int check_capture(int trial_num);
      virtual void report_search_data(int iteration_num);
      void report_search_data(int iteration_num,double current_temperature,double probability,double random_threshold);
  
      ofstream capture_data_file;
      void set_iterations (int value);  

      int status;

      //	This methods turns on capture of the serach trajectory
      //	for a specified trial. The captured data consists of the
      //	genome and associated fitness for each iteration of the
      //	trial. A flag also indicates wheter or not the
      //	individual was accepted , rejected or accepted
      //	conditionally.
    // Additional Public Declarations

  protected:


      int iterations;
      int capture_iterations;
      long int accumulated_genome_size;
      int search_progress_indicator;  
  
      int trial_result;
  
  


      Genome current_genome;
  
      Genome new_genome;
 
      Genome best_genome;
  

      char cfg_filename[30];
  
      Results * r_ptr;
  
      Configuration * c_ptr;
  

      const int  get_trial_result () const;
      void set_trial_result (int  value);

    // Additional Protected Declarations

  private:

      const int get_search_progress_indicator () const;
      void set_search_progress_indicator (int value);

      char * get_cfg_filename (void);
      void set_cfg_filename (char * filename);

      void reset_zero_improvement_accept (void);   
      void set_zero_improvement_accept (void);   



    // Additional Private Declarations

    // Data Members for Class Attributes

    // Data Members for Associations

    // Additional Implementation Declarations

};


// Class Metaheuristic 




inline const int  Metaheuristic::get_trial_result () const
{
  return trial_result;
}

inline void  Metaheuristic::set_trial_result (int value) 
{
  trial_result = value;
}


inline const int  Metaheuristic::get_search_progress_indicator () const
{
  return search_progress_indicator;
}

inline void  Metaheuristic::set_search_progress_indicator (int value) 
{
  search_progress_indicator = value;
}
#endif

















