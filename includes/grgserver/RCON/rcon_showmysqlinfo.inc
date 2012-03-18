RCMD:showmysqlinfo(params[], 157)
{
	printf("Number of warnings: %d", mysql_warning_count());
	return true;
}