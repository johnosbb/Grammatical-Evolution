/*************************************************************************/
/*                                                                       */
/*             FILE   :  getest.cc                                       */
/*             AUTHOR :  Michael O'Neill                                 */
/*             DATE   :  April 2000                                      */
/*             SCHOOL :  Dept. Computer Science                          */
/*                       University of Limerick                          */
/*                                                                       */
/*  -------------------------------------------------------------------  */
/*    FUNCTIONALITY :                                                    */
/*      Demonstration of GE for Santa Fe Trail                           */
/*  -------------------------------------------------------------------  */
/*     BUGS : todate, none to report.                                    */
/*                                                                       */
/*************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "ge.hpp"
#include "Random.hpp"
#include "params.h"
#include <new.h>
#include <time.h>
#define NUMBITS 160
#define BYTE 8

double decode_binary(int[],int,int);
int convertToUnsignedByte(int d, int binarystring[]);
void intArrayToBinaryArray(int i[],int b[]);


int main()
{
  int * binarystring ;
  int time_elapsed;
  time_t start_time;
  time(&start_time);
  Random r;
  
  for(int f=1; f< 80500 ;f ++)
{
  //myrandomize();

  int binaryStringLength =  r.randomint(196);
  if (binaryStringLength < 8)
    {
      f--;
      continue;
    }
  
  binarystring = new int[binaryStringLength];  
  fprintf(stdout,"Starting GE test program.....\n");

  /* create binary string */

  fprintf(stdout,"cycle %d....\n",f);
  for(int i=0;i< binaryStringLength ;i++){
    if(r.randomint(2))
      binarystring[i] = 1;
    else  binarystring[i] = 0;
  }
  
  fprintf(stdout,"The Input Binary String is : ");
  for(int i=0;i< binaryStringLength;i++) fprintf(stdout,"%d",binarystring[i]);
  fprintf(stdout,"\n");
  //intArrayToBinaryArray(intarray,binarystring);
  /* map with GE */ 
  //for(int i=0;i< binaryStringLength;i++) fprintf(stdout,"%d",binarystring[i]);
  //fprintf(stdout,"\n");
  double fitness = 0.0;
  //ge mapobject(&fitness,binaryStringLength,binarystring,1,0);
  fprintf(stdout,"Fitness (%f)\n",fitness);
  delete [] binarystring;
  
}
      time_t finish_time;
      time(&finish_time);
      time_elapsed = (int)(finish_time - start_time);
      cout << "Time Elapsed : " << time_elapsed << endl;   

  //fprintf(stdout,"Finished GE test!\n");
  return 1;
}



double decode_binary(int string[], int start, int len)
{
  /*********************************************/ 
  /* Decode a binary string to numeric, from   */ 
  /* string position "start" up to start + len */ 
  /*********************************************/ 
  double accum = 0.0;
  double powerof2 = len-1;
  for (int j=start; j < (start+len); j++){
    accum = accum + (string[j] * pow(2,powerof2));
    powerof2--;
  }
  return accum;
}


int convertToUnsignedByte(int d, int binarystring[])
{
  int  powerof2,p;
  powerof2 = 0;
  int i = 0;
  int f = 0;
  
  p = 7;
  while(!(p < 0))
    {
        if( pow(2,p) < d || pow(2,p) == d)
	  {
	    binarystring[i++] = 1;
	    d = d - pow(2,p);
	  }
	else 
	  binarystring[i++] = 0;
	p = p - 1;
    }
  return 1;
  
}

void intArrayToBinaryArray(int i[],int b[])
{
  int count =0;
  int count2 = 0;
  int binaryarray[BYTE];
  while(i[count] != 99)
    count++;
  for(int f = 0; f < count ; f++)
    {
      convertToUnsignedByte(i[f],binaryarray);
      for(int g = 0; g < BYTE ; g++)
	b[g + count2] = binaryarray[g];
      count2 = count2 + BYTE;
    }
  b[count2]= 99;
  
}
