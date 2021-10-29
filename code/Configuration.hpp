

#ifndef configuration_h
#define configuration_h 1


#include <stdio.h>
#include <iostream.h>
#include "defines.h"


//	the configuration struct will hold settings applicable
//	to all sub classes of metaheuristic.
//
//	Typical contents will be:
//	initial length of genome.
//	initial length variation range.
//	metaheuristic type.
//	zero improvement accept flag setting.
//	wrap on off flag
//	configuration for a starting genome.
//	flag to set biased annealing on or off.
//	The configuration file will also contain a list of
//	trials for which the search trajectory will be captured.


class Configuration 
{
  
public:
      Configuration();
  
  Configuration(const Configuration &right);
  
      virtual ~Configuration();
  virtual int selftest(void);
  
  int load_file(char filename[]);
  int load_data(void);
  int set_common_parameters(char parameter[], char value[]);
  virtual int set_specific_parameters(char parameter[], char value[]);
  
  
protected:
  
  FILE *config_fileptr; 
  int status;
  
private:
  
  
  
  
  
  // Data Members for Class Attributes
  
public:
  char initial_genome_value[MAX_GENOME_LENGTH * MAX_NO_CHARS_GENE ];
  char initial_population_config[20]; // this will be a file name
  char capture_data[100];
  double capture_data_list[100];
  int capture;     // flag indicating whether capture should operate for a particular trial
  int capture_status;   // flag used to inform the metaheuristic of the need to check the capture array
  int iterations;
  int maximum_iterations;
  int maximum_evaluations;
  int max_gene_value;
  int initial_length;
  int maximum_genome_length;
  int initial_length_variation_range;
  int wrap;
  int ge_report;
  int mutation_selector [NUM_OF_OPERATORS][2]; 
  int zero_improvement_accept;  
  int mutation_rate;  
  int mutation_rate_range;
  int mutate_cnt;   // an index for the mutation_selector array
  int style; // gramatical processing style 0 is GE 1 is GEP
  int length_style;
  int recombination_type;
  int number_of_parents;
  

};


// Class configuration 




#endif










