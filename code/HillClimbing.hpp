

#ifndef HillClimbing_h
#define HillClimbing_h 1



// Metaheuristic
#include "Metaheuristic.hpp"
#include "defines.h"

//#include "HcConfiguration.hpp"



//	Basic Algorithim
//	1. generate a current_genome as dictated by the genome
//	configuration.
//	2. Evaluate this current_genome to obtain the current_
//	score.
//	3. Set best_score = current_score
//	4. Randomly Generate a neighbour_genome of the current_
//	genome.
//	5. Evaluate the neighbour_genome for the current score.
//	6. if current_score is better than best_score then set
//	best_score = current_score and set best_genome = current_
//	genome. else do nothing.
//	7. repeat step 4 until termination condition is reached.

class HillClimbing : public Metaheuristic

{

  public:
      HillClimbing();

      HillClimbing(const HillClimbing &right);

      virtual ~HillClimbing();

      int run_trial(int trial_num);
      int selftest(void);
  
    // Additional Public Declarations

  protected:
    // Additional Protected Declarations

  private:

      const int get_dwell_time () const;
      void set_dwell_time (int value);

    // Additional Private Declarations

    // Data Members for Class Attributes

    int dwell_time;
  //HcConfiguration c;
  

    // Additional Implementation Declarations

};


// Class HillClimbing 


inline const int HillClimbing::get_dwell_time () const
{
  return dwell_time;
}

inline void HillClimbing::set_dwell_time (int value)
{
  dwell_time = value;
}



#endif






