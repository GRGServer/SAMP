Timer:StableCheck()
{
	new File:file = fopen(FILE_STABLEREVISION, io_write);
	fwrite(file, val2str(COMPILER_SVN_REVISION));
	fclose(file);
	print("Gamemode is still running after 10 minutes -> Marked as stable");
}