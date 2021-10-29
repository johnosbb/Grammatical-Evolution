

#ifndef saconfiguration_h
#define saconfiguration_h 1

#include "Configuration.hpp"
#include <stdio.h>
#include <stdlib.h>

//	the configuration struct will hold settings applicable
//	to the random search configuration object.
//
//	Typical contents will be:



class SaConfiguration : public Configuration
{

  public:
      SaConfiguration();

      SaConfiguration(const SaConfiguration &right);

      virtual ~SaConfiguration();
     
      int selftest(void);
      int set_specific_parameters(char parameter[], char value[]);
      const double  get_init_temperature (void);
      void set_init_temperature (double  value);  
      const double  get_temp_change_rate (void);
      void set_temp_change_rate (double  value);       
    // Additional Public Declarations

  protected:
    // Additional Protected Declarations

  private:
      double init_temperature;
      double temp_change_rate;
  


    // Additional Private Declarations

    // Data Members for Class Attributes

  

    // Additional Implementation Declarations

};


// Class configuration 



inline const double  SaConfiguration::get_init_temperature (void)
{
  return init_temperature;
}

inline void  SaConfiguration::set_init_temperature (double value) 
{
  init_temperature = value;
}

inline const double  SaConfiguration::get_temp_change_rate (void)
{
  return temp_change_rate;
}

inline void  SaConfiguration::set_temp_change_rate (double value) 
{
  temp_change_rate = value;
}

#endif












