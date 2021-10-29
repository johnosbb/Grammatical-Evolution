
#ifndef Genome_h
#define Genome_h 1


#include <vector>
#include <list>
#include "Random.hpp"
#include <iostream.h>
#include <defines.h>
#include <fstream.h>


typedef list<char> pidlist; 
typedef vector<double> gvector;
typedef vector<gvector> gvectorlist;



// The genome is the basic entity used by all of the search algorithms
// It the case of local search it provides a means of generating it neighbors
// for population based strategies it provides a methods for supporting
// various types of mutation and crossover strategies.
// Local search strategies use operators to mutate the genome
// while ES, EP use dedicated mutation operators





class Genome 
{
  
public:
  Genome();

  Genome(const Genome &right);

  ~Genome();

  gvector &  get_neighbour_genome (void);  // this function determines which mutation operation will be carried out to generate the neighbour
 
  

      //	Generates an initial genome. The genome will be randomly
  //	selected based on the initial_length and initial_length_
  //	variation_range.
  
  //methods
  
  friend ostream & operator<<(ostream &stream,const Genome &right);
  void stream_std(ofstream &stream);
  
  Genome & operator=(const Genome &right); 
  friend bool  operator>(const Genome &left,const Genome &right);
  friend bool  operator<(const Genome &left,const Genome &right) ;
  friend bool  operator>=(const Genome &left,const Genome &right) ;  
  bool  operator==(const Genome &right) const;  
  bool  operator!=(const Genome &right);
  void get_genome_value(char genome_val[]);
  const int get_wrap () const;
  void generate_neighbourhood_genomes (gvectorlist * glist);
  void generate_neighbourhood_genomes_pure (gvectorlist * glist);
  int create(int initial_length_value , int initial_length_variation_range_value);
  int create_with_stdev(int initial_length_value ,int initial_length_variation_range_value, double stdev_value);
  int add_stdev(double value);
  int create(char initial_genome_val[]);
  int create(gvector genome_val); 
  int create(void); 
  int create(int length); 
  int configure(int wrap_val,int ge_report_val,int sel_bias[][2],int mutation_rate,int style,int mutation_rate_range);
 int configure(int wrap_val,int ge_report_val,int sel_bias[][2],int mutation_rate,int style,int mutation_rate_range,int mutation_bias);
  int configure(int wrap_val,int ge_report_val,int style);
  double  evaluate(void);
  double  dummy_evaluate(void);
  const double get_score () const; 
  const int get_mutation_rate () const;
  void set_mutation_rate(int value);  
  const int get_mutation_rate_range () const;
  void set_mutation_rate_range(int  value);
  void set_mutation_bias(int  value);
  const int get_mutation_bias () const;
  void set_score (double value);  
  const int get_tenure () const; 
  const int get_number_of_wins () const;
  void set_tenure (int value);  
  void set_number_of_wins (int value);
  void incr_number_of_wins (void); 
  void dcr_tenure (void);
  const double get_score_delta () const;
  void set_score_delta (double value);
  const int get_max_gene_value () const;
  const int get_max_stdev_value () const;
  void set_max_gene_value (int value);
  const int get_max_length () const; 
  const int get_min_length () const;
  void set_max_length (int value);  
  const int get_current_length () const;
  void set_current_length (int value); 
  int get_genes_used ();
  int reduce(int amount);
  void swap_two_genes(const int pos1, const int pos2);
  void duplicate_genes(); //Duplicates 1 or More Genes    
  double get_codon_value(unsigned int index);
  void show_neighbour_genome(void);
  void show_genome(gvector * the_gvector);  
  int set_codon_value(unsigned int index , double value);
  int increment_codon_value(unsigned int index , double value);
  void sync_to_genome(void) ;
  void sync_to_neighbour(void);
  void show_standard_deviation(void);
  double get_stdev_value(unsigned int index);
  int set_stdev_value(unsigned int index , double value);
  int set_all_stdev_value(double value);
  double get_average_stdev_value(void);
  
  // Additional Public Declarations
  
