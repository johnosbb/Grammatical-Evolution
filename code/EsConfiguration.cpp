
// EsConfiguration
#include "EsConfiguration.hpp"


// Class EsConfiguration 


#include <string.h>
#include <iostream.h>
#include "defines.h"


EsConfiguration::EsConfiguration()
  : parent_population_size(100),
    offspring_population_size(100),
    xover_type(1),
    std_deviation(0),
    selection_strategy(2)
 
{
   
}

EsConfiguration::EsConfiguration(const EsConfiguration &right)
  : parent_population_size(100),
    offspring_population_size(100),
    xover_type(1),
    std_deviation(0)
{
}


EsConfiguration::~EsConfiguration()
{
}




int EsConfiguration::selftest(void)
{
  return 1;
}




int EsConfiguration::set_specific_parameters(char parameter[], char value[])
{

  bool match = false;
  if(strcmp(parameter,"parent_population_size")==0)
    {
      parent_population_size = atoi(value);
      cout << " parent_population_size: " << parent_population_size << "\n";
      match = true;
    }
  else if(strcmp(parameter,"offspring_population_size")==0)
    {
      offspring_population_size = atoi(value);
      cout << " offspring_population_size: " <<  offspring_population_size << "\n";
      match = true;
    }
  else if(strcmp(parameter,"xover_type")==0)
    {
      xover_type = atoi(value);
      cout << " xover_type: " <<  xover_type << "\n";
      match = true;
    }
  else if(strcmp(parameter,"std_deviation")==0)
    {
      std_deviation = atof(value);
      cout << " std_deviation: " <<  std_deviation << "\n";
      match = true;
    }
  else if(strcmp(parameter,"selection_strategy")==0)
    {
      if(strcmp(value,"comma")==0) 
	{
	  selection_strategy = 1;
	  match = true;
	}
      else if(strcmp(value,"plus")==0) 
	{
	  selection_strategy = 2;
	  match = true;
	}
      else
	match = false;
     cout << " selection_strategy: " <<  selection_strategy << "\n";
    }

  if(match)
    status = OKAY;
  else 
    status = NOT_OKAY;
  return status;
}
















