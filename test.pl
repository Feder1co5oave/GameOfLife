#!/bin/perl -w
use constant N => 20;
my $SIZE = 1000;
my $STEP = 1000;

my $sum=0;
my $max=0;
my $min=-1;
foreach my $i (0..N) {
  #\time --format="%E" ./main.out --step 1000 --height 1000 --width 1000 --thread 16
  my $r=`\\time --format="%e" ./main.out --step $STEP --height $SIZE --width $SIZE --thread 16 2>&1`;
  $sum=$sum + $r;
  $r =~ s/^\s+|\s+$//g;
  if ($r > $max) {
      $max=$r;
  }

  if ($r < $min || $min==-1){
      $min=$r;
  }

  print $r."\n";
}
my $avg = $sum/N;
print "min:$min - max:$max - sum:$avg\n";
