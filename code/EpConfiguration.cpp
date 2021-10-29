
// EpConfiguration
#include "EpConfiguration.hpp"


// Class EpConfiguration 


#include <string.h>
#include <iostream.h>
#include "defines.h"


EpConfiguration::EpConfiguration()
  : parent_population_size(100),
    offspring_population_size(100),
    xover_type(1),
    std_deviation(0)
 
{
   
}

EpConfiguration::EpConfiguration(const EpConfiguration &right)
  : parent_population_size(100),
    offspring_population_size(100),
    xover_type(1),
    std_deviation(0)
{
}


EpConfiguration::~EpConfiguration()
{
}




int EpConfiguration::selftest(void)
{
  return 1;
}




int EpConfiguration::set_specific_parameters(char parameter[], char value[])
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
  if(match)
    status = OKAY;
  else 
    status = NOT_OKAY;
  return status;
}
















