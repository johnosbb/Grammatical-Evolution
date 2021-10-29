#include <stdlib.h>
#include <iostream.h>
#include "defines.h"
#include "Random.hpp"
#include <stdio.h>
#include <time.h>
#include <fstream.h>
#include <new.h>
#include <list>
#include "Generator.hpp"
#include "AnalyserConfig.hpp"
#include "Genome.hpp"
#include <assert.h>
#include <algorithm>
#include <functional>


//function prototypes
#define REPORT_LEVEL 0
#define PRINT_SOLUTION 0

typedef vector<Genome> genomelist;

Generator::Generator()
{
}

Generator::Generator(const Generator &right)
{
}

Generator::~Generator()
{
}

//main
int Generator::run(char filename[])
{

  int status = OKAY;
  cout << "--------------- Generator ------------------\n\n";
  AnalyserConfig ac;
  ac.load_file(filename);
  ac.load_data(this->glist,1);   // wrap is on by default
  process();
  //status = save_generator_data(filename);
  return status;
}



int Generator::save_generator_data(char filename[])
{
  ofstream save_generator_file;
  int status = OKAY;
  char generator_filename[50];
  strcpy(generator_filename,filename);
  strcat(generator_filename,".generator.txt");
  save_generator_file.open(generator_filename,ios::app);  
  if(!save_generator_file.is_open())
    {
      cout << "Error opening file " << generator_filename  << endl;
      status = NOT_OKAY;     
    }
  genomelist::iterator iterl;
  iterl = genome_neighbourhood.begin();
  cout << "Genome Neighbourhood:__________Score_\n";
  while(iterl!= genome_neighbourhood.end())
    {
      save_generator_file  <<  *(iterl) << "  " << (*iterl).get_score() << endl;
      iterl++;
    }
  save_generator_file.close();
  return status;
} 




int Generator::show_list_solutions(void)
{
  genomelist::iterator iter;
  iter = glist.begin();
  while(iter!= glist.end())
    {  
      cout << *(iter) << "  "  << (*iter).get_score() << endl;
      iter++;
    }
  return OKAY;
  
}



int Generator::show_list_neighbours(void)
{
  gvectorlist::iterator iterl;
  iterl = all_neighbour_genomes.begin();
  while(iterl!= all_neighbour_genomes.end())
    {
      show_genome(&(*iterl));
      iterl++;
    }
  return OKAY;
  
}





int  Generator::show_genome(gvector * the_gvector)
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
  return OKAY;
  
}




// iterate through all genomes in the file generating a neighbourhood for each
int Generator::process(void)
{
  genomelist::iterator iter;
  iter = glist.begin();
  while(iter!= glist.end())
    {  
      (*iter).generate_neighbourhood_genomes_pure(&all_neighbour_genomes); // all_neigh is a gvectorlist
      //show_list_neighbours();
      (*iter).configure(1,REPORT_LEVEL,0);   // wrap on , desired report level
      (*iter).evaluate();
      create_neighbourhood();
#ifdef PRINT_SOLUTION
      cout << *iter << "  " << (*iter).get_score() << endl;
#endif
      show_genome_neighbourhood();
      iter++;
    }
  return OKAY;
  
}

// iterate through the gvectorlist making each a genome and then evaluating them in turn

int Generator::create_neighbourhood()
{
  gvectorlist::iterator iterl;
  iterl = all_neighbour_genomes.begin();
  clear(&genome_neighbourhood);
  while(iterl!= all_neighbour_genomes.end())
    {
        new_genome.create(*iterl);
        new_genome.configure(1,REPORT_LEVEL,0);   // wrap on , desired report level
	new_genome.evaluate();
	genome_neighbourhood.push_back(new_genome);
	iterl++;
    }
  sort(genome_neighbourhood.begin(),genome_neighbourhood.end());
  reverse(genome_neighbourhood.begin(),genome_neighbourhood.end());

  return OKAY;
  
}





int Generator::show_genome_neighbourhood()
{
  genomelist::iterator iterl;
  iterl = genome_neighbourhood.begin();
  //cout << "Genome Neighbourhood:__________Score____Used______Length____Wrap\n";
  while(iterl!= genome_neighbourhood.end())
    {
      cout <<  *(iterl) << "  " << (*iterl).get_score() <<  "  " << (*iterl).get_genes_used() << "  " << (*iterl).get_current_length() << "  " << (*iterl).get_wrap() << endl;
      iterl++;
    }
    cout << endl;
  return OKAY;
}




void  Generator::clear(genomelist * g)
{
    g->erase(g->begin(),g->end());
    
}



