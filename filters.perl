#!PATH_TO_PERL

while ($_ = shift(@ARGV)) {
	if ($_ eq "-f"   ) { last; }
	if ($_ eq "-file") { last; }
	$filters = "$filters | $_";
}

while ($filename = shift(@ARGV)) {
	$command = "cat $filename$filters > $filename.tmp";
	print STDERR "$command\n";
	$ret = system($command);
	if ($ret != 0) { die "Command not found. Install perl scripts.\n"; }
	$command = "mv $filename.tmp $filename";
	print STDERR "$command\n";
	$ret = system($command);
	if ($ret != 0) { die "Command not found.\n"; }
}

exit (0);
