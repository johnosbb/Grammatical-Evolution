

#ifndef analyserconfig_h
#define analyserconfig_h 1


#include <stdio.h>
#include <iostream.h>
#include "defines.h"
#include <Genome.hpp>


typedef vector<Genome> genomelist;

class AnalyserConfig 
{

  public:
      AnalyserConfig();

      AnalyserConfig(const AnalyserConfig &right);

      virtual ~AnalyserConfig();
      int load_file(char filename[]);
      int load_data(genomelist & g,int wrap_flag);
      int set_common_parameters(char value[],genomelist & g,int wrap_flag);
      genomelist glist;
  
  protected:

      FILE *config_fileptr; 
      int status;

  private:
  




    // Data Members for Class Attributes

public:
      char initial_genome_value[MAX_GENOME_LENGTH * MAX_NO_CHARS_GENE];
      char capture_data[100];
      int capture_data_list[100];

};


// Class configuration 




#endif










