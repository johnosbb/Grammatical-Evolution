

#ifndef EpConfiguration_h
#define EpConfiguration_h 1

#include "Configuration.hpp"
#include <stdio.h>
#include <stdlib.h>

//	the configuration struct will hold settings applicable
//	to the random search configuration object.
//
//	Typical contents will be:



class EpConfiguration : public Configuration
{
  
public:
  EpConfiguration();
  
  EpConfiguration(const EpConfiguration &right);
  
  virtual ~EpConfiguration();
  
  int selftest(void);
  int set_specific_parameters(char parameter[], char value[]);
    // Additional Public Declarations
  int parent_population_size;
  int offspring_population_size;
  int xover_type; // 1 is discrete recombination
  double std_deviation;
  
protected:
    // Additional Protected Declarations

private:

  


    // Additional Private Declarations

    // Data Members for Class Attributes

  

    // Additional Implementation Declarations

};


// Class configuration 




#endif












