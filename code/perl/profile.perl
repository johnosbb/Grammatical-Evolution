#! /usr/bin/perl -w
$number_of_times = 10;
$sa = 0;
$status = 0;
$trials = 20;
for ( $sa = 0; $sa < $number_of_times ; $sa++) {
    if(! system("./GramaEvovledummy sa testfile1.cfg $trials r ")) {
	die " ./GramaEvovledummy sa testfile1.cfg $trials r failed at iteration $sa \n"; }

}
for ( $sa = 0; $sa < $number_of_times ; $sa++) {
    if(! system("./GramaEvovle sa testfile2.cfg $trials r ")) {
	die " ./GramaEvovle sa testfile2.cfg $trials r failed at iteration $sa \n"; }
}

for ( $sa = 0; $sa < $number_of_times ; $sa++) {
    if(! system("./GramaEvovledummy rs testfile3.cfg $trials r ")) {
	die " ./GramaEvovledummy rs testfile3.cfg $trials r failed at iteration $sa \n"; }
}
for ( $sa = 0; $sa < $number_of_times ; $sa++) {
    if(! system("./GramaEvovle rs testfile4.cfg $trials r ")) {
	die " ./GramaEvovle rs testfile4.cfg $trials r failed at iteration $sa \n"; }
}


for ( $sa = 0; $sa < $number_of_times ; $sa++) {
    if(! system("./GramaEvovledummy hc testfile5.cfg $trials r ")) {
	die " ./GramaEvovledummy hc testfile5.cfg $trials r failed at iteration $sa \n"; }
}
for ( $sa = 0; $sa < $number_of_times ; $sa++) {
    if(! system("./GramaEvovle hc testfile6.cfg $trials r ")) {
	die " ./GramaEvovle hc testfile6.cfg $trials r failed at iteration $sa \n"; }

}

    print " Normal Completion \n";















