#ifndef analyser_h
#define analyser_h 1


#include <stdio.h>
#include <iostream.h>
#include "defines.h"
#include <list>
#include "Genome.hpp"

typedef vector<Genome> genomelist;

class Analyser 
{

  public:
      Analyser();

      Analyser(const Analyser &right);

      ~Analyser();
      int  run(char filename[],int wrap_flag);
      int process(void);
      int save_analyser_data(char filename[]);
      int show_list(void);
      genomelist glist;
  
  protected:

      FILE *config_fileptr; 
      int status;

  private:
  




    // Data Members for Class Attributes

public:
  


};


// Class configuration 




#endif










