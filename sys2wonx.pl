#!/usr/bin/perl

while ($FILENAME = shift(@ARGV)) {
	open (RFILE, "< $FILENAME");
	open (WFILE, "> $FILENAME.tmp");
	while (<RFILE>) {
		s/^(\s*\#\s*include\s*)[\<\"]sys\/(.+\.h)[\>\"]/$1\"wonx_include\/$2\"/i;
		print WFILE $_;
	}
	close (RFILE);
	close (WFILE);

	system("mv $FILENAME.tmp $FILENAME");
}
