#include <stdlib.h>
#include <iostream.h>
#include "defines.h"
#include "Random.hpp"
#include <stdio.h>
#include <time.h>
#include <fstream.h>
#include <new.h>
#include <list>
#include "Analyser.hpp"
#include "AnalyserConfig.hpp"
#include "Genome.hpp"

//function prototypes


typedef vector<Genome> genomelist;

Analyser::Analyser()
{
}

Analyser::Analyser(const Analyser &right)
{
}

Analyser::~Analyser()
{
}

//main
int Analyser::run(char filename[],int wrap_flag)
{

  int status = OKAY;
  cout << "--------------- Analyser ------------------\n\n";
  AnalyserConfig ac;
  ac.load_file(filename);
  ac.load_data(this->glist,wrap_flag);
  process();
  //status = save_analyser_data(filename);
  return status;
}



int Analyser::save_analyser_data(char filename[])
{
  ofstream save_analyser_file;
  int status = OKAY;
  char analyser_filename[50];
  strcpy(analyser_filename,filename);
  strcat(analyser_filename,".analyser.txt");
  save_analyser_file.open(analyser_filename,ios::app);  
  cout << "Creating output file : " << analyser_filename << endl;
  
  if(!save_analyser_file.is_open())
    {
      cout << "Error opening file " << analyser_filename  << endl;
      status = NOT_OKAY;     
    }
  save_analyser_file << "test" << endl;
  save_analyser_file.close();
  return status;
} 




int Analyser::show_list(void)
{
  genomelist::iterator iter;
  iter = glist.begin();
  while(iter!= glist.end())
    {  
      cout << *(iter) << "  "  << (*iter).get_score() << endl;
      iter++;
      
    }
  return OKAY;
  
}


int Analyser::process(void)
{
  genomelist::iterator iter;
  iter = glist.begin();
  while(iter!= glist.end())
    {  
      cout << "Evaluating Genome: " << (*iter) << endl;
      (*iter).evaluate();
      iter++;
      
    }
  return OKAY;
  
}















