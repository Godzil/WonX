#!/usr/bin/perl

use FileHandle;

while (<STDIN>) {
	if (/output to serial port : /) {
		($string) = /output to serial port : (.*)/;
		$string =~ s/\\n/\n/;
		$string =~ s/\\r/\n/;
		$string =~ s/\\t/\t/;
		print "$string";
		STDOUT->autoflush();
	}
}

# End of program
