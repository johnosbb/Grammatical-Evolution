


#ifndef RandomSearchFD_h
#define RandomSearchFD_h 1



// Metaheuristic
#include "Metaheuristic.hpp"
#include "FrequencyDistribution.hpp"



//	Random Search Algorithim with support for fitness frequency distribution logging
//	1. generate a current_genome as dictated by the genome
//	configuration.
//	2. Evaluate this current_genome to obtain the current_
//	score.
//	3. Set best_score = current_score
//	4. Randomly Generate another_genome who may or may not
//	be a neighbour.
//	5. Evaluate another_genome to obtain current_score.
//	6. if the current_score is better than the best_score
//	then set the best_score = current_score.
//	7. goto step 4.

class RandomSearchFD : public Metaheuristic

{

  public:
      RandomSearchFD();

      RandomSearchFD(const RandomSearchFD &right);

      virtual ~RandomSearchFD();

      int run_trial(int);
      int selftest(void);
  
    // Additional Public Declarations

  protected:
    // Additional Protected Declarations

  private:
    // Additional Private Declarations
   FrequencyDistribution fd;
  

  

    // Additional Implementation Declarations

};


// Class RandomSearchFD 



#endif





































