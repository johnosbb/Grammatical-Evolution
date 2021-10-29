#!/usr/bin/perl

print "Processing file $ARGV[0]\n";
@fields = split(/\./,$ARGV[0]);

unless (open IN, $ARGV[0]) {
    die "Could not open file $ARGV[0]\n"
}
@data1;
$gp_file = ">".$fields[0].".solutions".".txt";
print "Creating file $gp_file \n";
$filenameout = $gp_file;
unless (open OUT, $filenameout) {
    die "Could not open file $filenameout\n"
}

while(<IN>) {
	($name,@data) = split / +/;
	if($data[1] eq "1")
		{
#	        print "The $name genome has :\n";
#		for($x=0; $x <= $#data ; $x++)
#		   {
#   		   print " $data[$x]";
#		   }
		    print OUT "$data[0]\n";
	        }


}


