#!/bin/perl -w

if ($#ARGV + 1 != 5) {
    print "Usage: test.pl <executable> <size> <iterations> <samples> mic0|mic1\n";
    exit;
}

my $EXE = $ARGV[0];
my $SIZE = $ARGV[1];
my $STEP = $ARGV[2];
my $N = $ARGV[3];
my $HOST = $ARGV[4];
my @json = ();

print "[\n";
foreach my $p (10,20,40,60,80,100,120,140,160,200,240) {
  my $sum=0;
  my @timings = ();
  
  print STDERR "$p: ";
  foreach my $i (1..$N) {
    my $r=`\\ssh $HOST "TIMEFORMAT=%R && time ./$EXE $SIZE $STEP $p" 2>&1`;
    $sum=$sum + $r;
    $r =~ s/^\s+|\s+$//g;
    push @timings, $r;
    
    print STDERR $r." ";
  }
  print STDERR "\n";
  my @sorted = sort {$a <=> $b} @timings;
  my $avg = $sum/$N;
  push @json, "[$p, $avg, " . join(", ", @sorted) . "]";
}
print join(",\n", @json) . "\n]\n";
