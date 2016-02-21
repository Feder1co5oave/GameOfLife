#!/bin/perl -w
use constant N => 5;
my $SIZE = 4096;
my $STEP = 1000;
my @json = ();

print "[\n";
foreach my $p (10,20,40,60,80,100,120,140,160,200,240) {
  my $sum=0;
  my @timings = ();
  
  print STDERR "$p: ";
  foreach my $i (1..N) {
    my $r=`\\ssh mic1 "TIMEFORMAT=%R && time ./main.out $SIZE $STEP $p" 2>&1`;
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
