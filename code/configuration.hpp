//   Read the documentation to learn more about C++ code generator
//   versioning.

//	  %X% %Q% %Z% %W%



#ifndef configuration_h
#define configuration_h 1



// Experiment
#include "Experiment.hpp"
// Metaheuristic
#include "Metaheuristic.hpp"



//	the configuration struct will hold settings applicable
//	to all sub classes of metaheuristic.
//
//	Typical contents will be:
//	initial length of genome.
//	initial length variation range.
//	metaheuristic type.
//	zero improvement accept flag setting.
//	wrap on off flag
//	configuration for a starting genome.
//	flag to set biased annealing on or off.
//	The configuration file will also contain a list of
//	trials for which the search trajectory will be captured.


class configuration 
{

  public:
      configuration();

      configuration(const configuration &right);

      ~configuration();

      configuration & operator=(const configuration &right);

      int operator==(const configuration &right) const;

      int operator!=(const configuration &right) const;

      friend ostream & operator<<(ostream &stream,const configuration &right);

      friend istream & operator>>(istream &stream,configuration &object);


      const Experiment * get_the_Experiment () const;
      void set_the_Experiment (Experiment * value);

    // Additional Public Declarations

  protected:
    // Additional Protected Declarations

  private:

      const Integer get_metaheuristics () const;
      void set_metaheuristics (Integer value);

      const String get_configuration_filename () const;
      void set_configuration_filename (String value);

      const struct get_configuration_settings () const;
      void set_configuration_settings (struct value);

    // Additional Private Declarations

    // Data Members for Class Attributes

      Integer metaheuristics;

      String configuration_filename;

      struct configuration_settings;

    // Data Members for Associations

      Experiment *the_Experiment;

    // Additional Implementation Declarations

};


// Class configuration 


inline const Integer configuration::get_metaheuristics () const
{
  return metaheuristics;
}

inline void configuration::set_metaheuristics (Integer value)
{
  metaheuristics = value;
}

inline const String configuration::get_configuration_filename () const
{
  return configuration_filename;
}

inline void configuration::set_configuration_filename (String value)
{
  configuration_filename = value;
}

inline const struct configuration::get_configuration_settings () const
{
  return configuration_settings;
}

inline void configuration::set_configuration_settings (struct value)
{
  configuration_settings = value;
}


inline const Experiment * configuration::get_the_Experiment () const
{
  return the_Experiment;
}

inline void configuration::set_the_Experiment (Experiment * value)
{
  the_Experiment = value;
}



#endif
