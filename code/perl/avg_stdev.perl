#!/usr/bin/perl
# used to filter a cfg.capture.txt file for average stdev values
# these are placed in a .avg_stdev.txt file
# the name of the file to filter is passed on the command line

print "Processing file $ARGV[0]\n";
@fields = split(/\./,$ARGV[0]);

unless (open IN, $ARGV[0]) {
    die "Could not open file $ARGV[0]\n"
}
@data1;
$gp_file = ">".$fields[0].".avg_stdev".".txt";
print "Creating file $gp_file \n";
$filenameout = $gp_file;
unless (open OUT, $filenameout) {
    die "Could not open file $filenameout\n"
}
while(<IN>) {
	($name,@data) = split / +/;
	if($data[0] eq "Stdev")
		{
#	        print "The $name Stdev was $data[1]\n";
		print OUT "$data[1]\n";
	        }


}


