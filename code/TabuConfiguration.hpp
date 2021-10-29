#ifndef tabuconfiguration_h
#define tabuconfiguration_h 

#include "Configuration.hpp"
#include <stdio.h>

//	the configuration struct will hold settings applicable
//	to the random search configuration object.
//
//	Typical contents will be:



class TabuConfiguration : public Configuration
{

  public:
      TabuConfiguration();

      TabuConfiguration(const TabuConfiguration &right);

       ~TabuConfiguration();

       int selftest(void);
       int set_specific_parameters(char parameter[], char value[]);
  
      const int  get_tabu_tenure (void);
      void set_tabu_tenure (int  value);    
    // Additional Public Declarations

  protected:
    // Additional Protected Declarations

  private:
    int tabu_tenure;
  


    // Additional Private Declarations

    // Data Members for Class Attributes

  

    // Additional Implementation Declarations

};


inline const int  TabuConfiguration::get_tabu_tenure (void)
{
  return tabu_tenure;
}

inline void  TabuConfiguration::set_tabu_tenure (int value) 
{
  tabu_tenure = value;
}



// Class configuration
#endif








