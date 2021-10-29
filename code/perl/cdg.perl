#! /usr/bin/perl -w
# takes the search capture  file (passed as an argument) and creates a gnuplot file which creates a .png
# file when run. This .png file displays a graphic representation of the search space

print "Processing file $ARGV[0]\n";
@fields = split(/\./,$ARGV[0]);

unless (open IN, $ARGV[0]) {
    die "Could not open file $ARGV[0]\n"
}
#while (<IN>) {
#    chomp;
#    print "$_\n";
#}

$gp_file = ">".$fields[0].".capture.".$fields[3].".gp";
print "Creating file $gp_file \n";
$filenameout = $gp_file;
unless (open OUT, $filenameout) {
    die "Could not open file $filenameout\n"
}

print OUT "set title \"Search Trajectory for Trial  \"\n";
print OUT "set xlabel \"Iteration\"\n";
print OUT "set ylabel \"Score\"\n";
print OUT "set size 1.0, 0.55\n";
#print OUT "set origin 0.1, 1.3\n";
print OUT   "plot  [] [0:88] \"$ARGV[0]\"  using 3 title 'Selected Path' with lines\n";
print OUT   "replot   \"$ARGV[0]\"  using 5 title 'Explored Path' with lines\n";
print OUT "pause -1\n";
print OUT "set terminal png small color\n";
print OUT "set out \"testfile.cfg.capture.0.png\"\n";
print OUT "replot\n";
close(IN);
close(OUT);


#

#set autoscale
#set size  2.0 , 2.0
#set origin 0.0 , 0.0
#set multiplot

#set size 1.0, 0.55
#set origin 0.1, 0.7
#set title
#set title "Best Energy Values"
#plot  "energy1.dat"  thru f1(x) using 3 title 'Best Energy' with lines
#set size 1.0, 0.55
#set origin 0.1, 0.7
#set label 1 'Initial Temperature : 0.4 ' at screen .05 ,screen .05
#set label 2 'Minimum Temperature : 0.005 ' at screen .330 ,screen .05
#set label 3 'Iterations : 15 ' at screen .65 ,screen .05
#set label 5 'Temp Chng 0.95'at screen 1 ,screen .05
#set label 6 'Number of successes for Final values: 16'at screen .05 ,screen .08
#set label 7 'Number of successes for Best values: 16'at screen .50 ,screen .08
#set label 8 'Number of Evaluations: 1.29e+06'at screen .05 ,screen .11
#set label 9 'Wrapping : 1'at screen .40 ,screen .11
#set label 10 'Problem : santafe'at screen .55 ,screen .11
#set label 4 'Used Bias 20,2' at screen .75 ,screen .11
#set size 1.0,0.5
#set origin 0.1, 0.2
#set title
#set title "Delta between Best and Final Energy"
#plot "energy1.dat"  using ($2 - $3) title 'Delta' with lines
#set nomultiplot



