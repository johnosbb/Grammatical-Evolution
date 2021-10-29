// Genome
#include "Genome.hpp"
#include "defines.h"
#include "string.h"
#include "Random.hpp"
#include "converter.hpp"
#include "ge_gep.hpp"
#include "ge.hpp"
#include <string.h>
#include <stdio.h>
#include <iostream.h>
#include <vector>
#include <assert.h>
#include "Mutation.hpp"



extern "C" int  string_to_doublearray(char c[],double double_array[]);

// Class Genome 


Genome::Genome()
  : score(0),
    bias(false),
    max_length(MAX_GENOME_LENGTH),
    min_length(MIN_GENOME_LENGTH),
    max_gene_value(MAX_GENE_VALUE),
    wrap(1),
    ge_report(0),
    mutation_rate(3),
    mutation_rate_range(20),
    mutation_bias(0),
    genes_used(0),
    number_of_wins(0),
    max_stdev_value(MAX_STDEV_VALUE),
    grammatical_processing(0)  // default is GE style
{
}

Genome::Genome(const Genome &right)
  : score(0),
    bias(false),
    max_length(MAX_GENOME_LENGTH),
    min_length(MIN_GENOME_LENGTH),
    max_gene_value(255),
    wrap(1),
    ge_report(0),
    mutation_rate(3),
    mutation_rate_range(20),
    mutation_bias(0),
    genes_used(0),
    number_of_wins(0),
    max_stdev_value(MAX_STDEV_VALUE),
    grammatical_processing(0) // default is GE style
{
  max_length = right.max_length;
  min_length = right.min_length;
  max_gene_value = right.max_gene_value;
  wrap = right.wrap;
  ge_report = right.ge_report;
  bias = right.bias;
  current_length = right.current_length;
  status = right.status;
  for(int i =0; i < NUM_OF_OPERATORS;i++)
    {
      selector_bias[i][0] = right.selector_bias[i][0];
      selector_bias[i][1] = right.selector_bias[i][1];	  
    }
  clear(&genome);
  clear(&neighbour_genome);
  copy(right.genome.begin(), right.genome.end(), back_inserter(this->genome));
  copy(right.genome.begin(), right.genome.end(), back_inserter(this->neighbour_genome));
  clear(&standard_deviation);
  copy(right.standard_deviation.begin(), right.standard_deviation.end(), back_inserter(this->standard_deviation));
  score = right.score;
  score_delta = right.score_delta;
  tenure = right.tenure;
  mutation_rate = right.mutation_rate;
  mutation_rate_range = right.mutation_rate_range;
  mutation_bias = right.mutation_bias;
  genes_used = right.genes_used;
  number_of_wins = right.number_of_wins;
  grammatical_processing = right.grammatical_processing;
  
}



// configuration function  for creating a genome of a desired initial length
// The contents of the genome are randomly generated
// The initial_length_variation_range_value determines the amount by which
// the initial length can vary

int Genome::create(int initial_length_value ,int initial_length_variation_range_value)
{
    int length = r.randomintrange(initial_length_value - initial_length_variation_range_value ,initial_length_value +  initial_length_variation_range_value + 1);
    if (length < min_length)
      length = min_length;
    if (length > max_length)
      length = max_length;
    clear(&genome);
    clear(&neighbour_genome);
    
    for(int i = 0;i < length;i++)
    {
      int n = r.randomint(max_gene_value + 1);
      genome.push_back(n);
      neighbour_genome.push_back(n);
    }
    current_length = genome.size();
    return OKAY;
}

int Genome::create_with_stdev(int initial_length_value ,int initial_length_variation_range_value, double stdev_value)
{
    int length = r.randomintrange(initial_length_value - initial_length_variation_range_value ,initial_length_value +  initial_length_variation_range_value + 1);
    if (length < min_length)
      length = min_length;
    if (length > max_length)
      length = max_length;
    clear(&genome);
    clear(&neighbour_genome);
    clear(&standard_deviation);  
    for(int i = 0;i < length;i++)
    {
      int n = r.randomint(max_gene_value + 1);
      genome.push_back(n);
      neighbour_genome.push_back(n);
      standard_deviation.push_back(stdev_value);
    }
    current_length = genome.size();
    return OKAY;
}


// create a genome with random contents of a given length

int Genome::create(int length)
{
    clear(&genome);
    clear(&neighbour_genome);
    clear(&standard_deviation);
    
    for(int i = 0;i < length;i++)
    {
      double n = double(r.randomint(max_gene_value + 1));
      genome.push_back(n);
      neighbour_genome.push_back(n);
      standard_deviation.push_back(0);
    }
    current_length = genome.size();
    return OKAY;

}


