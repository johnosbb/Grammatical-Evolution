
#ifndef Mutation_h
#define Mutation_h 1


#include <vector>
#include <list>
#include "Random.hpp"
#include <iostream.h>
#include <defines.h>
#include "Genome.hpp"


typedef list<char> pidlist; 
typedef vector<double> gvector;


class Mutation 
{
  
public:
  Mutation();

  Mutation(const Mutation &right);

  ~Mutation();

   
  void mutate_genome(Genome * g);
  void multiple_mutate_genome(Genome * g);
  void multiple_mutate_genome_fixed(Genome * g);
  void multiple_mutate_genome_fixed_with_bias(Genome * g, int bias);
  void EP_mutate_non_random_with_bias(Genome * g);
  
  void force_gene_up(Genome * g)  ;
  int  force_gene_up(Genome * g,int gene_num);
  void force_gene_down(Genome * g);
  int  force_gene_down(Genome * g,int gene_num);
  void shrink_genome(Genome * g);
  int reduce(Genome * g,int amount);
  void grow_genome(Genome * g);
  void EP_mutate_genome(Genome * g); 
  void EP_mutate_genome_classic_adaptive(Genome * g);
  void EP_mutate_genome_classic_adaptive_with_bias(Genome * g);
  void EP_mutate_strategy_variables(Genome * g);
  
protected:
  // Additional Protected Declarations
  
private:
  int status;
  

    // Data Members for Associations

    // Additional Implementation Declarations
};


// Class Mutation 








#endif
































