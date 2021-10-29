#! /tools2/freeware/bin/perl -w
$number_of_times = 100;
$sa = 0;
$status = 0;
$trials = 1;
for ( $sa = 0; $sa < $number_of_times ; $sa++) {
    if(! system("./GramaEvovledummy rs testfile1.cfg $trials r ")) {
	die " ./GramaEvovledummy rs testfile1.cfg $trials r failed at iteration $sa \n"; }

}
for ( $sa = 0; $sa < $number_of_times ; $sa++) {
    if(! system("./GramaEvovle rs testfile11.cfg $trials r ")) {
	die " ./GramaEvovle rs testfile11.cfg $trials r failed at iteration $sa \n"; }
}

for ( $sa = 0; $sa < $number_of_times ; $sa++) {
    if(! system("./GramaEvovledummy hc testfile2.cfg $trials r ")) {
	die " ./GramaEvovledummy hc testfile2.cfg $trials r failed at iteration $sa \n"; }
}
for ( $sa = 0; $sa < $number_of_times ; $sa++) {
    if(! system("./GramaEvovle hc testfile12.cfg $trials r ")) {
	die " ./GramaEvovle hc testfile12.cfg $trials r failed at iteration $sa \n"; }
}


for ( $sa = 0; $sa < $number_of_times ; $sa++) {
    if(! system("./GramaEvovledummy sa testfile3.cfg $trials r ")) {
	die " ./GramaEvovledummy sa testfile3.cfg $trials r failed at iteration $sa \n"; }
}
for ( $sa = 0; $sa < $number_of_times ; $sa++) {
    if(! system("./GramaEvovle sa testfile13.cfg $trials r ")) {
	die " ./GramaEvovle sa testfile13.cfg $trials r failed at iteration $sa \n"; }

}

for ( $sa = 0; $sa < $number_of_times ; $sa++) {
    if(! system("./GramaEvovledummy brs testfile4.cfg $trials r ")) {
	die " ./GramaEvovledummy brs testfile4.cfg $trials r failed at iteration $sa \n"; }
}

for ( $sa = 0; $sa < $number_of_times ; $sa++) {
    if(! system("./GramaEvovle brs testfile14.cfg $trials r ")) {
	die " ./GramaEvovle brs testfile14.cfg $trials r failed at iteration $sa \n"; }

}

    print " Normal Completion \n";










