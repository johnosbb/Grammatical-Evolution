//   Read the documentation to learn more about C++ code generator
//   versioning.

//	  %X% %Q% %Z% %W%



#ifndef GrammaticalEvolution_h
#define GrammaticalEvolution_h 1



// Evaluation
#include "Evaluation.hpp"
// Grammar
#include "Grammar.hpp"




class GrammaticalEvolution 
{

  public:
      GrammaticalEvolution();

      GrammaticalEvolution(const GrammaticalEvolution &right);

      ~GrammaticalEvolution();

      GrammaticalEvolution & operator=(const GrammaticalEvolution &right);

      int operator==(const GrammaticalEvolution &right) const;

      int operator!=(const GrammaticalEvolution &right) const;

      friend ostream & operator<<(ostream &stream,const GrammaticalEvolution &right);

      friend istream & operator>>(istream &stream,GrammaticalEvolution &object);


      const Evaluation * get_the_Evaluation () const;
      void set_the_Evaluation (Evaluation * value);

      const Grammar get_the_Grammar () const;
      void set_the_Grammar (Grammar value);

    // Additional Public Declarations

  protected:
    // Additional Protected Declarations

  private:
    // Additional Private Declarations

    // Data Members for Associations

      Evaluation *the_Evaluation;

      Grammar the_Grammar;

    // Additional Implementation Declarations

};


// Class GrammaticalEvolution 


inline const Evaluation * GrammaticalEvolution::get_the_Evaluation () const
{
  return the_Evaluation;
}

inline void GrammaticalEvolution::set_the_Evaluation (Evaluation * value)
{
  the_Evaluation = value;
}

inline const Grammar GrammaticalEvolution::get_the_Grammar () const
{
  return the_Grammar;
}

inline void GrammaticalEvolution::set_the_Grammar (Grammar value)
{
  the_Grammar = value;
}



#endif
