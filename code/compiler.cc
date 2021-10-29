/*
 * called from GE/ge.cc::compile()
 *
 * - an individual's code is output to a file "individual.cc"
 * - use this file to invoke your favourite compiler on the source
 *   then run the exectuable
 * - the individual's program should output the fitness score to a file
 *   "score.dat" (user must implement this either in the grammar or by
 *    using wrappers as described below), this file is read by ge
 * - If wrappers are required in addition to the output code just include
 *   the individual.cc file within another file that has the wrappers,
 *   ensuring to output the fitness to the file score.dat, and compile and 
 *   run this file below instead!
 */

  if( system("g++ -o individual individual.cc") != -1 ){
    system("./individual");
    system("rm -f individual.cc");
    system("rm -f individual");
  }
