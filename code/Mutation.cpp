// Mutation
#include "Mutation.hpp"
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
#include <math.h>



extern "C" int  string_to_doublearray(char c[],int double_array[]);

// Class Mutation 


Mutation::Mutation()
{
}

Mutation::Mutation(const Mutation &right)
{

}

Mutation::~Mutation()
{
}

// randomly selects a gene a carries out mutation by 
// generating a new random value
void Mutation::mutate_genome(Genome * g)
{
  gvector::iterator iter;
  Random r1,r2;
  int neighbour_genome_current_length;
  neighbour_genome_current_length = g->neighbour_genome.size();
  int i = 0;
  iter = g->neighbour_genome.begin();
  int n1 = r1.randomint(neighbour_genome_current_length); 
  int n2 = r2.randomint(g->get_max_gene_value());
  while(i < n1)
    {
      i++;
      iter++;
    }
  *iter = (double)n2;
  if(*iter > g->get_max_gene_value())
    *iter = 0;
  //cout << "DEBUG: Mutate \n";
}


// this features the normal EP mutation more commonly associated with continous  data
// The strategy variables and the genome itself is nutated
void Mutation::EP_mutate_genome(Genome * g)
{
  gvector::iterator itern, iters;
  Random r; 
  double N_0_1 = r.normal_distr_rand_var_1_0(); 
  itern = g->neighbour_genome.begin(); 
  iters = g->standard_deviation.begin(); 
  //cout << "DEBUG: Using EP mutation \n";
  
  while(itern!= g->neighbour_genome.end()) 
    {   
      //cout << (*itern) << "  ";
      //cout << (*iters) << "   ";
      //cout << N_0_1 << "  ";
      //cout <<  sqrt(*iters) << "  "  <<  (sqrt(*iters) * N_0_1) << endl;     
      *(itern) = *(itern) + sqrt(*iters) * N_0_1; 
      if(*(itern) > g->get_max_gene_value())
	*(itern) = 0;
      if(*(itern) <  0)
	*(itern) = g->get_max_gene_value();
      itern++; 
      iters++; 
    }  

}

// features classic EP mutation. Single Strategy variables used,
// The genes mutation rate evolves with the genome , it is randomly perturbed
// at each generation and then applied. 
void Mutation::EP_mutate_genome_classic_adaptive(Genome * g)
{
  // perturb the mutation rate
  Random r;
  int n;
  n = r.randomint(g->get_mutation_rate_range()); 
  //n = r.randomint(20);
  g->set_mutation_rate(n); 
  // mutate the genome using the new mutation rate
  multiple_mutate_genome_fixed(g);
}


// features classic EP mutation. Two Strategy variables used,
// The genes mutation rate evolves with the genome , it is randomly perturbed
// at each generation and then applied.  
// The genes mutation bias evolves with the genome , it is randomly perturbed
// at each generation and then applied. 
void Mutation::EP_mutate_genome_classic_adaptive_with_bias(Genome * g)
{
  // perturb the mutation rate
  Random r;
  int n1,n2;
  n1 = r.randomint(g->get_mutation_rate_range()); 
  //n = r.randomint(20);
  n2 = r.randomint(g->get_current_length()); 
  g->set_mutation_rate(n1); 
  g->set_mutation_bias(n2); 
  // mutate the genome using the new mutation rate
  multiple_mutate_genome_fixed_with_bias(g,n2);
}





// features classic EP mutation. Two Strategy variables used,
// The genes mutation rate evolves with the genome , it is non-randomly perturbed
// at each generation and then applied.  
// The genes mutation bias evolves with the genome , it is non-randomly perturbed
// at each generation and then applied. 
// In this scenario the mutation_range is the amount by which the mutation rate can decline
void Mutation::EP_mutate_non_random_with_bias(Genome * g)
{
  // perturb the mutation rate
  Random r;
  int n1,n2,n3;
  n1 = r.randomint(g->get_mutation_rate_range()); 
  //n = r.randomint(20);
  n3 = (g->get_mutation_rate() - n1);
  if (n3 < 0)
    n3 = 1;
  n2 =  g->get_mutation_bias() + 1;
  if(n2 > g->get_current_length())
    n2 = g->get_current_length() - 10; 
  g->set_mutation_rate(n3); 
  g->set_mutation_bias(n2); 
  // mutate the genome using the new mutation rate
  multiple_mutate_genome_fixed_with_bias(g,n2);
}


