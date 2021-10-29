// Genome
#include <fstream.h>
#include "Population.hpp"
#include "defines.h"
#include "string.h"
#include "Random.hpp"
#include "converter.hpp"
#include "ge.hpp"
#include <string.h>
#include <stdio.h>
#include <iostream.h>
#include <vector>
#include <assert.h>
#include "Configuration.hpp"
#include "Results.hpp"
#include "Selection.hpp"
#include <algorithm>
#include <functional>


extern "C" int  string_to_doublearray(char c[],int double_array[]);

// Class Population 


winsCompare winscomp;

Population::Population()
  
{
}

Population::Population(const Population &right)
{
  clear(&the_population);
  copy(right.the_population.begin(), right.the_population.end(), back_inserter(this->the_population));
  
}

// creates a population of a given size. Genomes are created with the initial value supplied , the value of the individual genes are the values given

void Population::create(int size, int maximum_genome_length ,int maximum_gene_value, char initial_genome_value[])
{
  int n = 0;
  Genome g;
  g.set_max_length(maximum_genome_length);
  g.set_max_gene_value(maximum_gene_value);
  clear(&the_population);
    
  while(n < size)
    {
      g.create(initial_genome_value);  // creates a genome of random length
      the_population.push_back(g);
      n++;
      }
}





// creates a population from a given comma delimted file of genomes.
// if there are more than 'size' individuals in the file then only 'size' individuals will be used
// if there are less than size individuals then the population will be padded with the last
// individual 

void Population::create(int maximum_genome_length ,int maximum_gene_value,char filename[],int size )
{
  FILE * config_fileptr;
  char initial_genome_value[MAX_GENOME_LENGTH * MAX_NO_CHARS_GENE]; 
  int n = 0;
  Genome g;
  cout << ".......Loading Population configuration file " << filename << " for population size " << size << endl;
  if( (config_fileptr = fopen(filename,"r")) == NULL)
    {
      cout << "Error opening Population configuration file " << filename << endl;
      exit(1);
    }
  g.set_max_length(maximum_genome_length);
  g.set_max_gene_value(maximum_gene_value);
  clear(&the_population);
  // open the population file
  while ( fscanf(config_fileptr, "%s",initial_genome_value) != EOF)
    {
      // read the next individual from the file
      strcat(initial_genome_value,"\n");
      g.create(initial_genome_value);  // creates a genome from given value
      the_population.push_back(g);
      n++;
      if(n > size)
	{
	  cout << "Error Population configuration file larger than population " << size << endl;
	  exit(1);
	}
    }
  if(n < size)
    {
      cout << "Error Population configuration file smaller than population " << size << endl;
      exit(1);
    }
  cout << "Loaded  population size " << size << endl;
  fclose(config_fileptr);
}





// creates a population of a given size. Genomes are created with the initial length specified, the value of the individual genes are randomly selected upto a value of max_gene_value

void Population::create(int size, int maximum_genome_length , int maximum_gene_value , int initial_length, int initial_length_variation_range)
{
  int n = 0;
  Genome g;
  g.set_max_length(maximum_genome_length);
  g.set_max_gene_value(maximum_gene_value);
  clear(&the_population);
  while(n < size)
    {
      g.create(initial_length, initial_length_variation_range );  // creates a genome of random length
      the_population.push_back(g);
      n++;
    }
}


void Population::create(int size, int maximum_genome_length , int maximum_gene_value , int initial_length, int initial_length_variation_range , double std_deviation)
{
  int n = 0;
  Genome g;
  g.set_max_length(maximum_genome_length);
  g.set_max_gene_value(maximum_gene_value);
  clear(&the_population);
  while(n < size)
    {
      g.create_with_stdev(initial_length, initial_length_variation_range, std_deviation );  // creates a genome of random length
      the_population.push_back(g);
      n++;
    }
}

// create a population of individuals of given fixed length
void Population::create(int size, int maximum_genome_length , int maximum_gene_value , int initial_length)
{
  int n = 0;
  Genome g;
  g.set_max_length(maximum_genome_length);
  g.set_max_gene_value(maximum_gene_value);
  clear(&the_population);
  while(n < size)
    {
      g.create(initial_length);  // creates a genome of random length
      the_population.push_back(g);
      n++;
    }
}



// creates a population of a given size. Genomes are randomly created with a randomly created length less upto max_genome_length, the value of the individual genes are randomly selected upto a value of max_gene_value

void Population::create(int size, int maximum_genome_length , int maximum_gene_value)
{
  int n = 0;
  Genome g;
  g.set_max_length(maximum_genome_length);
  g.set_max_gene_value(maximum_gene_value);
  clear(&the_population);
  while(n < size)
    {
      g.create();  // creates a genome of random length
      the_population.push_back(g);
      n++;
    }
}


