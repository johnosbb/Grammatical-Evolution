#ifndef FrequencyDistribution_h
#define FrequencyDistribution_h 1
#include <list>

#include "FrequencyDistributionElement.hpp"

typedef list<FrequencyDistributionElement> frequency_distribution;


//	Random Search Algorithim with support for calciculation of fitness frequency distribution
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

class FrequencyDistribution 

{

  public:
      FrequencyDistribution();

      FrequencyDistribution(const FrequencyDistribution &right);

      virtual ~FrequencyDistribution();
      void  evaluate(double f);
      void show(void);
      int save(void);
  


    // Additional Public Declarations

  protected:
    // Additional Protected Declarations

  private:
  frequency_distribution fd;
  FrequencyDistributionElement fde;
  
  
    // Additional Private Declarations


  

    // Additional Implementation Declarations

};


// Class FrequencyDistribution 



#endif













