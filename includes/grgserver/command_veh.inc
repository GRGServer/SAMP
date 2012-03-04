PCMD:veh[MAPPER](playerid, params[], "Fahrzeug spawnen")
{
	new vehicleName[20];
	new modelID;
	new color1;
	new color2;
	if (sscanf(params, "ddd", modelID, color1, color2))
	{
		if (!sscanf(params, "d", modelID))
		{
			color1 = random(127);
			color2 = random(127);
		}
		else
		{
			if (sscanf(params, "sdd", vehicleName, color1, color2))
			{
				if (!sscanf(params, "s", vehicleName))
				{
					color1 = random(127);
					color2 = random(127);
				}
				else
				{
					CmdUsageMsg(playerid, "veh", "ModelID/Name", "[Color1]", "[Color2]");
					return COMMAND_USAGE;
				}
			}
			modelID = strval(GetMySQLValue("vehiclemodels", "ModelID", "Name", str_replace("*", "%%", vehicleName), "LIKE"));
		}
	}
	if (modelID >= 400 && modelID <= 611)
	{
		if (color1 >= 0 && color1 <= 127 && color2 >= 0 && color2 <= 127)
		{
			new Float:posX;
			new Float:posY;
			new Float:posZ;
			GetPlayerPos(playerid, posX, posY, posZ);
			new vehicleID = CreateVehicleEx(modelID, posX, posY, posZ, 0.0, color1, color2, -1);
			LinkVehicleToInterior(vehicleID, GetPlayerInterior(playerid));
			SetVehicleVirtualWorld(vehicleID, GetPlayerVirtualWorld(playerid));
			PutPlayerInVehicle(playerid, vehicleID, 0);
			printf("%s spawned a vehicle (ModelID: %d)", GetPlayerNameEx(playerid), modelID);
			SendClientMessage(playerid, COLOR_INFO, "Das Fahrzeug wurde gespawnt");
			return COMMAND_OK;
		}
		else
		{
			SendClientMessage(playerid, COLOR_ERROR, "Die Farbe muss zwischen 0 und 127 sein!");
		}
	}
	else
	{
		if (strlen(vehicleName))
		{
			SendClientMessage(playerid, COLOR_ERROR, "Das Fahrzeug wurde nicht gefunden!");
		}
		else
		{
			SendClientMessage(playerid, COLOR_ERROR, "Die ModelID muss zwischen 400 und 611 sein!");
		}
	}
	return COMMAND_ERROR;
}