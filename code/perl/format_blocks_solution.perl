#!/usr/bin/perl
# This file formats the output program from santafe
# It takes the output from the Analyser program
 
print "Processing file $ARGV[0]\n";
@fields = split(/\./,$ARGV[0]);

unless (open IN, $ARGV[0])
{
    die "Could not open file $ARGV[0]\n"
}

@data1;
$braceflag = 0;
$gp_file = ">".$fields[0].".formated".".txt";
print "Creating file $gp_file \n";
$filenameout = $gp_file;
unless (open OUT, $filenameout) {
    die "Could not open file $filenameout\n"
}

while(<IN>)
{
    ($name,@data) = split / +/;
    if($name eq "Output_Code:")
    {
	for($x=0; $x <= $#data ; $x++)
	{
	    for($y=0; $y < $braceflag ; $y++)
	    {
		print OUT " ";
	    }
	    
	    if ($data[$x] eq "DO")
	    {
		print OUT "DO\n";
		$braceflag += 3;
	    }
	    elsif ($data[$x] eq "UNTIL")
	    {
		print OUT "UNTIL\n";
	    }

	    
	    elsif ($data[$x] eq "ODU")
	    {
		print OUT "ODU\n";
		$braceflag -= 3;
	    }    
	    elsif ($data[$x] eq "(")
	    {
		print OUT "(";
	    }
	    elsif ($data[$x] eq "!")
	    {
		print OUT "!";
	    }
	    
	    elsif ($data[$x] eq ")")
	    {
		print OUT ")\n";
	    }


	    elsif ($data[$x] eq "NN")
	    {
		print OUT "NN";
	    }

	    elsif ($data[$x] eq "TB")
	    {
		print OUT "TB";
	    }

	    elsif ($data[$x] eq "CS")
	    {
		print OUT "CS";
	    }


	    elsif ($data[$x] eq "MS")
	    {
		print OUT "MS";
	    }

	    elsif ($data[$x] eq "MT")
	    {
		print OUT "MT";
	    }

	    else
	    {
		print OUT "$data[$x]\n";
	    }
	}	
	print OUT "\n";
        print OUT "--------------------------------------------\n";
    }
    
}
	    









