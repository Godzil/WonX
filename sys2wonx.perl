#!PATH_TO_PERL

while (<STDIN>) {
	s/^(\s*\#\s*include\s*)[\<\"]sys\/(.+\.h)[\>\"]/$1\"wonx\/$2\"/i;
	print $_;
}

exit (0);
