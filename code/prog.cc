/********************************************************************
 *                                                                  *
 *                      Genetic Algorithm                           *  
 *          Coded in Object C++ by J.J. Collins (9035672)           *
 *             University of Limerick   1997                        *
 *                                                                  *
 *                 F I L E   :   P R O G . C P P                    *
 *          Testing population generation methodologies             *
 *                                                                  *
 ********************************************************************/     

#include <iostream.h>
#include "gstream.hpp"
#include "generate.hpp"
#include "params.h"
#include <time.h>
#include <fstream.h>
#include "../defines.h"
#include <new.h>

const int BEEP = '\a';
//#include "TOOLS/reporter.hpp"
static void memory_error_handler();

int save_profile_data(char filename[],int data);
int save_results_data(char filename[],int data);


int evaluations;


/*************************************************************************/
int main(int argc , char *argv[])
{
  int status = OKAY;
  int  gen_no = 0;
  set_new_handler(memory_error_handler);
#ifdef _PROFILE_
  cout << "P R O F I L I N G   T U R N E D   O N\n";
#endif 
#ifdef _DUMMY_
  cout << "S T U B B E D   O B J E C T I V E   F U N C T I O N\n";
#endif        
  if(argc < 2)
    {
      cout << "Error: Usage prog <profilename>" << endl;
      status = NOT_OKAY;
    }  
  if(status)
    {
      //gstream gout("set title 'best individual' ");
      time_t start_time;
      time(&start_time);
      evaluations = 0;
      generate p; 
      p.report();
      p.theMikeReport();


      while (p.generatefin()==0)
	{
	  fflush(stdout);
	  //gout << p.bestIndividual();
          cout << "Generation " << gen_no << " complete........\n";
	  gen_no ++;
	  p.resetGEreport();
	  p.generate_pop();
	  p.report();
	  p.theMikeReport();
	}   
 
      fflush(stdout);
      //if(full_report) cout << "\n Full report generated in 'full_report.rpt'.";
      //if(Mikes_Report) cout << "\n Full report generated in 'Mikes_report.rpt'.";
      //if(gnuplot) cout << "\n File for gnuplot generated 'plot.dat'.\n"; 
      time_t finish_time;
      time(&finish_time);
      int time_elapsed = (int)(finish_time - start_time);
      cout << "\n\nTime Elapsed : " << time_elapsed << endl;
      cout << "Total objective function evaluations : " << evaluations << endl;
      cout << "Successful Completion!\n";
      status = save_profile_data(argv[1],time_elapsed);
      status = save_results_data("testfile",evaluations);
    }
  
  return status;
}




int save_profile_data(char filename[],int data)
{
  ofstream save_profile_file;
  int status = OKAY;
  char profile_filename[50];
  strcpy(profile_filename,filename);
  strcat(profile_filename,".profile.txt");
  save_profile_file.open(profile_filename,ios::app);  
  if(!save_profile_file.is_open())
    {
      cout << "Error opening file " << profile_filename  << endl;
      status = NOT_OKAY;     
    }
  save_profile_file << data << endl;
  save_profile_file.close();
  return status;
} 



int save_results_data(char filename[],int data)
{
  ofstream save_results_file;
  int status = OKAY;
  char results_filename[50];
  strcpy(results_filename,filename);
  strcat(results_filename,".results.txt");
  save_results_file.open(results_filename,ios::app);  
  if(!save_results_file.is_open())
    {
      cout << "Error opening file " << results_filename  << endl;
      status = NOT_OKAY;     
    }
  save_results_file << "0  " << data << endl;
  save_results_file.close();
  return status;
} 




static void memory_error_handler()
{
  cerr << "Out of memory \n!!!!!!!!!!!!!!!" << BEEP << "\n";
  exit(1);
  
}




