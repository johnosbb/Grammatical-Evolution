

#ifndef hcconfig_h
#define hcconfig_h 1

#include "Configuration.hpp"
#include <stdio.h>

//	the configuration struct will hold settings applicable
//	to the random search configuration object.
//
//	Typical contents will be:



class HcConfiguration : public Configuration
{

  public:
      HcConfiguration();

      HcConfiguration(const HcConfiguration &right);

      virtual ~HcConfiguration();

      int set_specific_parameters(char parameter[], char value[]);
      int selftest();
      const int get_dwell_time() const;
      void set_dwell_time (int value);
  

    // Additional Public Declarations

  protected:
    // Additional Protected Declarations

  private:
     int dwell_time;
  


    // Additional Private Declarations

    // Data Members for Class Attributes

  

    // Additional Implementation Declarations

};






// Class configuration


inline const int HcConfiguration::get_dwell_time () const
{
  return dwell_time;
}

inline void HcConfiguration::set_dwell_time (int value)
{
  dwell_time = value;
}


#endif






