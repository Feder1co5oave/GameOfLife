#!/bin/perl -w
use constant N => 5;
my $SIZE = 4096;
my $STEP = 1000;
my @json = ();

print "[\n";
foreach my $p (1,2,4,6,8,10,12,14,16,18,20,25,30) {
  my $sum=0;
  my @timings = ();
  
  print STDERR "$p: ";
  foreach my $i (1..N) {
    #\time --format="%E" ./main.out --step 1000 --height 1000 --width 1000 --thread 16
    my $r=`\\time --format="%e" ./main.out $SIZE $STEP $p 2>&1`;
    $sum=$sum + $r;
    $r =~ s/^\s+|\s+$//g;
    push @timings, $r;
    
    print STDERR $r." ";
  }
  print STDERR "\n";
  my @sorted = sort {$a <=> $b} @timings;
  my $avg = $sum/N;
  push @json, "[$p, $avg, " . join(", ", @sorted) . "]";
}
print join(",\n", @json) . "\n]\n";
