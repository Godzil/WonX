#!/usr/local/bin/perl

while (<STDIN>) {
	s/^(\s*\#\s*include\s*)[\<\"]sys\/(.+\.h)[\>\"]/$1\"wonx_include\/$2\"/i;
	print $_;
}
