OnServerTimeChange(hour, minute, changeType)
{
	switch (changeType)
	{
		case TIMECHANGE_HOUR:
		{
			SetWorldTime(hour);
			gasPrice = float(GASSTATION_MINPRICE + random(GASSTATION_MAXDIFFERENCE)) / 100;
			printf("Updated gas price to $%s", FormatMoney(gasPrice));
		}
		case TIMECHANGE_MINUTE:
		{
			FormatNew:string[16]("%02d:%02d", hour, minute);
			TextDrawSetString(textDrawClock, string);
			Format:string("worldtime %s", string);
			SendRconCommand(string);
		}
	}
}