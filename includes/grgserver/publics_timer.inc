forward timer_fast();
public timer_fast()
{
	for (new playerID = 0; playerID < MAX_PLAYERS; playerID++)
	{
		if (IsPlayerConnected(playerID) && !IsPlayerNPC(playerID))
		{
			if (IsPlayerInAnyVehicle(playerID))
			{
				new Float:velocityX;
				new Float:velocityY;
				new Float:velocityZ;
				new string[256];
				GetVehicleVelocity(GetPlayerVehicleID(playerID), velocityX, velocityY, velocityZ);
				format(string, sizeof(string), "%d Km/h", floatround(floatsqroot(floatabs(floatpower(velocityX + velocityY + velocityZ, 2))) * 100 * 1.61));
				TextDrawSetString(textDrawSpeedo[playerID], string);
				TextDrawShowForPlayer(playerID, textDrawSpeedo[playerID]);
			}
			else
			{
				TextDrawHideForPlayer(playerID, textDrawSpeedo[playerID]);
			}
		}
	}
}

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
