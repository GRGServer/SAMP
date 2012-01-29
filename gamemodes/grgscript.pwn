#include <a_samp>
#include <grgserver/compiler>

main()
{
	// Log printing work around (Must be printed with *one* print() command to prevent time from displaying)
	new string[256];
	format(string, sizeof(string), "\n\n*** GRG Server Game Mode ***\n");
	format(string, sizeof(string), "%s\nSVN Revision %d\n", string, COMPILER_SVN_REVISION);
	format(string, sizeof(string), "%sCompile date: %s %s\n", string, COMPILER_DATE, COMPILER_TIME);
	format(string, sizeof(string), "%s\nCopyright 2012 GRG Server\n", string);
	print(string);
}