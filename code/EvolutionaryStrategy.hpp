#ifndef EvolutionaryStrategy_h
#define EvolutionaryStrategy_h 1



// Metaheuristic
#include "Metaheuristic.hpp"
#include "Population.hpp"
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
class EvolutionaryStrategy : public Metaheuristic
{

public:
  EvolutionaryStrategy();
  
  EvolutionaryStrategy(const EvolutionaryStrategy &right);
  
  virtual ~EvolutionaryStrategy();
  
  int setup_trial();
  void  report_search_data(int iteration_num);
  int run_trial(int trial_num);
  int selftest(void);
  
         
  // Additional Public Declarations
  
protected:
    // Additional Protected Declarations
  
private:
  Population parent_population;
  Population offspring_population; 
  Population combined_population;
  
      // Additional Private Declarations

    // Data Members for Class Attributes

  
    // Additional Implementation Declarations

};




// Class EvolutionaryStrategy 


#endif











