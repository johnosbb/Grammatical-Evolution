
// Configuration
#include "Configuration.hpp"


// Class Configuration 


#include <string.h>
#include <iostream.h>
#include "defines.h"
#include <stdio.h>
#include <stdlib.h>  // for atoi
#include "defines.h"


extern "C" int  string_to_doublearray(char c[],double double_array[]);

Configuration::Configuration()
      : capture(0),
        capture_status(0),
        iterations(10),
	maximum_iterations(900000),
	maximum_evaluations(1900000),
	max_gene_value(MAX_GENE_VALUE),
	initial_length(0),
        maximum_genome_length(MAX_GENOME_LENGTH),
	initial_length_variation_range(0),
	wrap(1),
	ge_report(0), 
	zero_improvement_accept(0),
        mutation_rate(3),
	mutation_rate_range(20),
	mutate_cnt(0),
	style(0),
	length_style(0),
	recombination_type(0),
	number_of_parents(10)
       
	

{
  strcpy(initial_genome_value,"empty");
  strcpy(capture_data,"empty");  
  strcpy(initial_population_config,"empty");
  for(int i = 0;i < NUM_OF_OPERATORS;i++)
    {
      mutation_selector[i][0] = 0;
      mutation_selector[i][1] = 0;      
    }
}

Configuration::Configuration(const Configuration &right)
{
  for(int i = 0;i < NUM_OF_OPERATORS;i++)
    {
      mutation_selector[i][0] = 0;
      mutation_selector[i][1] = 0;      
    }
  
  
}


Configuration::~Configuration()
{
}


int Configuration::load_file (char filename[])
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


int Configuration::load_data(void)
{
  char parameter[CFG_MAX_PARAMETER_SIZE+1];
  char value[CFG_MAX_VALUE_SIZE+1];
  while ( fscanf(config_fileptr, "%s %s",parameter,value) != EOF)
    {
      if(!(set_common_parameters(parameter,value)))
	 {
	   if(!(set_specific_parameters(parameter,value)))
	     {
	       status = NOT_OKAY;
	       cout << "Error: Unrecognisable common parameter - " << parameter << " " << value << endl;
	       cout << "...... error occured while reading configuration file \n";
	       break;
	     } 	  
	 }
     
    }
  fclose(config_fileptr);
  return status;
  
}


