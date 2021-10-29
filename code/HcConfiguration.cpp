
// HcConfiguration
#include "HcConfiguration.hpp"


// Class HcConfiguration 


#include <string.h>
#include <iostream.h>
#include "defines.h"
#include <stdlib.h> // for atoi

HcConfiguration::HcConfiguration()
  :dwell_time(0)
{
}

HcConfiguration::HcConfiguration(const HcConfiguration &right)
{
}


HcConfiguration::~HcConfiguration()
{
}




int HcConfiguration::set_specific_parameters(char parameter[], char value[])
{

  bool match = false;
  if(strcmp(parameter,"dwell_time")==0)
    {
      dwell_time = atoi(value);
      cout << " dwell_time: " <<  dwell_time << "\n";
      match = true;
    }

  if(match)
    status = OKAY;
  else 
    status = NOT_OKAY;
  

  return status;
  
}

int HcConfiguration::selftest(void)
{
  return 1;
}


// Additional Declarations










