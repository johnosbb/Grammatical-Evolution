#include <stdlib.h>
#include <iostream.h>
#include "defines.h"
#include "Random.hpp"
#include <stdio.h>
#include <time.h>
#include <fstream.h>
#include <new.h>
#include "Generator.hpp"
//function prototypes


const int BEEP = '\a';

static void memory_error_handler(void); 

// The Generator is used to generate all neighbours of a genome
// It takes as input a file on genomes in comma delimited codon format
// this file is loaded a s a configuration file by the AlanyzeConfigurator
// The output from the program is to stdout
// the output consists of a genome and each of its immediate neighbours


//main
int main(int argc , char *argv[])
{

  set_new_handler(memory_error_handler);
  int status = OKAY;
  int time_elapsed;
  

  if(argc < 2)
    {
      cout << "Error: Usage Generator <solution file> " << endl;
      status = NOT_OKAY;
    }

  else 
    {
      
      cout << "--------------- neighbourhood generator ------------------\n\n";
      time_t start_time;
      time(&start_time);
      Generator g;
      g.run(argv[1]);
      time_t finish_time;
      time(&finish_time);
      time_elapsed = (int)(finish_time - start_time);
      cout << "Time Elapsed : " << time_elapsed << endl;
      cout << "Successful Completion!\n";
    }
      return status;
}




static void memory_error_handler()
{
  cerr << "Out of memory \n!!!!!!!!!!!!!!!" << BEEP << "\n";
  exit(1);
  
}

