int Genome::create(void)
{
    int length = r.randomintrange(min_length, max_length + 1); 
    clear(&genome);
    clear(&neighbour_genome);
    clear(&standard_deviation);
    
    for(int i = 0;i < length;i++)
    {
      double n = double(r.randomint(max_gene_value + 1));
      genome.push_back(n);
      neighbour_genome.push_back(n);
      standard_deviation.push_back(0);
    }
    current_length = genome.size();
    return OKAY;

}


// configuration function for creating a genome with agiven initial value

int Genome::create(char initial_genome_val[])
{
  status = NOT_OKAY;
  double double_array[MAX_GENOME_LENGTH + 1];     
  int cnt = 0;
  clear(&genome);
  clear(&neighbour_genome);
  clear(&standard_deviation);
  if(string_to_doublearray(initial_genome_val,double_array))
    {
       while(double_array[cnt]!= -1)
	 {
	   //cout << "DEBUG: Value returned from string_to_double " << double_array[cnt] << endl;
	   genome.push_back((double)double_array[cnt]);
	   neighbour_genome.push_back((double)double_array[cnt++]);
	   standard_deviation.push_back(0);
	 }
       
       status = OKAY;
       
    }

  current_length = genome.size();
  return status;
}

int Genome::create(gvector genome_val)
{
  status = OKAY;
  clear(&genome);
  clear(&neighbour_genome);
  copy(genome_val.begin(), genome_val.end(), back_inserter(this->genome));  
  copy(genome_val.begin(), genome_val.end(), back_inserter(this->neighbour_genome));  
  current_length = genome.size();
  return status;
}



// configuration function for creating a genome with agiven initial value

int Genome::configure(int wrap_val,int ge_report_val,int sel_bias[][2],int mut_rate, int style,int mut_rate_range,int mut_bias )
{
  status = OKAY;
  wrap = wrap_val;
  ge_report = ge_report_val;
  for(int i =0; i < NUM_OF_OPERATORS;i++)
    {
      selector_bias[i][0] = sel_bias[i][0];
      selector_bias[i][1] = sel_bias[i][1];
    }
  
  mutation_rate= mut_rate;
  mutation_rate_range= mut_rate_range;
  mutation_bias = mut_bias;
  grammatical_processing = style;
  return status;
}



// configuration function for creating a genome with agiven initial value

int Genome::configure(int wrap_val,int ge_report_val,int sel_bias[][2],int mut_rate, int style,int mut_rate_range )
{
  status = OKAY;
  wrap = wrap_val;
  ge_report = ge_report_val;
  for(int i =0; i < NUM_OF_OPERATORS;i++)
    {
      selector_bias[i][0] = sel_bias[i][0];
      selector_bias[i][1] = sel_bias[i][1];
    }
  
  mutation_rate= mut_rate;
  mutation_rate_range= mut_rate_range;
  grammatical_processing = style;
  return status;
}


// configuration function for creating a genome with a given initial value

int Genome::configure(int wrap_val,int ge_report_val,int style)
{
  status = OKAY;
  wrap = wrap_val;
  ge_report = ge_report_val;
  grammatical_processing = style;
  return status;
}



double Genome::evaluate(void)
{

  gvector::iterator iter;
  iter = genome.begin();
  double * gene_d;
  int genelength = genome.size();
  int * binarystring ;
  int stringlength = (genelength * 8);  
  gene_d =  new double [genelength];
  binarystring = new int[stringlength];  
  double fitness = 0.0;
  int count=0;
  while(iter != genome.end())
    {
      gene_d[count++]=*iter;
      //cout << "DEBUG: Gene value in evaluate" << *iter << endl;
      iter++;
    }
  converter cvrt;
  cvrt.process(gene_d,genelength,binarystring);
  
  if(grammatical_processing == 0)
    { 
      //cout << "DEBUG: Using GE style processing\n" << endl;
      ge mapobject(&fitness,stringlength,binarystring,wrap,ge_report);  // GE style processing
      genes_used = mapobject.get_num_genes_read();
    }
  
  else   // GEP style processing
    {
      //cout << "DEBUG: Using GEP style processing\n" << endl;
      ge_gep mapobject(&fitness,stringlength,binarystring,wrap,ge_report); 
      genes_used = mapobject.get_num_genes_read();
    }
  
  //cout << "Number of Genes used was " << get_genes_used() << "\n";
  
  delete [] gene_d;
  delete [] binarystring;
  set_score(fitness);
  return fitness;
}


