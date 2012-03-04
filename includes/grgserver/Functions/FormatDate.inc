FormatDate(sqlDateString[], showTime = true)
{
	new string[STRINGLENGTH_DATETIME + 2];
	new time[10];
	new day;
	new month;
	new year;
	sscanf(sqlDateString, "ss", string, time);
	sscanf(string, "p-ddd", year, month, day);
	Format:string("%02d.%02d.%d", day, month, year);
	if (showTime)
	{
		Format:string("%s - %s", string, time);
	}
	return string;
}