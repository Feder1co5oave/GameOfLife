#!/bin/perl -w
use constant N => 8;
my $SIZE = 1000;
my $STEP = 1000;

print "[\n";
foreach my $p (10,12,14,16,18,20,25,30,35,40,50,60,80) {
  my $sum=0;
  my @timings = ();
  
  foreach my $i (1..N) {
    #\time --format="%E" ./main.out --step 1000 --height 1000 --width 1000 --thread 16
    my $r=`\\ssh mic1 "TIMEFORMAT=%R && time ./main.mic.out $SIZE $STEP $p" 2>&1`;
    $sum=$sum + $r;
    $r =~ s/^\s+|\s+$//g;
    push @timings, $r;
    
    #print $r." ";
  }
  my @sorted = sort @timings;
  my $avg = $sum/N;
  print "[$p, $avg, " . join(", ", @sorted) . "],\n";
}
print "]\n";
