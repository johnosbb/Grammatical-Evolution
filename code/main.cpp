#include <stdlib.h>
#include <iostream.h>
#include "defines.h"
#include "Experiment.hpp"
#include "Random.hpp"
#include <stdio.h>
#include <time.h>
#include <fstream.h>
#include <new.h>

//function prototypes

const int BEEP = '\a';


int reset_seed(void);
int save_seed(char filename[]);
int save_profile_data(char filename[],int data);
static void memory_error_handler(void);



//main
int main(int argc , char *argv[])
{

#ifdef _PROFILE_
  cout << "P R O F I L I N G   T U R N E D   O N\n";
#endif 
#ifdef _DUMMY_
  cout << "S T U B B E D   O B J E C T I V E   F U N C T I O N\n";
#endif
  set_new_handler(memory_error_handler);
  Experiment the_experiment;
  int status = OKAY;
  int time_elapsed;
  
  if( argc == 1)
    {
       cout << "--------------- Experiment Test Mode ----------------\n\n";
       status = the_experiment.select("brs","testfile1.cfg",3);
    }
  

  else if(argc < 4)
    {
      cout << "Error: Usage GrammaSolve <metaheuristic>  <configuration file> <number of trials> <randomize flag - optional>" << endl;
      status = NOT_OKAY;
    }

  else 
    {
      
      cout << "--------------- Experiment ------------------\n\n";

      if(argc == 5)
	{
	  if(!strcmp(argv[4],"rerun"))
	     status = reset_seed();
	  Random r;
	  r.randomize();
	  cout << "Randomizing random number generator\n";
	  status = save_seed(argv[2]);
	}
      time_t start_time;
      time(&start_time);
      status = the_experiment.select(argv[1],argv[2],atoi(argv[3]));
      time_t finish_time;
      time(&finish_time);
      time_elapsed = (int)(finish_time - start_time);
      cout << "Time Elapsed : " << time_elapsed << endl;
      cout << "Successful Completion!\n";
      status = save_profile_data(argv[2],time_elapsed);
    }
      return status;
}


int reset_seed()
{
  FILE *fp;
  int seed;
  if ((fp=fopen("state.dat","r"))==NULL) {
    fprintf(stderr,"Linear Congruential Method:");
    fprintf(stderr,"\n  Error: could not open file state.dat");
    fprintf(stderr,"\n  Setting seed = 1 and creating file 'state.dat'\n");
    seed = 1;
  }
  else {
     fscanf(fp,"%d",&seed);
     fclose(fp);
     seed--;
     if(seed < 1) seed = 1;
  }
  printf("\n seed = %d \n",seed);
  fp=fopen("state.dat","w");
  fprintf(fp,"%d",seed);
  fclose(fp);
  return OKAY;
  
}  


int save_seed(char filename[])
{
  FILE *fp;
  int seed;
  int status = OKAY;
  char cfg_seed_file[30];
  if ((fp=fopen("state.dat","r"))==NULL)
    {
      fprintf(stderr,"Linear Congruential Method:");
      fprintf(stderr,"\n  Error: could not open file state.dat");
      status= NOT_OKAY;
    }
  else
    {
     fscanf(fp,"%d",&seed);
     fclose(fp);
    }
  if(status)
    {
      sprintf(cfg_seed_file,"%s.seed.dat",filename);
      printf("\n seed = %d \n",seed);
      fp=fopen(cfg_seed_file,"w");
      fprintf(fp,"%d",seed);
      fclose(fp);
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


static void memory_error_handler()
{
  cerr << "Out of memory \n!!!!!!!!!!!!!!!" << BEEP << "\n";
  exit(1);
  
}











