forward timer_slow();
public timer_slow()
{
	new hour;
	new minute;
	new second;
	gettime(hour, minute, second);
	SetWorldTime(hour);
	mysql_ping();
}