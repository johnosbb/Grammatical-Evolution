/********************************************************************/
/*                                                                  */
/*          FILE   :  BGE_DECODE.CC                                 */
/*          AUTHOR :  J.J. COLLINS                                  */
/*          DATE   :  NOVEMBER 1996                                 */
/*          SCHOOL :  Dept. Computer Science                        */
/*                    University of Limerick                        */
/*                                                                  */
/*  --------------------------------------------------------------- */
/*    FUNCTIONALITY :                                               */
/*  Implements object declared in header file "BGE_decode.hpp".     */
/*  --------------------------------------------------------------- */
/*     BUGS : todate, none to report.                               */
/*                                                                  */
/********************************************************************/
#include <iostream.h>
#include <math.h>
#include <stdlib.h>
#include "BGE_decode.hpp"
#include "defines.h"
#include "params.h"
/********************************************************************/
BGE_decode::BGE_decode(int nb)
{
  /*********************************************/
  /* CONSTRUCTOR.                              */
  /*********************************************/
  num_bits = nb;
  if((CODE_SCHEME == E_CODE) || (CODE_SCHEME== DYNAMIC) || (CODE_SCHEME==BOOL_DYNAMIC))
    enable_ECODE = 1; 
  else enable_ECODE = 0;
  num_enteries = (int)(pow(2,num_bits));
  if(enable_ECODE) {
    if ((num_enteries /1000000) > 128) {
      cerr << "\n ERROR: using E-code, no. entries in E-code table = "
           << num_enteries
           << "\n         which requires " << num_enteries/1000000 << " RAM.";
      exit(1);
    }
    table = new bit*[num_enteries];
    for(int i=0; i<num_enteries;i++)
      table[i] = new bit[num_bits];
    generate_E_table();
  }
}
/********************************************************************/
BGE_decode::~BGE_decode()
{
  /*********************************************/
  /* DESTRUCTOR .                              */
  /* deallocates memory required to build the  */
  /* E-code table.                             */
  /*********************************************/
  if(enable_ECODE) {
    for(int z1=0; z1<num_enteries; z1++)
      delete[] table[z1];
    delete[] table;
  }
}

/********************************************************************/
void BGE_decode::print_error(int which)
{
  /*********************************************/
  /* Private member function, which displays   */
  /* error messages to the standard I/O device */
  /*********************************************/
  cout << "\n Error: ";
  switch(which) {
    case 1: cout << "total != num_enteries";
            break;
    case 2: cout << "number of bits specified for representation too small";
            break;
    case 3: cout << "Ecode table dependent on number of bits used ("
                 << num_bits << ")"
                 << "\n        which must be the same as the third argument";
            break;
    case 4: cout << "\n ERROR: no match\n";
            break;
    case 5: cout << "\n ERROR: E-code not enabled. exiting!\n";
            break;
  }
  cout << "\n TERMINATING PROGRAM \n";
  exit(1);
}
/********************************************************************/
void BGE_decode::generate_E_table()
{
  /*********************************************/ 
  /* Private member function which generates   */
  /* the E-code table. This table resides in   */
  /* memory during the lifetime of the object. */
  /* The length of the E-code representation   */
  /* (number of bits) is static and fixed, and */
  /* this value is in the file "defines.h".    */
  /* As E-code is not directly translatable in */
  /* to binary or Gray, conversion is directly */
  /* constrained by the set E-code bit length  */
  /* in the table.                             */
  /*********************************************/  
  bit **temp_table = new bit*[num_enteries];
  for(int s=0; s<num_enteries; s++)
    temp_table[s] = new bit[num_bits];
  for(int i=0; i<num_enteries; i++)
    temp_table[i] = (bit*)encode_num_as_binary(i,num_bits);

  for(int num2=0; num2 < num_bits; num2++) {
    table[0][num2] = f;
    table[num_enteries-1][num2] = t;
  }

  int total = 2;
  int pos=1;
  for(int num_ones=1; num_ones < num_bits; num_ones++){
    for(int num3=1; num3<num_enteries-1; num3++) {
      
      int ones = 0;
      for(int j=0; j<num_bits; j++)
	if(temp_table[num3][j]==t) ones++;    

      if(ones==num_ones) {
	table[pos] = temp_table[num3];
	total++;
        pos++;
      }
    }
  }
  if(total!= num_enteries) print_error(1);
  delete temp_table;
}
/********************************************************************/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*             J - C O D E       F U N C T I O N S                  */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/********************************************************************/
double BGE_decode::decode_Jcode(bit string[], int start, int len)
{
  /*********************************************/ 
  /* Decode a binary string to numeric, from   */ 
  /* string position "start" up to start + len */ 
  /*********************************************/ 
  int test;
  double num2;
  double accum = 0.0;
  double powerof2 = len-1;
  test = 0;
  for (int j=start; j < (start+len); j++){
    accum = accum + (string[j] * pow(2,powerof2));
    powerof2--;
  }
  num2 = 3.0;
  while(num2 < accum) num2 += 8.0;
  if(accum == num2) {
    accum += 1.0;
    test = 1;
  }
  num2 = 4.0;
  if(!test) {
    while(num2 < accum) num2 += 8.0;
    if(accum == num2) accum = accum - 1.0;
  }
  return accum;
}

