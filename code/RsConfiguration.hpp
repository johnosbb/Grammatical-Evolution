#ifndef rsconfiguration_h
#define rsconfiguration_h 1

#include "Configuration.hpp"
#include <stdio.h>

//	the configuration class will hold settings applicable
//	to the random search configuration object.
//




class RsConfiguration : public Configuration
{

  public:
      RsConfiguration();
      RsConfiguration(const RsConfiguration &right);
      virtual ~RsConfiguration();
      int load_data(void);
      int set_specific_parameters(char parameter[], char value[]);
  int selftest(void);
  
  protected:


  private:

     
};

#endif
