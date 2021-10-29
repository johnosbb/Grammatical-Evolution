#! /tools2/freeware/bin/perl -w
$number_of_times = 60;

$sa = 0;
$status = 0;
$trials = 20;
for ( $sa = 0; $sa < $number_of_times ; $sa++) {
    if(! system("./getestdummy")) {
	die " ./GramaEvovledummy sa testfile1.cfg $trials r failed at iteration $sa \n"; }

}
for ( $sa = 0; $sa < $number_of_times ; $sa++) {
    if(! system("./getest")) {
	die " ./GramaEvovle sa testfile2.cfg $trials r failed at iteration $sa \n"; }
}



    print " Normal Completion \n";










