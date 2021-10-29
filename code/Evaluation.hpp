//   Read the documentation to learn more about C++ code generator
//   versioning.

//	  %X% %Q% %Z% %W%



#ifndef Evaluation_h
#define Evaluation_h 1



// Metaheuristic
#include "Metaheuristic.hpp"
// GrammaticalEvolution
#include "GrammaticalEvolution.hpp"




class Evaluation 
{

  public:
      Evaluation();

      Evaluation(const Evaluation &right);

      ~Evaluation();

      Evaluation & operator=(const Evaluation &right);

      int operator==(const Evaluation &right) const;

      int operator!=(const Evaluation &right) const;

      friend ostream & operator<<(ostream &stream,const Evaluation &right);

      friend istream & operator>>(istream &stream,Evaluation &object);


      const GrammaticalEvolution get_the_GrammaticalEvolution () const;
      void set_the_GrammaticalEvolution (GrammaticalEvolution value);

      const Metaheuristic * get_the_Metaheuristic () const;
      void set_the_Metaheuristic (Metaheuristic * value);

    // Additional Public Declarations

  protected:
    // Additional Protected Declarations

  private:

      const Double get_score () const;
      void set_score (Double value);

    // Additional Private Declarations

    // Data Members for Class Attributes

      Double score;

    // Data Members for Associations

      GrammaticalEvolution the_GrammaticalEvolution;

      Metaheuristic *the_Metaheuristic;

    // Additional Implementation Declarations

};


// Class Evaluation 


inline const Double Evaluation::get_score () const
{
  return score;
}

inline void Evaluation::set_score (Double value)
{
  score = value;
}


inline const GrammaticalEvolution Evaluation::get_the_GrammaticalEvolution () const
{
  return the_GrammaticalEvolution;
}

inline void Evaluation::set_the_GrammaticalEvolution (GrammaticalEvolution value)
{
  the_GrammaticalEvolution = value;
}

inline const Metaheuristic * Evaluation::get_the_Metaheuristic () const
{
  return the_Metaheuristic;
}

inline void Evaluation::set_the_Metaheuristic (Metaheuristic * value)
{
  the_Metaheuristic = value;
}



#endif
