#! /usr/bin/perl -w
# takes the search capture  file (passed as an argument) and creates a gnuplot file which creates a .png
# file when run. This .png file displays a graphic representation of the search space

print "Processing file $ARGV[0]\n";
@fields = split(/\./,$ARGV[0]);

unless (open IN, $ARGV[0]) {
    die "Could not open file $ARGV[0]\n"
}
$gp_file = $fields[0].".neighbourhood.".$fields[1].".gp";
print "Creating file $gp_file \n";
$filenameout = ">".$gp_file;
unless (open OUT, $filenameout) {
    die "Could not open file $filenameout\n"
}

print OUT "set title \"Neighbourhood of a Symbolic Integration Solution \"\n";
print OUT "set xlabel \"All Neighbours with a Hamming Distance of 1 from the Solution\"\n";
print OUT "set ylabel \"Fitness\"\n";
#print OUT "set size 1.0, 0.55\n";
#print OUT "set origin 0.1, 1.3\n";
print OUT   "plot [] [0:1]  \"$ARGV[0]\"   title 'Solution Neighbourhood' with lines\n";
print OUT "pause -1\n";
print OUT "set terminal fig monochrome landscape small \n";
print OUT "set out \"";
print OUT $gp_file;
print OUT ".fig\"\n";
print OUT "replot\n";
close(IN);
close(OUT);




