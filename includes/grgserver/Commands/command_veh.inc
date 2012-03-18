PCMD:veh[MAPPER](playerid, params[], 122)
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
			SendClientMessageEx(playerid, COLOR_INFO, 62);
			return COMMAND_OK;
		}
		else
		{
			SendClientMessageEx(playerid, COLOR_ERROR, 63);
		}
	}
	else
	{
		if (strlen(vehicleName))
		{
			SendClientMessageEx(playerid, COLOR_ERROR, 64);
		}
		else
		{
			SendClientMessageEx(playerid, COLOR_ERROR, 65);
		}
	}
	return COMMAND_ERROR;
}