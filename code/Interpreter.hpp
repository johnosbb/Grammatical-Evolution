//   Read the documentation to learn more about C++ code generator
//   versioning.

//	  %X% %Q% %Z% %W%



#ifndef Interpreter_h
#define Interpreter_h 1



// Grammar
#include "Grammar.hpp"




class Interpreter 
{

  public:
      Interpreter();

      Interpreter(const Interpreter &right);

      ~Interpreter();

      Interpreter & operator=(const Interpreter &right);

      int operator==(const Interpreter &right) const;

      int operator!=(const Interpreter &right) const;

      friend ostream & operator<<(ostream &stream,const Interpreter &right);

      friend istream & operator>>(istream &stream,Interpreter &object);


      const Grammar * get_the_Grammar () const;
      void set_the_Grammar (Grammar * value);

    // Additional Public Declarations

  protected:
    // Additional Protected Declarations

  private:
    // Additional Private Declarations

    // Data Members for Associations

      Grammar *the_Grammar;

    // Additional Implementation Declarations

};


// Class Interpreter 


inline const Grammar * Interpreter::get_the_Grammar () const
{
  return the_Grammar;
}

inline void Interpreter::set_the_Grammar (Grammar * value)
{
  the_Grammar = value;
}



#endif
