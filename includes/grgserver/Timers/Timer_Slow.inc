/**
 * <summary>
 *	<title>This timer executes the following tasks every 5 seconds:</title>
 *	<item>Trigger OnServerTimeChange if the hour or minute changes</item>
 *	<item>Check for update notification file and notify players with the ServerAdmin permission</item>
 * </summary>
 */

Timer:Slow()
{
	new hour;
	new minute;
	gettime(hour, minute);
	if (hour != oldHour)
	{
		OnServerTimeChange(hour, minute, TIMECHANGE_HOUR);
		oldHour = hour;
	}
	if (minute != oldMinute)
	{
		OnServerTimeChange(hour, minute, TIMECHANGE_MINUTE);
		oldMinute = minute;
	}
	//mysql_ping();
	if (fexist(FILE_UPDATENOTIFICATION))
	{
		new string[256];
		new File:file = fopen(FILE_UPDATENOTIFICATION, io_read);
		fread(file, string);// Skip "------------------------------------------------------------------------"
		fread(file, string);// Read "rXXX | user | yyyy-mm-dd hh:ii:ss +xxxx (ddd, dd mmm yyyy) | x line(s)"
		new revisionString[10];
		new committerName[100];
		new commitDate[50];
		new lineCount[20];
		sscanf(string, "p<|>s[10]s[100]s[50]s[20]", revisionString, committerName, commitDate, lineCount);
		new revision = Str2Val(revisionString);
		if (revision > COMPILER_SVN_REVISION)
		{
			printf("Detected update to revision %d", revision);
			fread(file, string);// Skip ""
			LoggedInPlayers(playerID)
			{
				if (permissions[playerID][PERMISSION_SERVERADMIN])
				{
					SendClientMessageEx(playerID, COLOR_SYSTEM, "127", revision);
					SendClientMessageEx(playerID, COLOR_SYSTEM, "128", committerName);
					SendClientMessage(playerID, COLOR_SYSTEM, "*** SVN Changelog:");
				}
			}
			while (fread(file, string))
			{
				RemoveNewLine(string);
				if (strlen(string) && strcmp(string, "------------------------------------------------------------------------"))
				{
					Format:string("> %s", string);
					LoggedInPlayers(playerID)
					{
						if (permissions[playerID][PERMISSION_SERVERADMIN])
						{
							SendClientMessage(playerID, COLOR_SYSTEM, string);
						}
					}
				}
			}
		}
		fclose(file);
		fremove(FILE_UPDATENOTIFICATION);
	}
	LoggedInPlayers(playerID)
	{
		UpdatePlayerNeeds(playerID);
	}
}