void Population::configure(Configuration * config_ptr)
{
  genomelist::iterator iter;
  c_ptr = config_ptr;
  iter = the_population.begin(); 
  while(iter != the_population.end())
    {  
      (*iter).configure(c_ptr->wrap,c_ptr->ge_report,c_ptr->mutation_selector,c_ptr->mutation_rate,c_ptr->style,c_ptr->mutation_rate_range);
      iter++;
      
    }
  
 
}

void Population::set_std_deviation(double value)
{
  genomelist::iterator iter;
  iter = the_population.begin(); 
  while(iter != the_population.end())
    {  
      (*iter).set_all_stdev_value(value);
      iter++;
      
    }
  
}
  

bool Population::evaluate(double target_score)
{
  genomelist::iterator iter;
  bool result = false;
  iter = the_population.begin(); 
  while(iter != the_population.end())
    {  
      (*iter).evaluate();
      if((*iter).get_score() == target_score)
	{
	  result = true;
	  best_genome = *(iter);
	  break;
	}
      iter++;
    }
  return result;
}
 

void  Population::clear_the_population(void)
{
  genomelist::iterator iter;
  iter = the_population.begin();
  while(iter!= the_population.end())
    {
      the_population.pop_back();
    }
  
  //g->erase(g->begin(),g->end());
}



void  Population::clear(genomelist * g)
{
  g->erase(g->begin(),g->end());
  
  //g->erase(g->begin(),g->end());
}

/*
void  Population::clear(gvectorlist * g)
{
    g->erase(g->begin(),g->end());
    
}

*/


Population::~Population()
{
}


void  Population::show()
{
  int cnt = 1;
  genomelist::const_iterator iter;
  iter = the_population.begin();
  while(iter!= the_population.end())
    {
      cout << cnt << ". " << *iter << "  ";
      cout << (*iter).get_score() << "  ";;
      cout << (*iter).get_number_of_wins();
      cout << "\n";
      iter++;
      cnt++;
      
    }
    
}

void  Population::show_stdev()
{
  int cnt = 1;
  genomelist::iterator iter;
  iter = the_population.begin();
  while(iter!= the_population.end())
    {
      cout << cnt << ". " ;
      (*iter).show_standard_deviation();
      cout << "\n";
      iter++;
      cnt++;
      
    }
    
}


double  Population::get_avg_mutation_rate()
{
  int cnt = 1;
  double total = 0;
  genomelist::iterator iter;
  iter = the_population.begin();
  while(iter!= the_population.end())
    {
      total += (*iter).get_mutation_rate();
      iter++;
      cnt++;
      
    }
  return total/cnt;
}


double  Population::get_avg_mutation_bias()
{
  int cnt = 1;
  double total = 0;
  genomelist::iterator iter;
  iter = the_population.begin();
  while(iter!= the_population.end())
    {
      total += (*iter).get_mutation_bias();
      iter++;
      cnt++;
      
    }
  return total/cnt;
}


void  Population::stream_stdev(ofstream & capture_data_file)
{
  genomelist::iterator iter;
  iter = the_population.begin();
  int cnt = 1 ;
  
  while(iter!= the_population.end())
    {
      capture_data_file << "S: " << cnt++ << ". ";
      
      (*iter).stream_std(capture_data_file);
      iter++;
    }
  capture_data_file << "\n";
  
}



Genome  Population::sort_descending()
{
  sort(the_population.begin(),the_population.end());
  reverse(the_population.begin(),the_population.end());
  genomelist::iterator iter;
  iter = the_population.begin();
  best_genome = *iter;
  return *iter;
  
}

void  Population::sort_using_wins(void)
{

  //  sort(the_population.begin(),the_population.end(),populationSortCriterion);
  sort(the_population.begin(),the_population.end(),winscomp);
  reverse(the_population.begin(),the_population.end());
}


Population & Population::operator=(const Population &right)
{
  clear_the_population();
  copy(right.the_population.begin(), right.the_population.end(), back_inserter(this->the_population));
  return *this;  
}

ostream & operator<<(ostream &stream,const Population &right)
{ 
  genomelist::const_iterator iter;
  iter = right.the_population.begin();
  int cnt = 1;
  
  while(iter!= right.the_population.end())
    {
      stream << "P: " << cnt++ << ". ";
      
      stream <<  *iter;
      stream << "  " << (*iter).get_score() << "  ";
      stream << (*iter).get_number_of_wins() << "  ";
      stream <<  (*iter).get_mutation_rate();
      stream << "\n";
      iter++;
    }
  return stream;
}


// returns a population based on the number of individuals specified using the specified selection mechanism


Population  Population::operator+(const Population &right)
{
  Population p;
  genomelist::const_iterator iter;
  iter = right.the_population.begin();
  while(iter!= right.the_population.end())
    {
      p.the_population.push_back(*iter);
      iter++;
    }
  iter = the_population.begin();
  while(iter!= the_population.end())
    {
      p.the_population.push_back(*iter);
      iter++;
    }  
  return p;  
}

