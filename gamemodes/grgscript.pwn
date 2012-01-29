#include <a_samp>
#include <grgserver/compiler>

main()
{
	print("\n*** GRG Server Game Mode ***\n");
	printf("SVN Revision %d", COMPILER_SVN_REVISION);
	printf("Compile date: %s %s", COMPILER_DATE, COMPILER_TIME);
	print("\nCopyright 2012 GRG Server\n");
}