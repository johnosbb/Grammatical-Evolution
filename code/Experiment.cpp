// Experiment
#include "Experiment.hpp"
#include <stdlib.h>
#include "defines.h"
#include <iostream.h>
#include <string.h>
#include "Metaheuristic.hpp"
#include "TabuSearch.hpp"
#include "SimulatedAnnealing.hpp"
#include "EvolutionaryStrategy.hpp"
#include "EvolutionaryProgramming.hpp"
#include "RandomSearch.hpp"
#include "BiasedRandomSearch.hpp"
#include "RandomSearchFD.hpp"
#include "HillClimbing.hpp"
#include "Configuration.hpp"
#include "HcConfiguration.hpp"
#include "SaConfiguration.hpp"
#include "EpConfiguration.hpp"
#include "EsConfiguration.hpp"
#include "TabuConfiguration.hpp"
#include "RsConfiguration.hpp"
#include <fstream.h>
#include <time.h>

// Class Experiment 

Experiment::Experiment()
      : status(0),
	failures(0),
	successes(0),
        experiment_accumulated_genome_size(0),
        total_objective_function_evaluations(0)
{
}

Experiment::Experiment(const Experiment &right)
      : status(0),
	failures(0),
	successes(0),
        experiment_accumulated_genome_size(0),
        total_objective_function_evaluations(0)
{
}


Experiment::~Experiment()
{
}


int Experiment::select(char m_type[],char filename[],int num_of_trials)
{
  status = OKAY;
  if(strcmp(m_type,"tabu")==0)
    {
      cout << "Metaheuristic Selected : Tabu Search" << endl;
      TabuSearch ts;  // create a TabuSearch Object
      m_ptr = &ts; // set the Metaheuristic Base Class pointer to the TabuSearch Object
      TabuConfiguration tsc; //  create a TabuConfiguration Object
      m_ptr->set_the_configuration(&tsc); // set the TabuSearch Configuration to the TabuConfiguration Object
      status = run(filename,num_of_trials);
      
    }
  
    else if(strcmp(m_type,"sa")==0)
      {
	cout << "Metaheuristic Selected : Simulated Annealing" << endl;
	SimulatedAnnealing sa;
        m_ptr = &sa; // set the Metaheuristic Base Class pointer to the SimulatedAnnealing Object
        SaConfiguration sac; //  create a SaConfiguration Object
        m_ptr->set_the_configuration(&sac); // set the SimulatedAnnealing Configuration to the SaConfiguration Object
        status = run(filename,num_of_trials);
      }
  
  //else if(strcmp(m_type,"ga")==0)
      // cout << "Metaheuristic Selected : Genetic Algorithim" << endl;
  
  else if(strcmp(m_type,"rs")==0)
    {
	  cout << "Metaheuristic Selected : Random Serach" << endl;
	  RandomSearch rs;
	  m_ptr = &rs;  // set the Metaheuristic Base Class pointer to the RandomSearch Object
          RsConfiguration rsc; //  create a RsConfiguration Object
          m_ptr->set_the_configuration(&rsc); // set the RandomSearch  Configuration to the RsConfiguration Object
	  status = run(filename,num_of_trials);
	  
    }
  else if(strcmp(m_type,"brs")==0)
    {
	  cout << "Metaheuristic Selected :Biased Random Serach" << endl;
	  BiasedRandomSearch brs;
	  m_ptr = &brs;  // set the Metaheuristic Base Class pointer to the RandomSearch Object
          RsConfiguration rsc; //  create a RsConfiguration Object
          m_ptr->set_the_configuration(&rsc); // set the RandomSearch  Configuration to the RsConfiguration Object
	  status = run(filename,num_of_trials);

    }       
  else if(strcmp(m_type,"rsfd")==0)
    {
      cout << "Metaheuristic Selected :Biased Random Serach" << endl;
      RandomSearchFD brs;
      m_ptr = &brs;  // set the Metaheuristic Base Class pointer to the RandomSearch Object
      RsConfiguration rsc; //  create a RsConfiguration Object
      m_ptr->set_the_configuration(&rsc); // set the RandomSearch  Configuration to the RsConfiguration Object
      status = run(filename,num_of_trials);
      
    }       
  else if(strcmp(m_type,"hc")==0)
    {
      cout << "Metaheuristic Selected : Hill Climbing" << endl;
      HillClimbing  hc;
      m_ptr = &hc; // set the Metaheuristic Base Class pointer to the HilClimbing Object
      HcConfiguration Hcc; //  create a HcConfiguration Object
      m_ptr->set_the_configuration(&Hcc); // set the HillClimbing  Configuration to the HcConfiguration Object
      status = run(filename,num_of_trials);
    }
  else if(strcmp(m_type,"es")==0)
    {
      cout << "Metaheuristic Selected : Evolutionary Strategy" << endl;
      EvolutionaryStrategy  es;
      m_ptr = &es; // set the Metaheuristic Base Class pointer to the ES Object
      EsConfiguration Esc; //  create a EsConfiguration Object
      m_ptr->set_the_configuration(&Esc); // set the ES Configuration to the EsConfiguration Object
      status = run(filename,num_of_trials);
    }      
  else if(strcmp(m_type,"ep")==0)
    {
      cout << "Metaheuristic Selected : Evolutionary Programming" << endl;
      EvolutionaryProgramming  ep;
      m_ptr = &ep; // set the Metaheuristic Base Class pointer to the ES Object
      EpConfiguration Epc; //  create a EsConfiguration Object
      m_ptr->set_the_configuration(&Epc); // set the ES Configuration to the EsConfiguration Object
      status = run(filename,num_of_trials);
    }     
  else
    {
	  cout << "Error: Invalid Metaheuristic requested." << endl;
	  cout << "Options are ga,sa,tabu,brs,rsfd,rs,hc,es,ep" << endl;
	  status = NOT_OKAY;
    }
  
  return status;

}