int Configuration::set_common_parameters(char parameter[], char value[])
{

  bool match = false;


  
  // first check for comments
  if(parameter[0] == '#')
    {
      cout << " comment , ignored : " <<  parameter << "  " << value <<  "\n";      
      match =true;
    }
  
  
  else if(strcmp(parameter,"genome")==0)
    {
      strcpy(initial_genome_value,value);
      strcat(initial_genome_value,"\n");
      cout << " initial_genome_value: " <<  initial_genome_value << "\n";
      match = true;
      
    }

 else if(strcmp(parameter,"initial_population_config")==0)
    {
      strcpy(initial_population_config,value);
      //strcat(initial_population_config,"\n");
      cout << " initial_population_config : " <<  initial_population_config << "\n";
      match = true;
      
    }

  else if(strcmp(parameter,"capture")==0)
    {
      int cnt =0;
      strcpy(capture_data,value);
      strcat(capture_data,"\n");
      string_to_doublearray(capture_data,capture_data_list);
      capture_status = 1;
      
      cout << " capture_data: " ;
      while(capture_data_list[cnt]!= -1)
	 {
	   cout << " " << capture_data_list[cnt++];
	 }
      
      cout <<  "\n";
      match = true;
    }

  else if(strcmp(parameter,"iterations")==0)
    {
      iterations = atoi(value);
      cout << " iterations: " << iterations << "\n";
      match = true;
    }

  else if(strcmp(parameter,"maximum_iterations")==0)
    {
      maximum_iterations = atoi(value);
      cout << " maximum_iterations: " << maximum_iterations << "\n";
      match = true;
    }

  else if(strcmp(parameter,"maximum_evaluations")==0)
    {
      maximum_evaluations = atoi(value);
      cout << " maximum_evaluations: " << maximum_evaluations << "\n";
      match = true;
    }
  else if(strcmp(parameter,"max_gene_value")==0)
    {
      max_gene_value = atoi(value);
      cout << " max_gene_value: " << max_gene_value << "\n";
      match = true;
    }
  else if(strcmp(parameter,"initial_length")==0)
    {
      initial_length = atoi(value);
      cout << " initial_length: " << initial_length << "\n";
      match = true;
    }  
  else if(strcmp(parameter,"maximum_genome_length")==0)
    {
      maximum_genome_length = atoi(value);
      cout << " maximum_genome_length: " << maximum_genome_length << "\n";
      match = true;
    }  
  else if(strcmp(parameter,"initial_length_variation_range")==0)
    {
      initial_length_variation_range = atoi(value);
      cout << " initial_length_variation_range: " << initial_length_variation_range << "\n";
      match = true;
    }

  else if(strcmp(parameter,"style")==0)   // style determines if GEP or GE processing is used
    {
      style =  atoi(value);
      cout << " style: " << style << "\n";
      match = true;
    }

 else if(strcmp(parameter,"length_style")==0)   // style determines if GEP or GE processing is used
    {
      length_style =  atoi(value);
      if(length_style == 1)
	initial_length = maximum_genome_length;
      cout << " length_style: " << length_style << "\n";
      match = true;
    }


  else if(strcmp(parameter,"wrap")==0)
    {
      wrap =  atoi(value);
      cout << " wrap: " << wrap << "\n";
      match = true;
    }



  else if(strcmp(parameter,"ge_report")==0)
    {
      ge_report = atoi(value);
      cout << " ge_report: " << ge_report << "\n";
      match = true;
    }

  else if(strcmp(parameter,"zero_improvement_accept")==0)
    {
      zero_improvement_accept = atoi(value);
      cout << " zero_improvement_accept: " << zero_improvement_accept << "\n";
      match = true;
    }
  else if(strcmp(parameter,"mutation_rate")==0)
    {
      mutation_rate = atoi(value);
      cout << " mutation_rate: " << mutation_rate << "\n";
      match = true;
    }
  else if(strcmp(parameter,"mutation_rate_range")==0)
    {
      mutation_rate_range = atoi(value);
      cout << " mutation_rate_range: " << mutation_rate_range << "\n";
      match = true;
    }
 else if(strcmp(parameter,"number_of_parents")==0)
    {
      number_of_parents = atoi(value);
      cout << " number_of_parents: " << number_of_parents << "\n";
      match = true;
    }
 else if(strcmp(parameter,"recombination_type")==0)
    {
      if(strcmp(value,"discrete")==0) 
	recombination_type = 1;
      else if(strcmp(value,"intermediate")==0) 
	recombination_type = 2;
      else
	recombination_type = 0;
      cout << " recombination_type: " << recombination_type << "\n";
      match = true;
    }
  //operators

  else if(strcmp(parameter,"forceup")==0)
    {
     if(mutate_cnt > 0)
       mutation_selector[mutate_cnt][0] = atoi(value) + mutation_selector[mutate_cnt-1][0];   // probability of selecting forceup operator
     else
       mutation_selector[mutate_cnt][0] = atoi(value);
     
      mutation_selector[mutate_cnt++][1] = Force_up;
      cout << " forceup: " << mutation_selector[mutate_cnt-1][0] << "% \n";
      match = true;
    } 
  else if(strcmp(parameter,"forcedown")==0)
    {
     if(mutate_cnt > 0)
       mutation_selector[mutate_cnt][0] = atoi(value) + mutation_selector[mutate_cnt-1][0];   // probability of selecting forcedown operator
     else
       mutation_selector[mutate_cnt][0] = atoi(value);
      mutation_selector[mutate_cnt++][1] = Force_down;
      cout << " forcedown: " << mutation_selector[mutate_cnt-1][0]  << "% \n";
      match = true;
    }
  else if(strcmp(parameter,"shrink")==0)
    {
     if(mutate_cnt > 0)
       mutation_selector[mutate_cnt][0] = atoi(value) + mutation_selector[mutate_cnt-1][0];   // probability of selecting shrink genome operator
     else
       mutation_selector[mutate_cnt][0] = atoi(value);
      mutation_selector[mutate_cnt++][1] = Shrink;
      cout << " shrink: " <<  mutation_selector[mutate_cnt-1][0]  << "% \n";
      match = true;
    } 
  else if(strcmp(parameter,"grow")==0)
    {
      if(mutate_cnt > 0)
	mutation_selector[mutate_cnt][0] = atoi(value) + mutation_selector[mutate_cnt-1][0];   // probability of selecting shrink genome operator
      else
	mutation_selector[mutate_cnt][0] = atoi(value);
      mutation_selector[mutate_cnt++][1] = Grow;
      cout << " grow: " <<  mutation_selector[mutate_cnt-1][0]  << "% \n";
      match = true;
    }

  else if(strcmp(parameter,"multiple_mutate")==0)
    {
     if(mutate_cnt > 0)
       mutation_selector[mutate_cnt][0] = atoi(value) +  mutation_selector[mutate_cnt-1][0];   // probability of selecting multiple mutation  operator
     else
       mutation_selector[mutate_cnt][0] = atoi(value);
      mutation_selector[mutate_cnt++][1] = Multiple_mutate;
      cout << " multiple_mutate: " << mutation_selector[mutate_cnt-1][0]  << "% \n";
      match = true;
    }
  else if(strcmp(parameter,"mutate")==0)
    {
     if(mutate_cnt > 0)
       mutation_selector[mutate_cnt][0] = atoi(value) + mutation_selector[mutate_cnt-1][0];   // probability of selecting mutation  operator
     else
       mutation_selector[mutate_cnt][0] = atoi(value);
      mutation_selector[mutate_cnt++][1] = Mutate;
      cout << " mutate: " << mutation_selector[mutate_cnt-1][0]  << "% \n";
      match = true;
    }

  else if(strcmp(parameter,"ep_mutate_classic_adaptive")==0)
    {

      if(mutate_cnt > 0)
	mutation_selector[mutate_cnt][0] = atoi(value) + mutation_selector[mutate_cnt-1][0];   // probability of selecting mutation  operator 
      else
	mutation_selector[mutate_cnt][0] = atoi(value);
      mutation_selector[mutate_cnt++][1] = EP_Mutate_classic_adaptive;
      cout << " ep_mutate_classic_adaptive: " << mutation_selector[mutate_cnt-1][0]  << "% \n";
      match = true;
    }
  else if(strcmp(parameter,"ep_mutate")==0)
    {

      if(mutate_cnt > 0)
	mutation_selector[mutate_cnt][0] = atoi(value) + mutation_selector[mutate_cnt-1][0];   // probability of selecting mutation  operator 
      else
	mutation_selector[mutate_cnt][0] = atoi(value);
      mutation_selector[mutate_cnt++][1] = EP_Mutate;
      cout << " ep_mutate: " << mutation_selector[mutate_cnt-1][0]  << "% \n";
      match = true;
    }

  else if(strcmp(parameter,"ep_mutate_with_bias")==0)
    {

      if(mutate_cnt > 0)
	mutation_selector[mutate_cnt][0] = atoi(value) + mutation_selector[mutate_cnt-1][0];   // probability of selecting mutation  operator 
      else
	mutation_selector[mutate_cnt][0] = atoi(value);
      mutation_selector[mutate_cnt++][1] = EP_Mutate_with_bias;
      cout << " ep_mutate_with_bias: " << mutation_selector[mutate_cnt-1][0]  << "% \n";
      match = true;
    }


  else if(strcmp(parameter,"ep_mutate_non_random")==0)
    {

      if(mutate_cnt > 0)
	mutation_selector[mutate_cnt][0] = atoi(value) + mutation_selector[mutate_cnt-1][0];   // probability of selecting mutation  operator 
      else
	mutation_selector[mutate_cnt][0] = atoi(value);
      mutation_selector[mutate_cnt++][1] = EP_Mutate_non_random;
      cout << " ep_mutate_non_random: " << mutation_selector[mutate_cnt-1][0]  << "% \n";
      match = true;
    }
  if(match)
    status = OKAY;
  else 
    status = NOT_OKAY;
  

  return status;
  
}
int Configuration::set_specific_parameters(char parameter[], char value[])
{
  cout << "Error: Configuration Base class set_specific parameters : Should not be called \n";
  cout << "Parameters " << parameter << "  " << value << endl;
  return NOT_OKAY;
  
}



int Configuration::selftest(void)
{
  return 0;
}

















