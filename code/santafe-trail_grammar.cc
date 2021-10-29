/*************************************************************************/
/*                                                                       */
/*              FILE   :  GRAMMAR.CC                                     */
/*              AUTHOR :  Michael O'Neill                                */
/*              DATE   :  MAY 98                                         */
/*              SCHOOL :  Dept. Computer Science                         */
/*                        University of Limerick                         */
/*                                                                       */
/*  -------------------------------------------------------------------  */
/*    FUNCTIONALITY :  Implements a BNF Grammar for Grammatical Evolution*/
/*  -------------------------------------------------------------------- */
/*     BUGS : todate, none to report.                                    */
/*                                                                       */
/*************************************************************************/
#include <iostream.h>
#include "grammar.hpp"
#include "../params.h"
/*************************************************************************/
grammar::grammar()
{}
/*************************************************************************/

/*************************************************************************/
void grammar::apply_grammar(int old_expr[], int *curr, int *length, int *gpos, const int rnd_num)
{ 
  /*************************************************************************************/
  /* Purpose: Used for solving Santa Fe Trail      (version 2)                         */
  /*************************************************************************************/
  /*              (1001)<code> :: = <line>|<code><line>                                */
  /*              (1002)<line> :: = <expr>                                             */
  /*              (1003)<expr> :: = <condition>|<op>|<progn>                           */
  /*              (1004)<condition> :: = if(food_ahead()==TRUE)<c-statement>           */
  /*              (1005)<op> :: = LEFT() | RIGHT() | MOVE()                            */
  /*              (1006)<c-statement>::=<if-true><else-false>                          */
  /*              (1007)<if-true>:={<expr>}                                            */
  /*              (1008)<else-false>:=else{<expr>}                                     */
  /*              (1009)<progn>:= <op><op>|<op><op><op>                                */
  /*                                                                                   */
  /*************************************************************************************/

  switch(old_expr[*curr])
  {
  case(1001) : {   /******************************************/
                   /*(1)  <code> :: = <line>|<code><line>   */
                   /******************************************/
                   switch(rnd_num%2)
		     {
		     case(0) :
		       {
			 //<line>
			 old_expr[*curr]=1002;
			 break;
		       }
		     case(1) :
		       {
			 //<code><line>
			 for (int i=*length-1;i>*curr;i--) old_expr[i+1]=old_expr[i];
			 *length=*length+1;
			 old_expr[*curr]=1001;
			 old_expr[*curr+1]=1002;
			 break;
		       }
		     }// of switch
		   *gpos=*gpos+1;
                   break;
               }
  case(1002) : {   /************************************/
                   /*(2)<line> :: = <expr>             */
                   /************************************/
                   //<line>
                   old_expr[*curr]=1003;                 
		   //*gpos=*gpos+1; 
		   break;
                 } // Of case 1002

  case(1003) : {  
                  /*************************************************/
                  /*(1003)  <expr> :: = <condition>|<op>|<progn>   */
                  /*************************************************/
                   switch(rnd_num%2)
		     {
		     case 0 :
		       {
			 //<condition>
			 old_expr[*curr]=1004;
			 break;
		       }
		     case 1 :
		       {
			 //<op>
			 old_expr[*curr]=1005;
			 break;
		       }
		     case 2 :
		       {
			 //<progn>
			 old_expr[*curr]=1009;
			 break;
		       }
		     }
		   *gpos=*gpos+1;
		   break;
               } // of case 1003

  case(1004) : {  /*****************************************************************/
                  /*(4)<condition> :: = if(food_ahead()==TRUE)<c-statement>        */
                  /*****************************************************************/
		   for (int i=*length-1;i>*curr;i--) old_expr[i+1]=old_expr[i];
		   *length=*length+1;
		   old_expr[*curr]=5; //if(food_ahead()==TRUE)
		   old_expr[*curr+1]=1006; //<c-statement>
		   //*curr=*curr+1;
		   //*gpos=*gpos+1;
		   break;
               } // of case 1004

  case(1005) : {  /**************************************************************************/
                  /*(5) <op> :: =    LEFT(); | RIGHT(); | MOVE();                           */
                  /**************************************************************************/
                  int r=rnd_num%3;
		  switch(r)
		    {
		    case 0:
		      {
			for (int i=*length-1;i>*curr;i--) old_expr[i+1]=old_expr[i];
			*length=*length+1;
			old_expr[*curr]=2; //left
			old_expr[*curr+1]=101; //;
			//*curr=*curr+3;
			break;
		      }
		    case 1:
		      {
			for (int i=*length-1;i>*curr;i--) old_expr[i+1]=old_expr[i];
			*length=*length+1;
			old_expr[*curr]=3; //right
			old_expr[*curr+1]=101; //;
			//*curr=*curr+3;
			break;
		      }
		    case 2:
		      {
			for (int i=*length-1;i>*curr;i--) old_expr[i+1]=old_expr[i];
			*length=*length+1;
			old_expr[*curr]=4; //move
			old_expr[*curr+1]=101; //;
			//*curr=*curr+3;
			break;
		      }
		    }
		  *gpos=*gpos+1; 
		  break;
  } // of case 1005

  case(1006):
    { /***************************************/
      /*<c-statement>:= <if-true><else-false>*/
      /***************************************/
      for (int i=*length-1;i>*curr;i--) old_expr[i+1]=old_expr[i];
     *length=*length+1; 
      old_expr[*curr]=1007;
      old_expr[*curr+1]=1008;
      //*gpos=*gpos+1;
      break;
    }//of case 1006

 case(1007):
   { /***********************/
     /* <if-true>:= {<expr>}  */
     /***********************/
     for (int i=*length-1;i>*curr;i--) old_expr[i+2]=old_expr[i]; //Move <line> & whatever & <else-false> to end
     *length=*length+2; 
     old_expr[*curr]=102; //{
     old_expr[*curr+1]=1005; //<expr>
     old_expr[*curr+2]=103; //}
     //*curr=*curr+1;
     //*gpos=*gpos+1;
     break;
    }//of case 1007

 case(1008):
   { /***************************/
     /*<else-false>:=else{<expr>}*/
     /***************************/
     for (int i=*length-1;i>*curr;i--) old_expr[i+3]=old_expr[i];
     *length=*length+3; 
     old_expr[*curr]=6;//else
     old_expr[*curr+1]=102; //{
     old_expr[*curr+2]=1005; //<expr>
     old_expr[*curr+3]=103; //}
     //*curr=*curr+2;
     //*gpos=*gpos+1;
     break;
    }//of case 1008 
 case(1009):
   { /********************************/
     /*<progn>:=<op><op>|<op><op><op>*/
     /********************************/
     int r=rnd_num%2;
     switch(r)
       {
       case 0:
	 {
	   for (int i=*length-1;i>*curr;i--) old_expr[i+2]=old_expr[i];
	   *length=*length+2;
	   old_expr[*curr]=7; //progn2
	   old_expr[*curr+1]=1005; //<op>
	   old_expr[*curr+2]=1005; //<op>
	   //*curr=*curr+4;
	   break;
	 }
       case 1:
	 {
	   for (int i=*length-1;i>*curr;i--) old_expr[i+3]=old_expr[i];
	   *length=*length+3;
	   old_expr[*curr]=8; //progn3
	   old_expr[*curr]=1005; //<op>
	   old_expr[*curr+1]=1005; //<op>
	   old_expr[*curr+2]=1005; //<op>
	   //*curr=*curr+5;
	   break;
	 }
       }
     *gpos=*gpos+1;
     break;
    }//of case 1009 
  default : { *curr=*curr+1; cout << "DEFAULT" << endl; break;}//of default
  } // Of switch
}
/*************************************************************************/
void grammar::print_grammar_individual(int old_expr[],int length)
{
  for (int i=0;i<length;i++)
    switch(old_expr[i])
      {
      case 2 : {cout << "trail.left()";break;}
      case 3 : {cout << "trail.right()";break;}
      case 4 : {cout << "trail.move()";break;}
	//5 food_ahead()
      case 5 : {cout << "if(trail.food_ahead()) ";break;}
	//6 else
      case 6 : {cout << "else ";break;}
	//7 PROG2
      case 7 : {cout << "/*PROG2*/ ";break;}
	//8 PROG3
      case 8 : {cout << "/*PROG3*/ ";break;}
      case 51 : {cout << "if(food_ahead()==TRUE) ";break;}
      case 52 : {cout << "else ";break;}
      case 101 : {cout << "; ";break;}
      case 102 : {cout << " {";break;}
      case 103 : {cout << "} ";break;}
      default : {cout << " ERROR ";break;}
	
#if 0
      case 2 : {cout << "LEFT()";break;}
      case 3 : {cout << "RIGHT()";break;}
      case 4 : {cout << "MOVE()";break;}
	//5 food_ahead()
      case 5 : {cout << "if(food_ahead()==TRUE) ";break;}
	//6 else
      case 6 : {cout << "else ";break;}
	//7 PROG2
      case 7 : {cout << "/*PROG2*/ ";break;}
	//8 PROG3
      case 8 : {cout << "/*PROG3*/ ";break;}
      case 51 : {cout << "if(food_ahead()==TRUE) ";break;}
      case 52 : {cout << "else ";break;}
      case 101 : {cout << "; ";break;}
      case 102 : {cout << " {";break;}
      case 103 : {cout << "} ";break;}
      default : {cout << " ERROR ";break;}
#endif
      }
}
/*************************************************************************/
void grammar::fprint_grammar_individual(ostream& output_stream,
					int old_expr[],int length)
{      
  for (int i=0;i<length;i++)
    switch(old_expr[i])
      {
      case 2 : {output_stream << "trail.left()";break;}
      case 3 : {output_stream << "trail.right()";break;}
      case 4 : {output_stream << "trail.move()";break;}
	//5 food_ahead()
      case 5 : {output_stream << "if(trail.food_ahead()) ";break;}
	//6 else
      case 6 : {output_stream << "else ";break;}
	//7 PROG2
      case 7 : {output_stream << "/*PROG2*/ ";break;}
	//8 PROG3
      case 8 : {output_stream << "/*PROG3*/ ";break;}
      case 51 : {output_stream << "if(food_ahead()==TRUE) ";break;}
      case 52 : {output_stream << "else ";break;}
      case 101 : {output_stream << "; ";break;}
      case 102 : {output_stream << " {";break;}
      case 103 : {output_stream << "} ";break;}
      default : {output_stream << " ERROR ";break;}
	
#if 0
      case 2 : {output_stream << "LEFT()";break;}
      case 3 : {output_stream << "RIGHT()";break;}
      case 4 : {output_stream << "MOVE()";break;}
	//5 food_ahead()
      case 5 : {output_stream << "if(food_ahead()==TRUE) ";break;}
	//6 else
      case 6 : {output_stream << "else ";break;}
	//7 PROG2
      case 7 : {output_stream << "/*PROG2*/ ";break;}
	//8 PROG3
      case 8 : {output_stream << "/*PROG3*/ ";break;}
	
      case 51 : {output_stream << "if(food_ahead()==TRUE) ";break;}
      case 52 : {output_stream << "else ";break;}
      case 101 : {output_stream << "; ";break;}
      case 102 : {output_stream << " {";break;}
      case 103 : {output_stream << "} ";break;}
      default : {output_stream << " ERROR ";break;}
#endif
      }
  output_stream << endl;
}
/*************************************************************************/
