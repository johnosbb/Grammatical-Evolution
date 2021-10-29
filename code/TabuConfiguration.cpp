
// TabuConfiguration
#include "TabuConfiguration.hpp"


// Class TabuConfiguration 


#include <string.h>
#include <iostream.h>
#include "defines.h"
#include <stdlib.h>  // for atoi

TabuConfiguration::TabuConfiguration()
  :tabu_tenure(0)
{
}

TabuConfiguration::TabuConfiguration(const TabuConfiguration &right)
{
}


TabuConfiguration::~TabuConfiguration()
{
}

int TabuConfiguration::set_specific_parameters(char parameter[], char value[])
{

  bool match = false;
  if(strcmp(parameter,"tabu_tenure")==0)
    {
      tabu_tenure = atoi(value);
      cout << " tabu_tenure: " << tabu_tenure << "\n";
      match = true;
    }

  if(match)
    status = OKAY;
  else 
    status = NOT_OKAY;
  return status;
}




int TabuConfiguration::selftest(void)
{
  return 1;
}




























