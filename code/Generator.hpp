#ifndef generator_h
#define generator_h 1


#include <stdio.h>
#include <iostream.h>
#include "defines.h"
#include <list>
#include "Genome.hpp"

typedef vector<Genome> genomelist;


class Generator 
{

public:
  Generator();
  
  Generator(const Generator &right);
  
  ~Generator();
  int  run(char filename[]);
  int process(void);
  int save_generator_data(char filename[]);
  int show_list_solutions(void);
  int show_list_neighbours(void);
  int show_genome(gvector * the_gvector);
  int create_neighbourhood();
  int show_genome_neighbourhood();
  void  clear(genomelist * g);
  
  
protected:

  FILE *config_fileptr; 
  int status;
  
private:
  Genome new_genome;
  genomelist glist;
  genomelist genome_neighbourhood;  
  gvectorlist all_neighbour_genomes;



  // Data Members for Class Attributes

public:
  


};


// Class configuration 




#endif










