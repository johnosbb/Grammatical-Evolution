
#ifndef Population_h
#define Population_h 1

#include <fstream.h>
#include <vector>
#include <list>
#include "Random.hpp"
#include "Configuration.hpp"
#include <iostream.h>
#include "defines.h"
#include "Genome.hpp"
#include "Results.hpp"


typedef vector<double> gvector;
typedef vector<Genome> genomelist;


// The population object consists of a variable number of Genomes
// The size of the population can be set at runtime through a configuration file
// The object has the following  responsibilities
// crossover 
// Sorting itself into a required order and performing selection
// Any fitness scaling that is required
// we will need some method of allowing population pass back the necessary reporting parameters
// for now this may be the best genome and some indication of success
// When a population is initialised the operators it uses are defined
// This is preferable to having dedicated subclasses for ES, EP and GA populations
class Population 
{
  
public:
  Population();

  Population(const Population &right);

  ~Population();
  
  friend ostream & operator<<(ostream &stream,const Population &right);
  Population & operator=(const Population &right);
  Population operator+(const Population &right);
  
  double get_avg_mutation_rate();
  double get_avg_mutation_bias();
  
  // used to initialise the individuals in the population to a particular configuration. Each new individual in subsequent populations will have this configuration, it should take a pointer to a configuration object and will be invoked from the setup trial function in the appropriate metaheuristic
  void configure(Configuration * config_ptr);
  // used to configure an already created population
  void evolve(); // creates a new population using the specified crossover/recombination operator ,it invokes the select method to create the evolved population
  bool evaluate(double target_score); // evaluates all individuals in the population using the objective function, it returns true if an individual achieves the target_score or false otherwise
  void create(int size,int maximum_genome_length , int max_gene_value ); // Creates a population of size 
  void create(int size, int maximum_genome_length , int max_gene_value ,char initial_genome_value[]); // Creates a population of size with given value
  // create a population of fixed length individuals
  void create(int size, int maximum_genome_length , int maximum_gene_value , int initial_length);
  
 void create(int maximum_genome_length , int max_gene_value ,char filename[],int size); // Creates a population of size using given configuration filename
  void create(int size, int maximum_genome_length , int max_gene_value , int initial_length, int initial_length_variation_range);  // Creates a population of size with genomes on given length
  void create(int size, int maximum_genome_length , int maximum_gene_value , int initial_length, int initial_length_variation_range , double std_deviation);
  const int get_current_size () const;
  void show(void);
  Genome sort_descending(void); // sorts into descending order
  void  Population::sort_using_wins(void);
  
  void discrete_recombination(Population & parent_pop, int size, int maximum_genome_length , int maximum_gene_value);

  void intermediate_recombination(Population & parent_pop, int size, int maximum_genome_length , int maximum_gene_value,int num_parents);
  
  void set_std_deviation(double value);
  void show_stdev();
  void stream_stdev(ofstream & capture_data_file);
  
  void mutate(void);
  void get_statistics(Results * r_ptr)  ;
  void add_genome(Genome & g);
  Genome  get_random_genome(void);
  
  genomelist the_population;
  
protected:
  // Additional Protected Declarations
  
private:

  void clear(genomelist *);
  void clear_the_population(void);
  Genome best_genome;
  
  
  // Data Members for Associations
  Configuration * c_ptr; // pointer for the configuration object  which will be used to configure individual genomes 
  
  // Additional Implementation Declarations
  void select(); // used by evolve to select the evolved population using the specified selection criteria  


  
};



// Class Population 






inline const int Population::get_current_size () const
{
  return the_population.size();
}



// Following is a function object type, 
// defines how to compare persons (for sorting/searching)
struct winsCompare {  
  bool operator()(const Genome& left, const Genome& right) {
      return left.get_number_of_wins() < right.get_number_of_wins();  // based on last names only
  }
};



#endif
































