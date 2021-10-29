#ifndef __GSTREAM_HPP
#define __GSTREAM_HPP

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <iostream.h>
#include <fstream.h>
#include <stdio.h>
#include "myrandom.h"

#ifdef FALSE
#undef FALSE
#endif
#ifdef TRUE
#undef TRUE
#endif

typedef char fileName[100];
typedef enum mybool { FALSE=0, TRUE };
typedef enum plotType { LINES, DOTS, POINTS, BOXES };

class gstream {

  private:

    FILE* gnuFile;		// pipe to gnuplot
    fstream tempF;		// to contain output file
    char tempGnu[17];	        // Name of temp file and initString
    char plType;
    mybool flush;
    const char* getTemp() const { return tempGnu; };
    void rePlot();		// private func

  public:

    gstream( char* _initStr, plotType _plType = LINES, mybool _flush = TRUE );
    ~gstream(); 
    void    reStart( void );
    gstream& operator << ( float );
    gstream& operator << ( const float* );
    gstream& operator << ( const char* );
};

#endif