  gvector genome; // this is the central component of the genome , a vector of doubles
  gvector neighbour_genome;  // for local search a genome can reference its immediate neighbor
  gvector standard_deviation; // for ES and EP a genome can maintain a list of strategy variables
  gvector rotation_angle;   // ES can additionally support a number of rotation angles
  gvectorlist parents; // a list of its immediate parents , normally two but could be more
  pidlist parents_id; // a list of ids to immediate parents which relate to previous list

  void clear(void);
  int add_codon(double value);
  
   

protected:
  // Additional Protected Declarations
  
private:
  void clear(gvector *);
  void clear(gvectorlist *);
  void mutate_genome(MUTATOR m);
  const gvector get_genome () const;
  void set_genome (gvector value);
  const int get_bias () const;
  void set_bias (int value);
  //void force_gene_up(void);
  //void mutate_genome(void);
  //void multiple_mutate_genome(void);
  //void force_gene_down(void);   
  //int force_gene_down(int num_gene);   
  //int force_gene_up(int num_gene); 
  //void shrink_genome(void);
  //void grow_genome(void); 
  // Additional Private Declarations
  // Data Members for Class Attributes
  
  int current_length;
  int status;
  double score;
  double score_delta;
  int tenure;
  int bias;
  Random r;
  int max_length;
  int min_length;
  int max_gene_value;
  int wrap;
  int ge_report;
  int selector_bias[NUM_OF_OPERATORS][2];
  int mutation_rate;  
  int mutation_rate_range;
  int mutation_bias;
  int genes_used;
  int number_of_wins; 
  int max_stdev_value;
  int grammatical_processing;
  
  
  
  // Data Members for Associations


  // Additional Implementation Declarations

};


// Class Genome 


inline const int Genome::get_current_length () const
{
  return genome.size();
}

inline const int Genome::get_max_length () const
{
  return max_length;
}

inline const double  Genome::get_score () const
{
  return score;
}

inline const int  Genome::get_min_length () const
{
  return min_length;
}

inline const int  Genome::get_mutation_rate () const
{
  return mutation_rate;
}

inline void Genome::set_mutation_rate (int value)
{
  mutation_rate = value;
}
inline const int  Genome::get_mutation_rate_range () const
{
  return mutation_rate_range;
}

inline const int  Genome::get_mutation_bias () const
{
  return mutation_bias;
}


inline void Genome::set_mutation_rate_range (int  value)
{
  mutation_rate_range = value;
}

inline void Genome::set_mutation_bias (int  value)
{
  mutation_bias = value;
}


inline int Genome::get_genes_used ()
{
  return genes_used;
}

inline void Genome::set_score (double value)
{
  score = value;
}


inline void Genome::set_number_of_wins (int value)
{
  number_of_wins = value;
}

inline void Genome::incr_number_of_wins (void)
{
  number_of_wins += 1;
}

inline const int  Genome::get_number_of_wins () const
{
  return number_of_wins;
}


inline const double  Genome::get_score_delta () const
{
  return score_delta;
}


inline void Genome::set_score_delta (double value)
{
  score_delta = score - value;
}
inline const int  Genome::get_tenure () const
{
  return tenure;
}


inline void Genome::set_tenure (int value)
{
  tenure = value;
}

inline void Genome::dcr_tenure (void)
{
  tenure = tenure -1;
}
inline const int Genome::get_wrap () const
{
  return wrap;
}

inline void Genome::set_current_length (int value)
{
  current_length = value;
}

inline void Genome::set_max_length (int value)
{
  max_length = value;
}

inline const gvector Genome::get_genome () const
{
  return genome;
}

inline void Genome::set_genome (gvector value)
{
  genome = value;
}


inline const int Genome::get_bias () const
{
  return bias;
}

inline void Genome::set_bias (int value)
{
  bias = value;
}



inline const int Genome::get_max_gene_value () const
{
  return max_gene_value;
}

inline const int Genome::get_max_stdev_value () const
{
  return max_stdev_value;
}


inline void Genome::set_max_gene_value (int value)
{
  max_gene_value = value;
}





#endif
































