#!/usr/local/bin/perl

while ($_ = shift(@ARGV)) {
	if ($_ eq "-f"   ) { last; }
	if ($_ eq "-file") { last; }
	$filters = "$filters | $_";
}

while ($filename = shift(@ARGV)) {
	$command = "cat $filename$filters > $filename.tmp";
	print "$command\n";
	system($command);
	$command = "mv $filename.tmp $filename";
	print "$command\n";
	system($command);
}
