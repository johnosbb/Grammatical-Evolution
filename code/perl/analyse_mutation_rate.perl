#!/usr/bin/perl

# Used to analyse the trend of the mutation rate in adaptive algorithms

print "Processing file $ARGV[0]\n";
@fields = split(/\./,$ARGV[0]);

unless (open IN, $ARGV[0])
{
    die "Could not open file $ARGV[0]\n"
}

@data1;
$gp_file = ">".$fields[0].".mrate_stats".".txt";
print "Creating file $gp_file \n";
$filenameout = $gp_file;
unless (open OUT, $filenameout) {
    die "Could not open file $filenameout\n"
}

while(<IN>)
{
    ($name,@data) = split / +/;
    if ($name eq "Average")
    {
        print OUT  "$data[2]";
	#print  "$data[2]\n"
    }
}








