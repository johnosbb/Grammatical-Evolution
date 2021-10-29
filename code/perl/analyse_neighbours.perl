#!/usr/bin/perl
# used to analyse a santafe_neighbours.txt file for number of succesful neighbours

print "Processing file $ARGV[0]\n";
@fields = split(/\./,$ARGV[0]);

unless (open IN, $ARGV[0]) {
    die "Could not open file $ARGV[0]\n"
}
@data1;
$num_success = 0;
$num_failed = 0;
$total = 0;
while(<IN>) {
	($name,@data) = split / +/;
        $total += 1;
#        print  "$data[1]\n";        
	if($data[1] eq "88\n")
		{
		    $num_success += 1;
		    print  "$data[1] ";
	        }


}

$percent = ($num_success/$total) * 100;
print "\nSuccessful neighbours $num_success\n";
print "Total neighbours $total\n";
print "Percentage of total $percent %\n";








