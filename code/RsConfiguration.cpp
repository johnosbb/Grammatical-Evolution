// RsConfiguration
#include "RsConfiguration.hpp"


// Class RsConfiguration 


#include <string.h>
#include <iostream.h>
#include "defines.h"


RsConfiguration::RsConfiguration()


{
}

RsConfiguration::RsConfiguration(const RsConfiguration &right)

{
}


RsConfiguration::~RsConfiguration()
{
}





int RsConfiguration::set_specific_parameters(char parameter[], char value[])
{
  status = NOT_OKAY;  // there are no specific parameters for random search
  return status;
}



int RsConfiguration::selftest(void)
{
  return 1;
}