// mutate the strategy variables using mutation associated with continous data 
void Mutation::EP_mutate_strategy_variables(Genome * g)
{

  gvector::iterator  iters;
  Random r; 
  //cout << "DEBUG: Using EP strategy mutation \n";
  double N_0_1 = r.normal_distr_rand_var_1_0(); 
  iters = g->standard_deviation.begin(); 
  double tau = (double)1/(sqrt(2 * g->get_current_length()) );
  double tau_dash = (double)1/ sqrt((2 * sqrt(g->get_current_length())) );
  while(iters!= g->standard_deviation.end())
    {   
      double N_0_1_i = r.normal_distr_rand_var_1_0(); 
      *(iters) = *(iters) * exp((tau_dash * N_0_1) +  (tau * N_0_1_i));
      //cout << " DEBUG : " << (*iters) << " tau " << tau  << " N_0_1 " << N_0_1 <<  " tau_dash " << tau_dash << " N_0_1_i " << N_0_1_i << " exp " << exp((tau_dash * N_0_1) +  (tau * N_0_1_i)) << endl;
      iters++; 
    }  

}








// mutates the genome at various points as determined by the mutation rate
void Mutation::multiple_mutate_genome(Genome * g)
{
  gvector::iterator iter;
  Random r1,r2,r3;
  int n3,n4,n5;
  n3 = r3.randomint((int)g->get_mutation_rate());   
  if(n3 == 0)
    n5 = 0;
  else
    {
      n4 = 100/n3;             // mutation rate as a fraction
      n5 =  g->neighbour_genome.size()/n4; // number of codons to mutate
    }
  
  for(int i = 0;i < n5;i++)
    {
      int neighbour_genome_current_length;
      neighbour_genome_current_length = g->neighbour_genome.size();
      int i = 0;
      iter = g->neighbour_genome.begin();
      int n1 = r1.randomint(neighbour_genome_current_length); 
      int n2 = r2.randomint(g->get_max_gene_value());
      while(i < n1)
	{
	  i++;
	  iter++;
	}
      *iter = (double)n2;
      if(*iter > g->get_max_gene_value())
	*iter = 0; 
    }
}

  // this differs from above in that the mutation rate as given is used. The standard version uses a randomly selected rate upto 
  // a maximum of the given rate

void Mutation::multiple_mutate_genome_fixed(Genome * g)
{
  gvector::iterator iter;
  Random r1,r2,r3;
  int n3,n4,n5;
  n3 = (int)g->get_mutation_rate(); // mutation rate as a percentage
  if(n3 == 0)
    n5 = 0;
  else
    {
      n4 = 100/n3;             // mutation rate as a fraction
      n5 =  g->neighbour_genome.size()/n4; // number of codons to mutate
    }
  
  //cout <<  "n3: " << n3 << " n4; " << n4 << " n5: " << n5 << endl;
  for(int i = 0;i < n5;i++)
    {
      int neighbour_genome_current_length;
      neighbour_genome_current_length = g->neighbour_genome.size();
      int ii = 0;
      iter = g->neighbour_genome.begin();
      int n1 = r1.randomint(neighbour_genome_current_length); 
      int n2 = r2.randomint(g->get_max_gene_value());
      while(ii < n1)
	{
	  ii++;
	  iter++;
	}
      *iter = (double)n2;
      if(*iter > g->get_max_gene_value())
	*iter = 0; 
    }  
  //cout << "DEBUG: Multiple mutate \n";
}


void Mutation::multiple_mutate_genome_fixed_with_bias(Genome * g,int bias)
{
  gvector::iterator iter;
  //double bias_frac = (double)((double)bias/100.00);
  //cout << " bias frac is " << bias_frac << endl;
  
  //int start_point = (int)( (double)bias_frac * (double)g->get_current_length());
  int start_point = bias;
  
  //cout << "Start point is " << start_point << " bias was " << bias << endl;
  Random r1,r2,r3;
  int n3,n4,n5;
  n3 = (int)g->get_mutation_rate(); // mutation rate as a percentage
  cout << "Mutation Rate " << n3 << " start_point " << start_point << endl;
  
  if(n3 == 0)
    n5 = 0;
  else
    {
      n4 = 100/n3;             // mutation rate as a fraction
      n5 =  g->neighbour_genome.size()/n4; // number of codons to mutate
    }
  
  //cout <<  "n3: " << n3 << " n4; " << n4 << " n5: " << n5 << endl;
  for(int i = 0;i < n5;i++)
    {
      int neighbour_genome_current_length;
      neighbour_genome_current_length = g->neighbour_genome.size();
      int ii = 0;
      iter = g->neighbour_genome.begin();
      int n1 = r1.randomintrange(start_point,neighbour_genome_current_length);
      //cout << "n1 is " << n1 << "start point was " << start_point << endl;
      
      int n2 = r2.randomint(g->get_max_gene_value());
      while(ii < n1)
	{
	  ii++;
	  iter++;
	}
      //cout << "length is " << neighbour_genome_current_length <<  "  n1 is " << n1 << endl;
      
      *iter = (double)n2;
      if(*iter > g->get_max_gene_value())
	*iter = 0; 
      //cout << "DEBUG: Multiple mutate, mutated codon " << n1 << endl;
    }  

}


