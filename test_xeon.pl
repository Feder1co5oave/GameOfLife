#!/bin/perl -w
use constant N => 15;
my $SIZE = 2000;
my $STEP = 1000;

print "[\n";
foreach my $p (6,8,10,12,14,16,18,20,25,30,35,40,50) {
  my $sum=0;
  my @timings = ();
  
  foreach my $i (1..N) {
    #\time --format="%E" ./main.out --step 1000 --height 1000 --width 1000 --thread 16
    my $r=`\\time --format="%e" ./main.out $SIZE $STEP $p 2>&1`;
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
