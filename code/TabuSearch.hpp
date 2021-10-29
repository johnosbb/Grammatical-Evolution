#ifndef TabuSearch_h
#define TabuSearch_h 1



// Metaheuristic
#include "Metaheuristic.hpp"
#include "TabuConfiguration.hpp"
#include "TabuList.hpp"

typedef vector<Genome> genomelist;

//	Tabu Search
//	1. Randomly generate the current_genome and calculate
//	the current_score.
//	2. Generate neighbour_genomes ie. all of the neighbours
//	of current_genome and evaluate neighbour_genomes to
//	determine neighbours_score and neighbours_score_delta.
//	(neighbours_score_delta is the difference between a
//	neighbour_score and the current_score.
//	4. Select the neighbour_genome with the best_score_
//	delta. Start a tabu tenure for this neighbour_genome.
//	5. Set current_genome to selected neighbour_genome and
//	set current_score to best_neighbour_score.
//	6. Generate neighbour_genomes ie. all of the neighbours
//	of current_genome and evaluate neighbour_genomes to
//	determine neighbour_scores.
//	7. Select the neighbour_genome with the best_score_
//	delta. If this neighbour_genome is on the Tabu_list then
//	only select if the neighbours_score_delta yields an
//	improvement else select the next_best_neighbour_genome
//	not on the tabu list.
//	8. If the newly selected neighbour is not tabu then add
//	them to the tabu list.
//	9. Set current_genome to selected neighbour_genome and
//	set current_score to corresponding neighbour_score.
//	10. Decrement the tabu tenure for each tabu member.
//	11. Repeat step 6 until terminating conditions are met.


class TabuSearch : public Metaheuristic
{

  public:
      TabuSearch();

      TabuSearch(const TabuSearch &right);

      virtual ~TabuSearch();
        
      int run_trial(int trial_num);
      int selftest();
  
    // Additional Public Declarations
  
  protected:
    // Additional Protected Declarations

  private:
     gvectorlist all_neighbour_genomes;
     genomelist genome_neighbourhood;
     TabuList tabu_list;
     int show_neighbourhood(void);
     int create_neighbourhood(void);
     int show_genome_neighbourhood(void);
     void remove_best_neighbour(void);
  
     Genome select_best_neighbour(void);
     Genome best_neighbour;
     void  TabuSearch::clear(genomelist * g);
    // Additional Private Declarations

    // Additional Implementation Declarations

};


// Class TabuSearch 




#endif