void Mutation::force_gene_up(Genome * g)
{
  gvector::iterator iter;
  Random r;
  int neighbour_genome_current_length;
  neighbour_genome_current_length = g->neighbour_genome.size();
  int i = 0;
  iter = g->neighbour_genome.begin();
  int n = r.randomint(neighbour_genome_current_length);
  while(i < n)
    {
      i++;
      iter++;
    }
  *iter = *iter + 1;
  if(*iter > g->get_max_gene_value())
    *iter = 0;
  //cout << "DEBUG: Force gene up \n";   
}

int  Mutation::force_gene_up(Genome * g,int gene_num)
{
  gvector::iterator iter;
  int neighbour_genome_current_length;
  status = OKAY;
  neighbour_genome_current_length = g->neighbour_genome.size();
  if(gene_num > neighbour_genome_current_length || gene_num < 0)
    {
       status = NOT_OKAY;
       cout << "Error: gene is outside range \n";
    }
  if(status)
    {
      int i = 0;
      iter = g->neighbour_genome.begin();
      while(i < gene_num)
	{
	  i++;
	  iter++;
	}
      *iter = *iter + 1;
      if(*iter >g->get_max_gene_value())
	*iter = 0;
    }
  
  return status;
  //cout << "DEBUG: Force gene up \n";
  
}

void Mutation::force_gene_down(Genome * g)
{
  gvector::iterator iter;
  Random r;
  int neighbour_genome_current_length;
  neighbour_genome_current_length = g->neighbour_genome.size();
  int i = 0;
  iter = g->neighbour_genome.begin();
  int n = r.randomint(neighbour_genome_current_length+1);
  while(i < n)
    {
      i++;
      iter++;
    }
  *iter = *iter - 1;
  if(*iter <  0)
    *iter = g->get_max_gene_value();
  //cout << "DEBUG: Force gene down \n";  
}


int Mutation::force_gene_down(Genome * g,int gene_num)
{
  gvector::iterator iter;
  int neighbour_genome_current_length;
  status = OKAY;
  neighbour_genome_current_length = g->neighbour_genome.size();
  if(gene_num > neighbour_genome_current_length || gene_num < 0)
    {
       status = NOT_OKAY;
       cout << "Error: gene is outside range \n";
    }
  
  if(status)
    {
      int i = 0;
      iter = g->neighbour_genome.begin();
      while(i < gene_num)
	{
	  i++;
	  iter++;
	}
      *iter = *iter - 1;
      if(*iter <  0)
	*iter = g->get_max_gene_value();
    }
  //cout << "DEBUG: Force down \n";
  return status;
}

void Mutation::shrink_genome(Genome * g)
{
  int neighbour_genome_current_length;
  neighbour_genome_current_length = g->neighbour_genome.size();
  if(neighbour_genome_current_length > g->get_min_length())
    {
      //cout << "DEBUG: Shrinking \n";
      g->neighbour_genome.pop_back();
    }
  
}


// reduces a genome from its current size to amount
int Mutation::reduce(Genome * g,int amount)
{
  if(g->get_current_length() <= amount)
    status = NOT_OKAY;
  
  else
    {
      int new_length = g->get_current_length() -amount;
      for(int i = 0; i < new_length ; i++)
	g->genome.pop_back();
      status = OKAY;
      
    }
  
  return status;
}

void Mutation::grow_genome(Genome * g)
{
  Random r;
  int neighbour_genome_current_length;
  neighbour_genome_current_length = g->neighbour_genome.size();
  if(neighbour_genome_current_length <  g->get_max_length())
    {
     double n = (double)r.randomint(g->get_max_gene_value() + 1);
     g->neighbour_genome.push_back(n);
    }
  //cout << "DEBUG: Grow \n";  
}




















































