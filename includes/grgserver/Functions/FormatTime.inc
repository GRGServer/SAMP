FormatTime(seconds)
{
	new days = seconds / 60 / 60 / 24;
	seconds -= days * 60 * 60 * 24;
	new hours = seconds / 60 / 60;
	seconds -= hours * 60 * 60;
	new minutes = seconds / 60;
	seconds -= minutes * 60;
	FormatNew:string[20]("%02d:%02d:%02d", hours, minutes, seconds);
	if (days)
	{
		Format:string("%dd, %s", days, string);
	}
	return string;
}