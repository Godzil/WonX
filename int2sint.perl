#!PATH_TO_PERL

while (<STDIN>) {
	s/([\s;\}\/])uint(\s)/$1unsigned int$2/g;
	s/^uint(\s)/unsigned int$1/g;

	s/([\s;\}\/\(\)])long(\s+)int([\s\)\+\-\*\/])/$1_WONX_LONG_$2_WONX_INT_$3/g;
	s/([\s;\}\/\(\)])short(\s+)int([\s\)\+\-\*\/])/$1_WONX_SHORT_$2_WONX_INT_$3/g;
	s/^long(\s+)int([\s\)\+\-\*\/])/_WONX_LONG_$1_WONX_INT_$2/g;
	s/^short(\s+)int([\s\)\+\-\*\/])/_WONX_SHORT_$1_WONX_INT_$2/g;

	s/([\s;\}\/\(\)])int([\s\)\+\-\*\/])/$1_WONX_SHORT_ _WONX_INT_$2/g;
	s/^int([\s\)\+\-\*\/])/_WONX_SHORT_ _WONX_INT_$1/g;

	s/_WONX_LONG_/long/g;
	s/_WONX_SHORT_/short/g;
	s/_WONX_INT_/int/g;
	print $_;
}

exit (0);
