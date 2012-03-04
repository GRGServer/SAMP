RCMD:showmysqlinfo(params[], "Show various information about the MySQL connection (i.e. number of occured warnings)")
{
	printf("Number of warnings: %d", mysql_warning_count());
	return true;
}