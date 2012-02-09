forward timer_fast();
public timer_fast()// FIXME
{
	for(new playerID = 0; playerID < MAX_PLAYERS; playerID++)
	{
		if (IsPlayerConnected(playerID))
		{
			if (!IsPlayerNPC(playerID) && IsPlayerInAnyVehicle(playerID))
			{
				// Requires fix (Will *not* work!)
				/*new Float:vehiclePosX;
				new Float:vehiclePosY;
				new Float:vehiclePosZ;
				GetVehiclePos(GetPlayerVehicleID(playerID), vehiclePosX, vehiclePosY, vehiclePosZ);
				new Float:distance = floatsqroot(floatpower(floatabs(floatsub(vehiclePosX, x2[i])), 2)+floatpower(floatabs(floatsub(vehiclePosY, y2[i])), 2)+floatpower(floatabs(floatsub(vehiclePosZ, z2[i])), 2));
				speed = (distanz / (TACHOTIMER/1000)) * 3.6;
				new Tachostring[20];
				format(Tachostring, sizeof(Tachostring), "Km/h: %d", floatround(speed));
				TextDrawSetString(Tacho[i], Tachostring);
				GetVehiclePos(GetPlayerVehicleID(i), x2[i], y2[i], z2[i]);
				TextDrawShowForPlayer(i, Tacho[i]);*/
			}
			else
			{
				//TextDrawHideForPlayer(playerID, Tacho[i]);
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