int Experiment::selftest(void)
{
  RandomSearch rs;
  m_ptr = &rs;
  RsConfiguration rsc;
  m_ptr->set_the_configuration(&rsc);
  if( m_ptr->selftest())
    {
      cout << "RandomSearch with base pointer test passed \n";
    }
  
  else
    cout << "RandomSearch with base pointer test failed !\n "; 

 
  HillClimbing hc;
  
  m_ptr = &hc;
  if( m_ptr->selftest())
    cout << "HillClimbing with base pointer test passed \n";
  
  else
    cout << "HilClimbing with base pointer test failed !\n ";   
  TabuSearch tabu;
  m_ptr = &tabu;
  if( m_ptr->selftest())
    cout << "Tabu with base pointer test passed \n";
  
  else
    cout << "Tabu with base pointer test failed !\n ";    
  return OKAY;
  
}

// Additional Declarations



int Experiment::run(char filename[],int num_of_trials)
{

#ifdef _SANTAFE_
  cout << "Problem Selected: Santa Fe" << endl;
#endif

  status =  OKAY;
  if(m_ptr->configure(filename,&r))
    {
 
      
      if(open_data_files(filename))
	{
	  cout << "Total Number of Trials to run: " << num_of_trials << endl;
	  for(int i =0; i < num_of_trials; i++)
	    {
              cout << "DEBUG: Starting Trial " << i << "\n";
	      r.reset();   //reset the results;

	      m_ptr->setup_trial();
	
	      if( m_ptr->run_trial(i))
		{
		  incr_successes();

		}
	      
	      else
		incr_failures();
	      total_objective_function_evaluations+= r.get_objective_function_evaluations();
              experiment_accumulated_genome_size += r.get_average_genome_size();
	      report_trial_results(i);
	      save_trial_results(i);
              cout << "DEBUG: Trial " << i << " completed \n";
	      
	    } // for number of trials
	  save_results_file.close();
	  report_experiment_results(num_of_trials);
	  save_experiment_results(num_of_trials);
	  save_experiments_file.close();
	}
    }
  return status;
}


int Experiment::report_experiment_results(int num_of_trials)
{
  cout << "\nTotal Objective Function Evaluations : " << total_objective_function_evaluations << "\n";
  cout << "Successes : " << get_successes() << endl;
  cout << "Failures : " << get_failures() << endl;  
  cout << " Average Genome Size : " << (experiment_accumulated_genome_size/num_of_trials) << endl;
  return OKAY;
  
}

int Experiment::report_trial_results(int trial_num)
{

      cout << "\nTrial number " << trial_num << endl;
      cout << "-------------------------------- " << endl;
      cout << "Evaluations " << r.get_objective_function_evaluations() << endl;
      cout << "Final Value " << r.get_final_score() << endl;      
      cout << "Final Genome Value " << r.final_genome_value << endl;  
      cout << "Best Value " << r.get_best_score() << endl;   
      cout << "Best Genome Value " << r.best_genome_value << endl;  
      cout << "Average Genome Size " << r.get_average_genome_size() << endl;
      return OKAY;
      
}




int Experiment::save_trial_results(int trial_num)
{

      save_results_file <<  trial_num << "  ";
      save_results_file << r.final_genome_value << "  ";  
      save_results_file <<  r.get_final_score() << "  ";
      save_results_file << r.best_genome_value << "   ";
      save_results_file << r.get_best_score() << "   "; 
      save_results_file << r.get_objective_function_evaluations() << "  " ;
      save_results_file <<  r.get_average_genome_size() << endl;
      return OKAY;
      
}


int Experiment::save_experiment_results(int num_of_trials)
{
  save_experiments_file << "\nTotal Objective Function Evaluations : " << total_objective_function_evaluations << "\n";
  save_experiments_file << "Successes : " << get_successes() << endl;
  save_experiments_file << "Failures : " << get_failures() << endl;  
  save_experiments_file << "Average Genome Size : " << (experiment_accumulated_genome_size/num_of_trials) << endl;
  
  return OKAY;
  
}



int Experiment::open_data_files(char filename[])
{
  status = OKAY;
  char results_filename[50];
  strcpy(results_filename,filename);
  strcat(results_filename,".results.txt");
  save_results_file.open(results_filename);  
  if(!save_results_file.is_open())
    {
      cout << "Error opening file " << results_filename  << endl;
      status = NOT_OKAY;     
    }
  char experiment_filename[50];
  strcpy(experiment_filename,filename);
  strcat(experiment_filename,".experiment_results.txt");
  save_experiments_file.open(experiment_filename);  
  if(!save_experiments_file.is_open())
    {
      cout << "Error opening file " << experiment_filename  << endl;
      status = NOT_OKAY;     
    }  
  return status;
}
















