#!/usr/bin/perl

use FileHandle;

while (<STDIN>) {
	if (/output to serial port : /) {
		($string) = /output to serial port : \"(.*)\"\n/;
		$string =~ s/\\n/\n/;
		$string =~ s/\\r/\n/;
		$string =~ s/\\t/\t/;
		$string =~ s/\\s/ /;
		print "$string";
		STDOUT->autoflush();
	}
}

# End of program
