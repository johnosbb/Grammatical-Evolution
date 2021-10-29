#!/usr/bin/perl
# This file counts the terms in a santafe solution 
# It takes the output from the Analyser program
 
print "Processing file $ARGV[0]\n";
@fields = split(/\./,$ARGV[0]);

unless (open IN, $ARGV[0])
{
    die "Could not open file $ARGV[0]\n"
}

@data1;
$total_termcount = 0;
$total_records = 0;
while(<IN>)
{

    ($name,@data) = split / +/;
    $termcount = 0;
    
    if($name eq "Output_Code:")
    {
	$total_records += 1;
	for($x=0; $x <= $#data ; $x++)
	{
	    if ($data[$x] eq "*" ||
		$data[$x] eq "-" ||
		$data[$x] eq "+" ||
		$data[$x] eq "/" ||
		$data[$x] eq "Sin" ||
		$data[$x] eq "Cos" ||
		$data[$x] eq "Exp" ||
		$data[$x] eq "Log" ||
		$data[$x] eq "X" ||
		$data[$x] eq "1.0" ||
		$data[$x] eq "(" ||
		$data[$x] eq ")" 
		)
	    {
		$termcount += 1;
	    }

	}
	print " $termcount \n";
	$total_termcount += $termcount;
    }
   
}    

$average_termcount = $total_termcount/$total_records;
print "Total number of Terms $total_termcount\n";
print "Total number of Records $total_records\n";
print "Average Number of Terms per Solution $average_termcount\n";







