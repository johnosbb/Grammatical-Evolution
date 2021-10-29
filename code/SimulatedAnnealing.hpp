#ifndef SimulatedAnnealing_h
#define SimulatedAnnealing_h 1



// Metaheuristic
#include "Metaheuristic.hpp"
//#include "SaConfiguration.hpp"


//	Basic Algorithim
//	1. generate a current_genome as dictated by the genome
//	configuration.
//	2. Evaluate this current_genome to obtain the current_
//	score.
//	3. Set best_score = current_score and set the best_
//	genome = current_genome.
//	4. Randomly Generate a neighbour_genome of the current_
//	genome.
//	5. Evaluate the neighbour_genome for the new_score.
//	6. if the new_score is better than current_score then
//	set current_score = new_score and set current_genome =
//	neighbour_genome.
//	7. if the new_score is not better than the current_score
//	then accept if exp ( -(new_score - current_
//	score)/(boltzmann_k * current_temperature)) is greater
//	than a andomly generated value in the range (threshold
//	to  100)/100. Also set the current_genome = neighbour_
//	genome.
//	8. If the current_score is better than the best_score
//	then set the best_score = current score and set the best_
//	genome = current_genome.
//	9. repeat step 4 until termination condition is reached.
//
//	NOTEs: Threshold is a value used to control the lower
//	range of the randomly generated integer. If threshold is
//	set to 20 then an integer in the range .2 to 1 will be
//	generated.
class SimulatedAnnealing : public Metaheuristic
{

  public:
      SimulatedAnnealing();

      SimulatedAnnealing(const SimulatedAnnealing &right);

      virtual ~SimulatedAnnealing();

  
      int run_trial(int trial_num);
      int selftest(void);
  
         
    // Additional Public Declarations

  protected:
    // Additional Protected Declarations

  private:

  //SaConfiguration c;
      void conditionally_accept(void);
  

      const int get_num_of_accepts () const;
      void set_num_of_accepts (int value);

      const int get_num_of_rejects () const;
      void set_num_of_rejects (int value);

      const double get_min_temperature () const;
      void set_min_temperature (double value);

      const double get_current_temperature () const;
      void set_current_temperature (double value);


      const double get_temp_change_rate () const;
      void set_temp_change_rate (double value);

      const double get_init_temperature () const;
      void set_init_temperature (double value);

      const int  get_probability_threshold () const;
      void set_probability_threshold (int value);

      const double get_boltzman_constant () const;
      void set_boltzman_constant (double value);


    // Additional Private Declarations

    // Data Members for Class Attributes

      int num_of_accepts;

      int num_of_rejects;

      double min_temperature;

      double current_temperature;

      double temp_change_rate;

      double init_temperature;
 
      double random_probability;

      double acceptance_probability;
  
      int  probability_threshold;

      double boltzman_constant;


    // Additional Implementation Declarations

};




inline void SimulatedAnnealing::set_init_temperature (double value)
{
  init_temperature  = value;
  
}

inline void SimulatedAnnealing::set_temp_change_rate (double value)
{
  temp_change_rate  = value;
  
}
// Class SimulatedAnnealing 


#endif