double Genome::dummy_evaluate(void)
{
  Random r;
  double d = r.randomintrange(0,87);
  set_score(d);
  return d;

}

// public method to clear current value of a genome
void  Genome::clear(void)
{
  clear(&genome);
}

void  Genome::clear(gvector * g)
{
    g->erase(g->begin(),g->end());
    set_score(0);
    current_length = 0;
}


void  Genome::clear(gvectorlist * g)
{
    g->erase(g->begin(),g->end());
    
}


Genome::~Genome()
{
}

ostream & operator<<(ostream &stream,const Genome &right)
{ 
  gvector::const_iterator iter;
  iter = right.genome.begin();
  stream << *iter++;
  while(iter!= right.genome.end())
    {
      stream << "," << *iter;
      iter++;
    }
  return stream;
}

// send the standard_deviations to a stream terminated with a newline 
void Genome::stream_std(ofstream &stream)
{ 
  gvector::iterator iter;
  
  iter = standard_deviation.begin();

  stream << *iter++;
  while(iter!= standard_deviation.end())
    {
      stream << "," << *iter;
      iter++;
    }
  stream << "\n";
  
}


void Genome::get_genome_value(char genome_val[])
{

  gvector::iterator iter;
  iter = genome.begin();
  char temp_string[MAX_NO_CHARS_GENE];
  char terminator[2] = " ";
  sprintf(temp_string,"%.3f",(double)*iter++);
  strcat(genome_val,temp_string);
  while(iter!= genome.end())
    {
      sprintf(temp_string,",%.3f",(double)*iter);
      strcat(genome_val,temp_string);
      iter++;
    }
  strcat(genome_val,terminator);
}


Genome & Genome::operator=(const Genome &right) 
{
  max_length = right.max_length;
  min_length = right.min_length;
  max_gene_value = right.max_gene_value;
  wrap = right.wrap;
  ge_report = right.ge_report;
  bias = right.bias;
  current_length = right.current_length;
  status = right.status;
  for(int i =0; i < NUM_OF_OPERATORS;i++)
    {
      selector_bias[i][0] = right.selector_bias[i][0];
      selector_bias[i][1] = right.selector_bias[i][1];
      
    }
  
  clear(&genome);
  clear(&neighbour_genome);
  copy(right.genome.begin(), right.genome.end(), back_inserter(this->genome));
  copy(right.genome.begin(), right.genome.end(), back_inserter(this->neighbour_genome));
  clear(&standard_deviation);
  copy(right.standard_deviation.begin(), right.standard_deviation.end(), back_inserter(this->standard_deviation));
  score = right.score;
  score_delta = right.score_delta;
  tenure = right.tenure;
  genes_used = right.genes_used;
  number_of_wins = right.number_of_wins;
  grammatical_processing = right.grammatical_processing;
  return *this;
}



bool Genome::operator==(const Genome &right) const
{
 return(equal(right.genome.begin(), right.genome.end(), genome.begin()));
}

bool Genome::operator!=(const Genome &right)
{
 return(!equal(right.genome.begin(), right.genome.end(), genome.begin()));
}


bool  operator>(const Genome &left,const Genome &right) 
{
  bool result;
  if(left.score > right.score)
    result = true;
  else
    result = false;
  return result;
}


bool  operator<(const Genome &left,const Genome &right) 
{
  bool result;
  if(left.score < right.score)
    result = true;
  else
    result = false;
  return result;
}

bool operator>=(const Genome &left,const Genome &right) 
{
  bool result;
  if(left.score >= right.score)
    result = true;
  else
    result = false;
  return result;
}




// The operators always work on the neighbour_genome
// change this so that there are up to 10 selectable operators
// an operator is identified by a selector_type which is passed to a mutation object





gvector &  Genome::get_neighbour_genome ()
{
  Random r;
  int n = r.randomint(101);
  if(n <= selector_bias[0][0] )
    mutate_genome((MUTATOR)selector_bias[0][1]);   
  else if(n > selector_bias[0][0] && n < (selector_bias[1][0]))
    mutate_genome((MUTATOR)selector_bias[1][1]); 
  else if (n >= (selector_bias[1][0]) && (n < (selector_bias[2][0])))
    mutate_genome((MUTATOR)selector_bias[2][1]); 
  else if (n >= (selector_bias[2][0] ) && (n < (selector_bias[3][0] )))
    mutate_genome((MUTATOR)selector_bias[3][1]); 
  else if (n >= (selector_bias[3][0] ) && (n < (selector_bias[4][0] )))
    mutate_genome((MUTATOR)selector_bias[4][1]); 
  else
    mutate_genome((MUTATOR)selector_bias[5][1]);
  return this->neighbour_genome;  
}



