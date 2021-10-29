#! /usr/bin/perl -w
first argumnet is the starting point the second is the end point

print "Processing file $ARGV[0]\n";
@fields = split(/\./,$ARGV[0]);



unless (open IN, $ARGV[0]) {
    die "Could not open file $ARGV[0]\n"
}



$gp_file = ">".$fields[0].".cfg.capture.".$fields[3].".zoom.txt";
print "Creating file $gp_file for range  $ARGV[1] to $ARGV[2] \n";
$filenameout = $gp_file;
unless (open OUT, $filenameout) {
    die "Could not open file $filenameout\n"
}

$printflag = "0";
while (<IN>) {
    chomp;
    $words = $_;
    @words = split;
    if($words[0] == $ARGV[1]) {
	$printflag = "1";
    }
    if($words[0] == $ARGV[2]) {
	$printflag = "0";
    }
    if($printflag == "1") {
	print OUT "$_\n";
    }

}

print "Complete!\n";
close(IN);
close(OUT);













