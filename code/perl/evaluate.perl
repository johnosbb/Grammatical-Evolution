#! /tools2/freeware/bin/perl -w
$number_of_times = 1000;


$sal = 0;
for ( $sal = 0; $sal < $number_of_times ; $sal++) {
    print "Evaluation $sal\n";
    if(!system("./prog testfile")) {
	die "prog testfile failed on iteration $sal"; }
}
print "Normal Termination\n"











