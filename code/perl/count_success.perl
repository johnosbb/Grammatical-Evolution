#!/tools2/freeware/bin/perl -w
# the script is used to count the number of successful runs for GA
# it processes a testfile.results.txt file

print "Processing file $ARGV[0]\n";
unless (open IN, $ARGV[0]) {
    die "Could not open file $ARGV[0]\n"
  }
$total = 0;
$total_records = 0;
while(<IN>)
  {
    ($name,@data) = split / +/;
    $total += $name;
    $total_records += 1;
		  
  
    

  }
$percent = ($total/$total_records)* 100;
print "Total number of evaluations was $total_records \n ";
print "Total number of successes was $total\n";
print "Percentage success was $percent\n";
