#!/bin/perl -w

if ($#ARGV + 1 != ) {
    print "Usage: test.pl <executable> <size> <iterations> <samples>\n";
    exit;
}

my $EXE = $ARGV[0];
my $SIZE = $ARGV[1];
my $STEP = $ARGV[2];
my $N = $ARGV[3];
my @json = ();

print "[\n";
foreach my $p (1,2,4,6,8,10,12,14,16) {
  my $sum=0;
  my @timings = ();
  
  print STDERR "$p: ";
  foreach my $i (1..$N) {
    my $r=`\\time --format="%e" ./main.out $SIZE $STEP $p 2>&1`;
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