void Genome::mutate_genome(MUTATOR mut_type)
{
  Mutation m;
  switch(mut_type)
    {
    case Force_up:
      m.force_gene_up(this);
      break;
    case Force_down:
      m.force_gene_down(this);
      break;
    case Shrink:
      m.shrink_genome(this);
      break;
    case Grow:
      m.grow_genome(this);
      break;
    case Multiple_mutate:
      m.multiple_mutate_genome(this);
      break;
    case Multiple_mutate_fixed:
      m.multiple_mutate_genome_fixed(this);
      break;
    case Mutate:
      m.mutate_genome(this);
      break;
    case EP_Mutate:
      m.EP_mutate_genome(this);
      m.EP_mutate_strategy_variables(this);
      break;
    case EP_Mutate_classic_adaptive:
      m.EP_mutate_genome_classic_adaptive(this);
      break;
    case EP_Mutate_with_bias:
      m.EP_mutate_genome_classic_adaptive_with_bias(this);
      break;
    case EP_Mutate_non_random:
      m.EP_mutate_non_random_with_bias(this);
      break;
    }
}

void  Genome::generate_neighbourhood_genomes (gvectorlist * glist)
{
  Mutation m;
  clear(glist);
  for (unsigned int i = 0; i < genome.size(); i ++)
    {
      assert(m.force_gene_up(this,i));        // generate the set of neighbours based on forcing up
      glist->push_back(neighbour_genome); 
      clear(&neighbour_genome);
      copy(genome.begin(), genome.end(), back_inserter(this->neighbour_genome)); // restore the neighbour genome with the original value
    }
  for (unsigned int i = 0; i < genome.size(); i ++)
    {
      assert(m.force_gene_down(this,i));        // generate the set of neighbours based on forcing up
      glist->push_back(neighbour_genome); 
      clear(&neighbour_genome);
      copy(genome.begin(), genome.end(), back_inserter(this->neighbour_genome)); // restore the neighbour genome with the original value
    }
  m.grow_genome(this);
  glist->push_back(neighbour_genome); 
  clear(&neighbour_genome);
  copy(genome.begin(), genome.end(), back_inserter(this->neighbour_genome)); // restore the neighbour genome with the original value  
  m.shrink_genome(this);
  glist->push_back(neighbour_genome); 
  clear(&neighbour_genome);
  copy(genome.begin(), genome.end(), back_inserter(this->neighbour_genome)); // restore the neighbour genome with the original value  
}

// Additional Declarations



//used for generating all neighbours that produce a production rule change
void  Genome::generate_neighbourhood_genomes_pure (gvectorlist * glist)
{
  Mutation m;
  clear(glist);
  for (unsigned int i = 0; i < genome.size(); i ++)
    {
      assert(m.force_gene_up(this,i));        // generate the set of neighbours based on forcing up
      glist->push_back(neighbour_genome); 
      clear(&neighbour_genome);
      copy(genome.begin(), genome.end(), back_inserter(this->neighbour_genome)); // restore the neighbour genome with the original value
    }
  for (unsigned int i = 0; i < genome.size(); i ++)
    {
      assert(m.force_gene_down(this,i));        // generate the set of neighbours based on forcing up
      glist->push_back(neighbour_genome); 
      clear(&neighbour_genome);
      copy(genome.begin(), genome.end(), back_inserter(this->neighbour_genome)); // restore the neighbour genome with the original value
    }
}

// Additional Declarations

void Genome::show_neighbour_genome(void)
{
  show_genome(&neighbour_genome);
}


void Genome::show_standard_deviation(void)
{
  show_genome(&standard_deviation);
}


void Genome::show_genome(gvector * the_gvector)
{
  gvector::iterator iter;
  iter = the_gvector->begin();
  cout << "DEBUG: ";
  while(iter!= the_gvector->end())
    {
      cout  << "," << *iter;
      iter++;
    }
  cout << endl;
}

// returns the value of the codon at index i

// returns the value of the codon at the specified index , returns -1 id index is greater than the length of the genome
// there is probably a more elegant way of doing this using STL

