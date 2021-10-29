#include <stdlib.h>
#include <iostream.h>
#include "defines.h"
#include "Random.hpp"
#include <stdio.h>
#include <time.h>
#include <fstream.h>
#include <new.h>
#include "Analyser.hpp"
//function prototypes


const int BEEP = '\a';

static void memory_error_handler(void); 




//main
int main(int argc , char *argv[])
{

  set_new_handler(memory_error_handler);
  int status = OKAY;
  int time_elapsed;
  

  if(argc < 2)
    {
      cout << "Error: Usage analyser <solution file> " << endl;
      status = NOT_OKAY;
    }

  else 
    {
      
      cout << "--------------- Analyser ------------------\n\n";
      time_t start_time;
      time(&start_time);
      Analyser a;
      a.run(argv[1]);
      // stuff in here.
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


















