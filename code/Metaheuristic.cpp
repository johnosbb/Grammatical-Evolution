// Metaheuristic
#include "Metaheuristic.hpp"
#include "Configuration.hpp"
#include "TabuConfiguration.hpp"
#include <iostream.h>
#include "defines.h"
#include "Results.hpp"
#include <stdlib.h>
#include <stdio.h>

// Class Metaheuristic 


Metaheuristic::Metaheuristic()
{
}

Metaheuristic::Metaheuristic(const Metaheuristic &right)
      

{
}


Metaheuristic::~Metaheuristic()
{
}



int Metaheuristic::run_trial (int trial_num)
{
  cout << "run_trial: " << trial_num << " Base Class\n";
  return OKAY;
  
}


int Metaheuristic::setup_trial (void)
{
  set_iterations(c_ptr->iterations);
  search_progress_indicator = 0;
  if(!c_ptr->initial_length == 0) // if an initial length is supplied
    {
      current_genome.set_max_length(c_ptr->maximum_genome_length);
      current_genome.set_max_gene_value(c_ptr->max_gene_value);
      current_genome.create(c_ptr->initial_length,c_ptr->initial_length_variation_range);
    }
  
  else if(!strcmp(c_ptr->initial_genome_value,"empty")==0) // if an initial genome value is supplied
    {
      current_genome.set_max_length(c_ptr->maximum_genome_length);
      current_genome.set_max_gene_value(c_ptr->max_gene_value);
      current_genome.create(c_ptr->initial_genome_value);  // note this over-rides a genome based on 
    }                                     //an initial length if both parameters are suppliedt
  else                              // no explicit configuration given , generating
    {
      current_genome.set_max_length(c_ptr->maximum_genome_length);
      current_genome.set_max_gene_value(c_ptr->max_gene_value);
      current_genome.create();     // a random genome
    }
  
  current_genome.configure(c_ptr->wrap,c_ptr->ge_report,c_ptr->mutation_selector,c_ptr->mutation_rate,c_ptr->style,c_ptr->mutation_rate_range);  
  new_genome.set_max_length(c_ptr->maximum_genome_length);
  new_genome.set_max_gene_value(c_ptr->max_gene_value);
  new_genome.configure(c_ptr->wrap,c_ptr->ge_report,c_ptr->mutation_selector,c_ptr->mutation_rate,c_ptr->style,c_ptr->mutation_rate_range);
  best_genome.set_max_length(c_ptr->maximum_genome_length);
  best_genome.set_max_gene_value(c_ptr->max_gene_value);
  best_genome.configure(c_ptr->wrap,c_ptr->ge_report,c_ptr->mutation_selector,c_ptr->mutation_rate,c_ptr->style,c_ptr->mutation_rate_range);
  accumulated_genome_size = 0;
  
  return OKAY;
  
}

int Metaheuristic::configure (char filename[], Results * results)
{
  status = c_ptr->load_file(filename);
  set_cfg_filename(filename);
  if(status)
    status  = c_ptr->load_data(); 
  if(status)
    r_ptr = results;
  
  return status;  
}



void Metaheuristic::set_cfg_filename(char * filename)
{
  strcpy(cfg_filename,filename);
}

char * Metaheuristic::get_cfg_filename(void)
{
  return cfg_filename;
}

void Metaheuristic::set_the_configuration ( Configuration * ptr)
{
  c_ptr = ptr;
}

void Metaheuristic::reset_results(void)
{
  r_ptr->set_best_score (0.00);
  r_ptr->set_objective_function_evaluations(0);
  r_ptr->set_final_score(0.0);
  
}


void Metaheuristic::set_iterations (int value)
{
  iterations = value;
  
}

// Additional Declarations


int Metaheuristic::selftest()
{
  cout << "Base Class for Metaheuristics:: ";
  return 0;
}

int Metaheuristic::check_capture(int trial_num)
{
  int flag = 0; 
  int cnt = 0;
  char filename[40];
  sprintf(filename,"%s.capture.%d.txt",cfg_filename,trial_num);
  if(capture_data_file.is_open())  // close any previously open capture files
    capture_data_file.close();
  while(c_ptr->capture_data_list[cnt]!= -1)
      {
	  if(trial_num == c_ptr->capture_data_list[cnt++])
	      {
		  flag = 1;	 
		  capture_data_file.open(filename);  
		  if(!capture_data_file.is_open())
		    {
		      cout << "Error opening file " << filename  << endl;
		      status = NOT_OKAY;     // nothing is done with this value yet
		    }  
		  break;
	      }
      }
  return flag;
  
}

void Metaheuristic::report_search_data(int iteration_num)
{
  capture_data_file << iteration_num << "   " << current_genome <<  "   " << current_genome.get_score() << "  " << new_genome << "  " << new_genome.get_score()<< "  " <<  current_genome.get_current_length() << "  " <<  new_genome.get_current_length() << endl;
}



void Metaheuristic::report_search_data(int iteration_num,double current_temperature,double probability,double random_threshold)
{
  capture_data_file << iteration_num << "   " << current_genome <<  "   " << current_genome.get_score() << "  " << new_genome << "  " << new_genome.get_score()<< "  " <<  current_genome.get_current_length() << "  " <<  new_genome.get_current_length() << "  " << current_temperature << "  " << probability << "  " << random_threshold << endl;
}




