/********************************************************************/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*       B I N A R Y    A N D    G R A Y    F U N C T I O N S       */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/********************************************************************/
bit* BGE_decode::convert_binary_to_Gray(bit string[], int start, int len)
{
  /*********************************************/ 
  /* Convert a binary string to Gray code, from*/ 
  /* string position "start" up to start + len */
  /*********************************************/ 
  bit *z = new bit[len];
  int hold;
  z[0] = string[start];
 
  int count=1;
  for(int k= start+1; k < (start+len); k++) {
    hold = string[k] + string[count-1];
    if (hold ==2) z[count] = f;
    else {
      if (hold ==0) z[count] = f;
      else z[count] = t;
    }
    count++;
  }    
  return z;
}
/********************************************************************/
bit* BGE_decode::convert_Gray_to_binary(bit string[], int start, int len)
{
  /*********************************************/
  /* Convert a Gray string to binary code, from*/ 
  /* string position "start" up to start + len */ 
  /*********************************************/ 
  bit *z = new bit[len];
  int hold;
  z[0] = string[start];

  int count=1;
  for (int k=start+1; k < (start + len); k++) {
    hold = string[k] + z[count-1];
    if (hold ==2) z[count] = f;
    else {
      if (hold ==0) z[count] = f;
      else z[count] = t;
    }
    count++;
  }
  return z;
}
/********************************************************************/
double BGE_decode::decode_binary(bit string[], int start, int len)
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
/********************************************************************/
double BGE_decode::decode_Gray(bit string[], int start, int len)
{
  /*********************************************/ 
  /* Decode a Gray string to numeric(real),from*/ 
  /* string position "start" up to start + len */ 
  /*********************************************/ 
  double res;
  bit *new_string = convert_Gray_to_binary(string,start,len);
  res = decode_binary(new_string,0,len);
  delete new_string;
  return res;
}
/********************************************************************/
bit* BGE_decode::encode_num_as_binary(int number,int number_of_bits)
{
  /*********************************************/
  /* Encode numeric (integer) into binary code */
  /* string, where str length= "number_of_bits"*/ 
  /*********************************************/ 
  int j=0;
  while((int)(pow(2,j)) <= number) j++;
  if(j > number_of_bits) print_error(2);

  bit *string = new bit[number_of_bits];
  for(int l=0; l<number_of_bits; l++) 
    string[l] = f;

  for(int k=0; k<j; k++) {
    int next = number/2;
    int modula = number % 2;
    if(modula==0) string[k]=f;
    else string[k]=t;
    number = next;
  }
  
  bit *new_string = new bit[number_of_bits];
  for (int m=0; m<number_of_bits; m++)
    new_string[m] = string[(number_of_bits-1)-m];
 
  return new_string;
} 
/********************************************************************/
bit* BGE_decode::encode_num_as_Gray(int number,int number_of_bits)
{
  /*********************************************/ 
  /* Encode numeric (integer) into Gray coded  */
  /* string, where str length= "number_of_bits"*/ 
  /*********************************************/ 
  bit *string = (bit*)encode_num_as_binary(number,number_of_bits);
  bit *new_string = (bit*)convert_binary_to_Gray(string,0,number_of_bits);
  return new_string;
} 
/********************************************************************/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*               E - C O D E    F U N C T I O N S                   */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/********************************************************************/
double BGE_decode::decode_Ecode(bit string[], int start, int number_of_bits)
{ 
  /*********************************************/ 
  /* Decode an E-code string to numeric (real),*/
  /* from string position "start" up to start+ */
  /* number_of_bits. If "number_of_bits" !=    */
  /* string length in E-code table, decoding is*/
  /* not possible -> exit.                     */ 
  /*********************************************/ 
  if(!enable_ECODE) print_error(5);    
  if(number_of_bits != num_bits) print_error(3);
  int pos =0;
  int found=0;
  while((pos< num_enteries) && (!found)){
    int pos1=start;
    while((pos1 < num_bits+start)&&(table[pos][pos1-start]==string[pos1]))
      pos1++;
    if((pos1-start) == num_bits) found=1;
    else pos++;
  }
  if(!found) print_error(4);
  return (double)(pos);
}
/********************************************************************/
bit* BGE_decode::encode_num_as_Ecode(int number,int number_of_bits)
{
  /*********************************************/ 
  /* Encode numeric (integer) as E-code string,*/
  /* If "number_of_bits" != string length in   */
  /* E-code table, encoding not possible ->exit*/
  /*********************************************/
  if(!enable_ECODE) print_error(5);     
  if(number_of_bits != num_bits) print_error(3);
  if(num_enteries < number+1) print_error(2);
  bit *temp = new bit[num_bits];
  for(int c1=0; c1 < num_bits; c1++) 
    temp[c1] = table[number][c1];
  return temp;
}
/********************************************************************/
bit* BGE_decode::convert_binary_to_Ecode(bit string[], int start, int number_of_bits)
{
  /*********************************************/ 
  /* Convert binary string, from strng position*/ 
  /* "start" to "start + number_of_bits"; to   */
  /* E-code string                             */
  /* If "number_of_bits" != string length in   */
  /* E-code table, encoding not possible ->exit*/
  /*********************************************/ 
  if(!enable_ECODE) print_error(5);    
  if(number_of_bits != num_bits) print_error(3);
  int res = (int)(decode_binary(string,start,number_of_bits));
  bit *new_string = (bit*)encode_num_as_Ecode(res,number_of_bits);
  return new_string;
}
/********************************************************************/
bit* BGE_decode::convert_Gray_to_Ecode(bit string[], int start, int number_of_bits)
{
  /*********************************************/ 
  /* Convert Gray string, from string position */ 
  /* "start" to "start + number_of_bits"; to   */
  /* E-code string                             */
  /* If "number_of_bits" != string length in   */
  /* E-code table, encoding not possible ->exit*/
  /*********************************************/
  if(!enable_ECODE) print_error(5);     
  if(number_of_bits != num_bits) print_error(3);
  int res = (int)(decode_Gray(string,start,number_of_bits));
  bit *new_string = encode_num_as_Ecode(res,number_of_bits);
  return new_string;
}
/********************************************************************/
bit* BGE_decode::convert_Ecode_to_binary(bit string[], int start, int number_of_bits)
{
  /*********************************************/ 
  /* Convert E-code string, from strng position*/ 
  /* "start" to "start + number_of_bits"; to   */
  /* binary string                             */
  /* If "number_of_bits" != string length in   */
  /* E-code table, encoding not possible ->exit*/
  /*********************************************/ 
  if(!enable_ECODE) print_error(5);    
  if(number_of_bits != num_bits) print_error(3);
  int res = (int)(decode_Ecode(string,start,number_of_bits));
  bit *new_string = encode_num_as_binary(res,number_of_bits);
  return new_string;
}
/********************************************************************/
bit* BGE_decode::convert_Ecode_to_Gray(bit string[], int start, int number_of_bits)
{
  /*********************************************/ 
  /* Convert E-code string, from strng position*/ 
  /* "start" to "start + number_of_bits"; to   */
  /* Gray string                               */
  /* If "number_of_bits" != string length in   */
  /* E-code table, encoding not possible ->exit*/
  /*********************************************/
  if(!enable_ECODE) print_error(5);    
  if(number_of_bits != num_bits) print_error(3);
  int res = (int)(decode_Ecode(string,start,number_of_bits));
  bit *new_string  = encode_num_as_Gray(res,number_of_bits);
  return new_string;
}
/********************************************************************/









