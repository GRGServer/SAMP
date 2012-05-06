OnServerTimeChange(hour, minute, changeType)
{
	switch (changeType)
	{
		case TIMECHANGE_HOUR:
		{
			gasPrice = float(GASSTATION_MINPRICE + random(GASSTATION_MAXDIFFERENCE)) / 100;
			printf("Updated gas price to $%s", FormatMoney(gasPrice));
		}
		case TIMECHANGE_MINUTE:
		{
			FormatNew:hourString[3]("%02d", hour);
			FormatNew:minuteString[3]("%02d", minute);
			if (hour < 10)
			{
				hourString[0] = '0';
			}
			if (minute < 10)
			{
				minuteString[0] = '0';
			}
			FormatNew:string[16]("%2d:%2d", hour, minute);
			TextDrawSetString(textDrawClock, string);
			Format:string("worldtime %s", string);
			SendRconCommand(string);
		}
	}
}