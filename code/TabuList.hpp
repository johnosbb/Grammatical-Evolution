
#ifndef TabuList_h
#define TabuList_h 1


#include <vector>
#include <list>
#include "Random.hpp"
#include <iostream.h>
#include "Genome.hpp"

//typedef vector<double> gvector;
//typedef list<gvector> gvectorlist;
typedef vector<Genome> genomelist;

// The TabuList class is responsible for maintaining a tabulist
// Genomes can be added to the list and removed automatically when their tenure expires
// A Genome added to the list has it's tenure set to the default tenure for the list.
// On each iteration the tenure of all Genomes is decremented by one.
// Genomes with zero tenure are automatically removed.
// The class supports search by value to determine if a chosen Genome is Tabu.


class TabuList 
{

public:
  TabuList();

  TabuList(const TabuList &right);

  ~TabuList();

  void add_genome(Genome right);   // add an aelement to the list
  void set_default_tenure(const int &val);  // set the default or reference value of tenure
  const int get_default_tenure (void) const;
  void  show_contents(void);
  void  dcr_tabu_tenure(void);
  int purge(void);  // removes all Genomes with zero tenure
  bool check(const Genome &right); // check if the referenced Genome is a member of the TabuList
      
    // Additional Public Declarations

  protected:
    // Additional Protected Declarations

  private:
  genomelist the_list;
  int default_tenure;
  
  
};



inline const int TabuList::get_default_tenure () const
{
  return default_tenure;
}

inline void TabuList::set_default_tenure (const int &value)
{
  default_tenure = value;
}




#endif