// Discrete recombination, the off spring is formed with codons from either of two paremts. 
// The codons are selected from the parents with equal probability
// It takes a reference to a parent population
// This function effectively creates a new population
void Population::discrete_recombination(Population & parent_pop, int size, int maximum_genome_length , int maximum_gene_value)
{
  // until size
  // randomly select two parents from the population
  // create an off-spring who is the same length as the parent
  // consisting of codons drawn from each parent with equal probability
  /* 
 int n = 0;
  Genome g;
  g.set_max_length(maximum_genome_length);
  g.set_max_gene_value(maximum_gene_value);
  clear(&the_population);
  while(n < size) // for the required size
    {
      g.create(maximum_genome_length);  // creates a genome of random value of given lengthlength
      the_population.push_back(g);
      n++;
    }
  */
  genomelist::iterator iter,iterp;
  iter = the_population.begin();
  iterp = parent_pop.the_population.begin();
  while(iter!= the_population.end())
    {
      // select two paremts from the parent population
      // from each of the genomes select a condon with equal probability
      // rebuild the current member with these new codon values
      Genome p1,p2;
      p1 = parent_pop.get_random_genome();
      p2 = parent_pop.get_random_genome();
      //cout << " Selected Genomes P1 : " << p1 << endl;
      //cout << " Selected Genomes P2 : " << p2 << endl; 
      // for each codon in the current genome
      for(int index = 0; index < (*iter).get_current_length();index++)
	{
	  Random r;
	  double val;
	  int selection;
	  selection = r.randomint(2);
	  if(selection == 0)
	    val = p1.get_codon_value(index);
	  else
	    val = p2.get_codon_value(index);
	  (*iter).set_codon_value(index,val);
	}
      //cout << " Resultant Genome C : " << *iter << endl;    
      iter++;
      
    }
  //cout << endl;
  
}

// Intermediate recombination, the off spring is formed with codons from either of two paremts. 
// The codons are selected from the parents with equal probability
// It takes a reference to a parent population
// This function effectively creates a new population
void Population::intermediate_recombination(Population & parent_pop, int size, int maximum_genome_length , int maximum_gene_value,int num_parents)
{
  // until size
  // randomly select two parents from the population
  // create an off-spring who is the same length as the parent
  // consisting of codons drawn from each parent with equal probability
  /*
  int n = 0;
  Genome g;
 
  g.set_max_length(maximum_genome_length);
  g.set_max_gene_value(maximum_gene_value);
  clear(&the_population);
  while(n < size) // for the required size
    {
      g.create(maximum_genome_length);  // creates a genome of random value of given lengthlength
      the_population.push_back(g);
      n++;
    }
  */
  genomelist gl; // a genomelist of the selected parents 
  genomelist::iterator iter,iterp;
  iter = the_population.begin();
  iterp = parent_pop.the_population.begin();
  while(iter!= the_population.end())
    {
      // select n paremts from the parent population
      // from each of the genomes select a condon with equal probability
      // rebuild the current member with these new codon values
     
      for(int i =0; i < num_parents; i++)
	{
	  Genome p;
	  p = parent_pop.get_random_genome();
	  gl.push_back(p);
	  //cout << " Selected Parent  P : " << p << endl;
	}
      
      // for each codon in the current genome
      for(int index = 0; index < (*iter).get_current_length();index++)
	{
	  Random r;
	  double val;
	  int selection;
	  selection = r.randomint(num_parents); 
	  genomelist::iterator itergl;
	  itergl = gl.begin();
	  int cnt =0;
	  while(itergl!= gl.end())
	    {
	      if(cnt == selection)
		break;
	      itergl++;
	      cnt++;
	    }
	  //cout << "Selected Parent was " << (*itergl) << endl;
	  val = (*itergl).get_codon_value(index);
	  (*iter).set_codon_value(index,val);
	}
      // cout << " Resultant Genome C : " << *iter << endl;    
      iter++;
      
    }
  //cout << endl;
  
}

void  Population::mutate(void)
{
  
  genomelist::iterator iter;
  iter = the_population.begin();
  while(iter!= the_population.end())
    {
      (*iter).get_neighbour_genome();
      (*iter).sync_to_neighbour();
      iter++;
    }
}



void  Population::get_statistics(Results * r_ptr)
{
  r_ptr->set_best_score(best_genome.get_score());  
}




void  Population::add_genome(Genome & g)
{
  the_population.push_back(g);  
}


// returns a randomly selected genome from the population

Genome  Population::get_random_genome(void)
{
  Random r; 
  int i = 0;
  genomelist::iterator iter;
  int n = r.randomint(get_current_size());
  iter = the_population.begin();
  while(i < n)
    {
      i++;
      iter++;
    }
  return *iter;
}
















