
// AnalyserConfig
#include "AnalyserConfig.hpp"


// Class AnalyserConfig 


#include <string.h>
#include <iostream.h>
#include "defines.h"
#include <stdio.h>
#include <stdlib.h>  // for atoi
#include "defines.h"
#include <string.h>

#define REPORT_LEVEL 2

extern "C" int  string_to_doublearray(char c[],int double_array[]);

AnalyserConfig::AnalyserConfig()
{
}

AnalyserConfig::AnalyserConfig(const AnalyserConfig &right)
{
}


AnalyserConfig::~AnalyserConfig()
{
}


int AnalyserConfig::load_file (char filename[])
{

  cout << ".......Loading configuration file " << filename << endl;
  if( (config_fileptr = fopen(filename,"r")) == NULL)
    {
      cout << "Error opening configuration file " << filename << endl;
      status = NOT_OKAY;
    }
  else
    status = OKAY;

  return status;
}




// Additional Declarations


int AnalyserConfig::load_data(genomelist & g,int wrap_flag)
{
  char value[(CFG_MAX_VALUE_SIZE*4) + 1];
  while (fscanf(config_fileptr,"%s",value) != EOF)
    {
      //fprintf(stderr,"Reading value %s length %d from file\n",value,strlen(value));
      
      if(!(set_common_parameters(value,g,wrap_flag)))
	 {
         status = NOT_OKAY;
         cout << "...... error occured while reading configuration file \n";
	 break;
	 } 	  
	     
    }
  fclose(config_fileptr);
  return status;
  
}


int AnalyserConfig::set_common_parameters(char value[],genomelist & g,int wrap_flag)
{
  int sel_bias[NUM_OF_OPERATORS][2];
  status = OKAY;
  Genome a_genome;
  //cout << "Setting Wrap to " << wrap_flag << endl;
  
  a_genome.configure(wrap_flag,1,sel_bias,0,0,0);
  strcpy(initial_genome_value,value);
  strcat(initial_genome_value,"\n");
  a_genome.create(initial_genome_value);
  a_genome.configure(wrap_flag,REPORT_LEVEL,0);   // wrap on , desired report level
  //a_genome.evaluate();
  //int used = a_genome.get_genes_used();
  //if(used < a_genome.get_current_length())
  //	  assert(a_genome.reduce(used));
  g.push_back(a_genome);   
  return status;
}




























