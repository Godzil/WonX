#!/usr/bin/perl

use FileHandle;

$file = @ARGV[0];

open(FILE, "$file");
FILE->autoflush();

while (<FILE>) {
	print "$_";
	STDOUT->autoflush();
	FILE->autoflush();
}

# End of program
