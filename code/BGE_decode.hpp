/********************************************************************/
/*                                                                  */
/*          FILE   :  BGE_DECODE.HPP                                */
/*          AUTHOR :  J.J. COLLINS                                  */
/*          DATE   :  JULY 1997                                     */
/*          SCHOOL :  Dept. Computer Science                        */
/*                    University of Limerick                        */
/*                                                                  */
/*  --------------------------------------------------------------- */
/*    FUNCTIONALITY :                                               */
/* Header file where functions for                                  */
/* 1. Encode numeric form as either binary, Gray or E-code form.    */
/* 2. Decoding binary, Gray or E-code into numeric.                 */
/* 3. Converting from one of binary, Gray or E-code to another.     */
/*                                                                  */
/* Number of bits in E-code is stated in the var num_bits.          */
/* Generates an E-code table based on bits in E-code. This table is */
/* used for encoding/decoding.                                      */
/*                                                                  */
/* The length of the E-code representation (num of bits) is static  */
/* and fixed through the var num_bits which is initialed through the*/
/* constructor.. As E-code is not directly translatable in to binary*/
/* or Gray, conversion is directly constrained by the set E-code bit*/
/*  length in the table.                                            */
/*  --------------------------------------------------------------- */
/*     BUGS : todate, none to report.                               */
/*                                                                  */
/********************************************************************/
#ifndef _BGE_DECODE_H
#define _BGE_DECODE_H 

#ifndef BOOLEAN_BIT
#define BOOLEAN_BIT
enum boolean {f=0, t=1};
typedef boolean bit;
#endif

/********************************************************************/
class BGE_decode
{
  private:
    // D A T A
    bit** table;
    int num_bits;
    int num_enteries;
    int enable_ECODE;
    // M E S S A G E S
    void print_error(int which);
    void generate_E_table();
  public:
    BGE_decode(int nb = 10);  // C O N S T R U C T O R
    ~BGE_decode(); // D E S T R U C T O R
    double decode_Jcode(bit string[], int start, int len);
    // M E S S A G E S   F O R   B I N A R Y   A N D   G R A Y
    bit* convert_binary_to_Gray(bit string[], int start, int len);
    bit* convert_Gray_to_binary(bit string[], int start, int len);
    double decode_binary(bit string[], int start, int len);
    double decode_Gray(bit string[], int start, int len);
    bit* encode_num_as_binary(int number,int number_of_bits);
    bit* encode_num_as_Gray(int number,int number_of_bits);
    // M E S S A G E S   FOR   E - C O D E
    double decode_Ecode(bit string[], int start, int number_of_bits);
    bit* encode_num_as_Ecode(int number,int number_of_bits);
    bit* convert_binary_to_Ecode(bit string[], int start, int number_of_bits);
    bit* convert_Gray_to_Ecode(bit string[], int start, int number_of_bits);
    bit* convert_Ecode_to_binary(bit string[], int start, int number_of_bits);
    bit* convert_Ecode_to_Gray(bit string[], int start, int number_of_bits);
};
/********************************************************************/
#endif




