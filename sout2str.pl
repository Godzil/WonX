#!/usr/local/bin/perl

use FileHandle;

while (<STDIN>) {
	if (/output to serial port : /) {
		($string) = /output to serial port : \"(.*)\"\n$/;
		$string =~ s/\\n/\n/g;
		$string =~ s/\\r/\n/g;
		$string =~ s/\\t/\t/g;
		$string =~ s/\\\"/\"/g;
		$string =~ s/\\\'/\'/g;
		$string =~ s/\\\\/\\/g;
		$string =~ s/\\s/ /g;
		print "$string";
		STDOUT->autoflush();
	}
}

# End of program
