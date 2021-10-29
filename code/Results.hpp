
#ifndef Results_h
#define Results_h 1

#include "defines.h"


// Experiment


class Results 
{

public:
  Results();
  
  Results(const Results &right);
  
  ~Results();
  
  void reset(void);
  
  const double get_best_score () const;
  void set_best_score (double value);
  
  const int get_run_status () const;
  void set_run_status (int value);
  
  const double get_best_ever_score () const;
  void set_best_ever_score (double value);
  
  const int get_result_status () const;
  void set_result_status (int value);

  const long get_objective_function_evaluations () const;
  void set_objective_function_evaluations (long value); 
  const long get_average_genome_size () const;
  void set_average_genome_size (long value);
  const double get_average_stdev_value() const;
  void set_average_stdev_value (double value);

  void incr_objective_function_evaluations (void);
  void incr_objective_function_evaluations (int amount);

  const double get_final_score () const;
  void set_final_score (double value);
  
  char best_genome_value[MAX_GENOME_LENGTH * MAX_NO_CHARS_GENE];
  char final_genome_value[MAX_GENOME_LENGTH * MAX_NO_CHARS_GENE];
  
  // Additional Public Declarations
  
protected:
  // Additional Protected Declarations
  
private:

  
  // Additional Private Declarations
  
  // Data Members for Class Attributes
  
  double best_score;
  
  int run_status;
  
  double best_ever_score;
  
  int result_status;
  
  double final_score;
  
  long objective_function_evaluations;
  
  long average_genome_size;
  
  
  double  average_stdev_value;
    // Data Members for Associations
  

  
};


// Class Results 


inline const double Results::get_best_score () const
{
  return best_score;
}

inline void Results::set_best_score (double value)
{
  best_score = value;
}

inline const int Results::get_run_status () const
{
  return run_status;
}

inline void Results::set_run_status (int value)
{
  run_status = value;
}

inline const double Results::get_best_ever_score () const
{
  return best_ever_score;
}

inline void Results::set_best_ever_score (double value)
{
  best_ever_score = value;
}

inline const int Results::get_result_status () const
{
  return result_status;
}




inline void Results::set_result_status (int value)
{
  result_status = value;
}

inline void Results::set_average_stdev_value (double value)
{
  average_stdev_value = value;
}


inline const long Results::get_objective_function_evaluations () const
{
  return objective_function_evaluations;
}

inline void Results::set_objective_function_evaluations (long value)
{
  objective_function_evaluations = value;
}

inline const long Results::get_average_genome_size () const
{
  return average_genome_size;
}

inline const double Results::get_average_stdev_value () const
{
  return average_genome_size;
}

inline void Results::set_average_genome_size (long value)
{
  average_genome_size = value;
}

inline void Results::incr_objective_function_evaluations (void)
{
  objective_function_evaluations+=1;
}

inline void Results::incr_objective_function_evaluations (int amount)
{
  objective_function_evaluations += amount;
}

inline const double Results::get_final_score () const
{
  return final_score;
}

inline void Results::set_final_score (double value)
{
  final_score = value;
  
}

#endif






