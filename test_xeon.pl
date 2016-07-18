#!/bin/perl -w

if ($#ARGV + 1 < 4) {
    print "Usage: test.pl <executable> <size> <iterations> <samples> [<csv thread list>]\n";
    exit;
}

my $EXE = $ARGV[0];
my $SIZE = $ARGV[1];
my $STEP = $ARGV[2];
my $N = $ARGV[3];
my @THREADS = (1,2,4,6,8,10,12,14,16);
if ($#ARGV + 1 == 5) {
	@THREADS = split /,/, $ARGV[4];
}
my @json = ();

foreach my $p (@THREADS) {
  my $sum=0;
  my @timings = ();
  
  print STDERR "$p: ";
  foreach my $i (1..$N) {
    my $r=`\\time --format="%e" ./$EXE -w $SIZE -h $SIZE -s $STEP -t $p 2>&1`;
    $sum=$sum + $r;
    $r =~ s/^\s+|\s+$//g;
    push @timings, $r;
    
    print STDERR $r." ";
  }
  print STDERR "\n";
  my @sorted = sort {$a <=> $b} @timings;
  my $avg = $sum/$N;
  push @json, "\t[$p, $avg, " . join(", ", @sorted) . "]";
}
print "[\n" . join(",\n", @json) . "\n]";
