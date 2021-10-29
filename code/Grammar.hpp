//   Read the documentation to learn more about C++ code generator
//   versioning.

//	  %X% %Q% %Z% %W%



#ifndef Grammar_h
#define Grammar_h 1



// Interpreter
#include "Interpreter.hpp"
// GrammaticalEvolution
#include "GrammaticalEvolution.hpp"




class Grammar 
{

  public:
      Grammar();

      Grammar(const Grammar &right);

      ~Grammar();

      Grammar & operator=(const Grammar &right);

      int operator==(const Grammar &right) const;

      int operator!=(const Grammar &right) const;

      friend ostream & operator<<(ostream &stream,const Grammar &right);

      friend istream & operator>>(istream &stream,Grammar &object);


      const GrammaticalEvolution * get_the_GrammaticalEvolution () const;
      void set_the_GrammaticalEvolution (GrammaticalEvolution * value);

      const Interpreter get_the_Interpreter () const;
      void set_the_Interpreter (Interpreter value);

    // Additional Public Declarations

  protected:
    // Additional Protected Declarations

  private:
    // Additional Private Declarations

    // Data Members for Associations

      GrammaticalEvolution *the_GrammaticalEvolution;

      Interpreter the_Interpreter;

    // Additional Implementation Declarations

};


// Class Grammar 


inline const GrammaticalEvolution * Grammar::get_the_GrammaticalEvolution () const
{
  return the_GrammaticalEvolution;
}

inline void Grammar::set_the_GrammaticalEvolution (GrammaticalEvolution * value)
{
  the_GrammaticalEvolution = value;
}

inline const Interpreter Grammar::get_the_Interpreter () const
{
  return the_Interpreter;
}

inline void Grammar::set_the_Interpreter (Interpreter value)
{
  the_Interpreter = value;
}



#endif
