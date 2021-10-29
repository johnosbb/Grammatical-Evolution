
// SaConfiguration
#include "SaConfiguration.hpp"


// Class SaConfiguration 


#include <string.h>
#include <iostream.h>
#include "defines.h"


SaConfiguration::SaConfiguration()
  :init_temperature(0),
   temp_change_rate(0)
 
{
   
}

SaConfiguration::SaConfiguration(const SaConfiguration &right)
{
}


SaConfiguration::~SaConfiguration()
{
}




int SaConfiguration::selftest(void)
{
  return 1;
}




int SaConfiguration::set_specific_parameters(char parameter[], char value[])
{

  bool match = false;

  if(strcmp(parameter,"init_temperature")==0)
    {
      init_temperature = atof(value);
      cout << " init_temperature: " << init_temperature << "\n";
      match = true;
    }
  else if(strcmp(parameter,"temp_change_rate")==0)
    {
      temp_change_rate = atof(value);
      cout << " temp_change_rate: " <<  temp_change_rate << "\n";
      match = true;
    }

  if(match)
    status = OKAY;
  else 
    status = NOT_OKAY;
  return status;
}
















