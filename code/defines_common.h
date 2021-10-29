#ifndef defines_common_h
#define defines_common_h 1

#define OKAY 1
#define NOT_OKAY 0
#define MAX_GENE_VALUE 255
#define MAX_NO_CHARS_GENE 11
#define CFG_MAX_VALUE_SIZE MAX_GENOME_LENGTH * MAX_NO_CHARS_GENE
#define CFG_MAX_PARAMETER_SIZE 30
#define NUM_OF_OPERATORS 12  // one more than the number of genome operators used
#define SUCCESS 1
#define FAILURE 0
#define MAX_STDEV_VALUE 999

enum MUTATOR
{ Force_up , Force_down , Shrink ,Grow ,  Multiple_mutate , Multiple_mutate_fixed,  Mutate ,EP_Mutate ,EP_Mutate_classic_adaptive, EP_Mutate_with_bias, EP_Mutate_non_random};


#endif // defines_commom_h




