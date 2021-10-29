#ifndef defines_h
#define defines_h 1

#include "defines_common.h"

//#define _PROFILE_
//#define _DUMMY_

#ifdef  _PROFILE_
   #define TARGET_SCORE 100
   #define MAX_GENOME_LENGTH 80
   #define MIN_GENOME_LENGTH 1
#else
   #define TARGET_SCORE 20
   #define MAX_GENOME_LENGTH 1000
   #define MIN_GENOME_LENGTH 10 
#endif




#endif



