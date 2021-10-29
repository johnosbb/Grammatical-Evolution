#include <string.h>
#include <unistd.h>		   // To use PID
#include <sys/types.h>		   // To use PID
#include <sys/stat.h>		   // for stat
#include <signal.h>		   // for signal
#include "gstream.hpp"

#define NUMPOSSFILES   20	   // Max number of files

#ifdef _ELLIPSIS
static void sigfunc(int,...);
#else
static void sigfunc(int);
#endif
/*******************************************************/
gstream::gstream(char* _initStr, plotType _plType, mybool _flush)
{
  // signal trapping
  signal(SIGTERM, sigfunc); // added JGH
  signal(SIGINT, sigfunc);  // added JGH
  signal(SIGHUP, sigfunc);  // added JGH

  gnuFile = popen( "gnuplot", "w" ); // open pipe to gnuplot
  if (gnuFile == 0) {
    cerr << "gnuPlot is not present or whatever other circunstance\n";
    exit(1);
  }    
  fprintf( gnuFile, "%s\n", _initStr );
     
  // find a name based on the process PID, plus a random number.
  unsigned procnum = getpid();
  struct stat dummy;
  do {	  
    sprintf( tempGnu, "gnu.tmp%d.%d", procnum, randomint(NUMPOSSFILES)); 
				   // as there are few possible files, there 
				   // may be filename conflicts
    } while ( stat( tempGnu, &dummy ) == 0 ); // while the file exists
	  
  tempF.open( tempGnu, ios::out); 
        
  // assign to instance variables
  switch ( _plType ) {
	  case LINES : plType = 'l'; break;
	  case DOTS : plType = 'd'; break;
	  case POINTS : plType = 'p'; break;	
	  case BOXES : plType = 'b'; break;
  }

  flush = _flush;
  if (flush) tempF.close();  // to create it, but not write
}
/*******************************************************/
gstream::~gstream( )
{
  const char* constGnu = tempGnu; // little trick to make variable
				  // a const string
  if (!flush) tempF.close();
  // closes pipe first, to not have trouble with non-existing files
  pclose( gnuFile );	
  remove( constGnu );  // removes the disk file
}
/*******************************************************/
void gstream::rePlot( )
{
//-----------------------------------------
// -- Plots whatever is in the file
// ----------------------------------------
  fprintf( gnuFile, "plot \"%s\" w %c\n",  tempGnu, plType );
  fflush( gnuFile);		  
}
/*******************************************************/
void gstream::reStart( void ) 
{
//-----------------------------------------
// -- Empties the buffer, and starts all over again
//-----------------------------------------  
  if ( !flush ) {
    tempF.close();
    rePlot();
    tempF.open( tempGnu, ios::out ); // puts pointer at the beginning
  }
  else {
    // puts pointer at the beginning of the file and closes it
    tempF.open( tempGnu, ios::out ); 
    tempF.close();
    }  
}
/*******************************************************/
gstream& gstream::operator << ( float _out) 
{
//----------------------------------------------
// -- output functions
//----------------------------------------------    
  if ( flush == TRUE ) tempF.open( getTemp(), ios::out|ios::app);
  tempF << _out << "\n";  
  if ( flush == TRUE ) {
    tempF.close();
    rePlot();
  }  
  return *this;
}
/*******************************************************/
gstream& gstream::operator << ( const float* _out) 
{
//----------------------------------------------
// --	output functions; takes only the first 2 
//      elements of the array only.
//---------------------------------------------- 
  if ( flush == TRUE ) tempF.open( getTemp(), ios::out|ios::app);	    
  tempF << _out[0] << " " << _out[1] << "\n"; 
  if ( flush == TRUE ) {
    tempF.close();
    rePlot();  
  }
  return *this;
}
/*******************************************************/
gstream&  gstream::operator << (  const char* _out) 
{
//----------------------------------------------
// -- output functions
//----------------------------------------------    
  if (flush == TRUE) tempF.open( getTemp(),ios::out|ios::app);	    
  // open for output && append
  tempF << _out << "\n";   // cannot have more than 2 comps
  if (flush == TRUE ) {
    tempF.close();
    rePlot();  
  }
  return *this;
}
/*******************************************************/
#ifndef _ELLIPSIS
void sigfunc(int) 
#else
void sigfunc(int, ...) 
#endif
{
//----------------------------------------------
// -- cleans up if ctrl-c or other similar key is pressed
//-------------------------------------------------------
  unsigned numproc = getpid();
  char tempGnu[17];
  // delete all the files, of the max 20. All this is 
  // done to prevent using global variables.
  for ( unsigned i= 0; i < NUMPOSSFILES; i ++ )  {
    sprintf( tempGnu, "gnu.tmp%d.%d", numproc, i ); 
    // unlink temporary file  Does not matter if it does not exist.
    remove(tempGnu ); 
  }
  exit(1); // exit closes files, thus getting rid of gnuplot.
}
/*******************************************************/