double Genome::get_codon_value(unsigned int index)
{
  gvector::iterator iter;
  iter = genome.begin();
  unsigned int cnt = 0;
  double codon_value = 0;
  
  if(index > genome.size())
    codon_value = -1;
  if(codon_value != -1)
    {
    
      while(cnt < index)
	{
	  codon_value = *iter;
	  iter++;
	  
	  cnt++;
	}
    }
  return codon_value;
  
}

double Genome::get_stdev_value(unsigned int index)
{
  gvector::iterator iter;
  iter = standard_deviation.begin();
  unsigned int cnt = 0;
  double stdev_value = 0;
  
  if(index > standard_deviation.size())
    stdev_value = -1;
  if(stdev_value != -1)
    {
    
      while(cnt < index)
	{
	  stdev_value = *iter;
	  iter++;
	  cnt++;
	}
    }
  return stdev_value;
  
}

// sets the value of the codon at index i to value

// sets the value of the codon at the specified index , returns false if index or value are too large 


int Genome::set_codon_value(unsigned int index , double value)
{
  gvector::iterator iter;
  status = OKAY;
  iter = genome.begin();
  unsigned int cnt = 1;
  if((index > genome.size()) || (value > get_max_gene_value()))
     status  = NOT_OKAY;
  if(status)
    {
    
      while(cnt < index)
	{
	
	  iter++;
	  cnt++;
	}
      *iter = value;
            
      //sync_to_neighbour();  // I believe that the genome should not have this responsibility 
    }
  return status;
  
}

int Genome::set_stdev_value(unsigned int index , double value)
{
  gvector::iterator iter;
  status = OKAY;
  iter = standard_deviation.begin();
  unsigned int cnt = 1;
  if(index > standard_deviation.size() )
     status  = NOT_OKAY;
  if(status)
    {
    
      while(cnt < index)
	{
	
	  iter++;
	  cnt++;
	}
      *iter = value;
    }
  return status;
  
}

int Genome::set_all_stdev_value(double value)
{
  gvector::iterator iter;
  status = OKAY;
  iter = standard_deviation.begin();
  while(iter != standard_deviation.end())
    {
      *iter = value;
      iter++;
    }
  return status;
  
}

double Genome::get_average_stdev_value(void)
{
  gvector::iterator iter;
  status = OKAY;
  double accumulated_value = 0;
  int i = 0;
  iter = standard_deviation.begin();
  while(iter != standard_deviation.end())
    {
      accumulated_value += *iter;
      iter++;
      i++;
      
    }
  return accumulated_value/i;
  
}

// increments the value of the codon at index i by value

// sets the value of the codon at the specified index to current value plus value 
// returns false if index or value are too large 

int Genome::increment_codon_value(unsigned int index , double value)
{
  gvector::iterator iter;
  status = OKAY;
  iter = genome.begin();
  unsigned int cnt = 1;
  if((index > genome.size()) || (value > get_max_gene_value()))
     status  = NOT_OKAY;
  if(status)
    {
       while(cnt < index)
	{
	
	  iter++;
	  cnt++;
	}
      *iter = *iter + value;
      if(*iter > get_max_gene_value())
	*iter = 0;
      
      //sync_to_neighbour();  // I believe that the genome should not have this responsibility 
    }
  return status;
  
}

// returns 1 on success , 0 otherwise
int Genome::add_codon(double value)
{
  status = OKAY;
  if((!(int)genome.size() < max_length) ||  (value > get_max_gene_value()))
    status = NOT_OKAY;
  else
    genome.push_back(value);
  return status;
  
}



// returns 1 on success , 0 otherwise
int Genome::add_stdev(double value)
{
  status = OKAY;
  standard_deviation.push_back(value);
  return status;
  
}

// reduces a genome from its current size to amount
int Genome::reduce(int amount)
{
  if(current_length <= amount)
    status = NOT_OKAY;
  
  else
    {
      int new_length = current_length -amount;
      for(int i = 0; i < new_length ; i++)
	genome.pop_back();
      status = OKAY;
      
    }
  
  return status;
}



// sync insures that genome and neighbour genome are identical
// the value of genome is copied to neighbour

void Genome::sync_to_genome(void)
{
  clear(&neighbour_genome);  
  copy(genome.begin(), genome.end(), back_inserter(neighbour_genome));
}


// sync insures that  neighbour and  genome are identical
// the value of neighbour is copied to genome

void Genome::sync_to_neighbour(void)
{
  clear(&genome);  
  copy(neighbour_genome.begin(), neighbour_genome.end(), back_inserter(genome));
}







































