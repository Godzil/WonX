#!/usr/bin/perl

while ($filename = shift(@ARGV)) {
	open(RFILE, "< $filename");
	open(WFILE, "> $filename.tmp");
	while (<RFILE>) {
		if (/Wonx/) {
			print $_;
			s/Wonx/WonX/g;
			print $_;
		}
		print WFILE $_;
	}
	close(RFILE);
	close(WFILE);
	system("mv $filename.tmp $filename");
}
