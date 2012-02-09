forward TachoTimer();
public TachoTimer()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerNPC(i) && IsPlayerInAnyVehicle(i))
		{
			new Float:distanz, Float:speed; 
			new Float:x1[MAX_PLAYERS]; 
			new Float:y1[MAX_PLAYERS]; 
			new Float:z1[MAX_PLAYERS];
			new Float:x2[MAX_PLAYERS];
			new Float:y2[MAX_PLAYERS];
			new Float:z2[MAX_PLAYERS];
			GetVehiclePos(GetPlayerVehicleID(i), x1[i], y1[i], z1[i]); 
			distanz = floatsqroot(floatpower(floatabs(floatsub(x1[i], x2[i])), 2)+floatpower(floatabs(floatsub(y1[i], y2[i])), 2)+floatpower(floatabs(floatsub(z1[i], z2[i])), 2)); 
			speed = (distanz / (TACHOTIMER/1000)) * 3.6; //Meter/Sekunde in Kilometer/Stunde
			new Tachostring[20]; // definiert den String
			format(Tachostring, sizeof(Tachostring), "Km/h: %d", floatround(speed)); 
			TextDrawSetString(Tacho[i], Tachostring); 
			GetVehiclePos(GetPlayerVehicleID(i), x2[i], y2[i], z2[i]);
			TextDrawShowForPlayer(i, Tacho[i]);
		}
		else
		{
			TextDrawHideForPlayer(i, Tacho[i]);
		}
	}
	return COMMAND_OK;
}

forward timer_slow();
public timer_slow()
{
	new hour;
	new minute;
	new second;
	gettime(hour, minute, second);
	SetWorldTime(hour);
	SetTimer("TachoTimer",TACHOTIMER,1);
	mysql_ping();
}