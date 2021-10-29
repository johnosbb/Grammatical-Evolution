// FrequencyDistribution
#include "FrequencyDistribution.hpp"
#include "FrequencyDistributionElement.hpp"
#include "defines.h"
#include <fstream.h>



// Class FrequencyDistribution 

FrequencyDistribution::FrequencyDistribution()
{
}

FrequencyDistribution::FrequencyDistribution(const FrequencyDistribution &right)
{
}


FrequencyDistribution::~FrequencyDistribution()
{
}


// this contains the main algorithm for random search
void FrequencyDistribution::evaluate(double f)
{
  frequency_distribution::iterator iter;
  bool matched = false;
  iter = fd.begin();
  while(iter!=fd.end())
    {
      if((*iter).check_value(f))
	{
	  (*iter).increment_frequency();
          matched = true;
	}
      
      iter++;

    }
  if (!matched)
    {
      
      fde.set(f,1);
      fd.push_back(fde);
    }
  
      
}





void FrequencyDistribution::show(void)
{
  frequency_distribution::iterator iter;
  iter = fd.begin();
  while(iter!=fd.end())
    {
      cout << (*iter).get_value() << "  " << (*iter).get_frequency() << endl;
      iter++;
    }
}





int FrequencyDistribution::save(void)
{
  int status = OKAY;
  ofstream fd_results_file;
  fd_results_file.open("frequency_distribution.txt");
  if(!fd_results_file.is_open())
    {
      cout << "Error opening file " << "frequency_distribution.txt"  << endl;
      status = NOT_OKAY;     
    } 
  frequency_distribution::iterator iter;
  iter = fd.begin();
  while(iter!=fd.end())
    {
      fd_results_file << (*iter).get_value() << "  " << (*iter).get_frequency() << endl;
      iter++;
    }
  fd_results_file.close();
  return status;

}



