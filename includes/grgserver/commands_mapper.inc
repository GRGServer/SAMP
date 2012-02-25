PCMD:addbuilding[MAPPER](playerid, params[])
{
	new Float:price;
	if (sscanf(params, "f", price))
	{
		CmdUsageMsg(playerid, "addbuilding", "Preis");
		return COMMAND_USAGE;
	}
	SetPVarFloat(playerid, "AddBuilding_Price", price);
	ShowDialog(playerid, DIALOG_ADDBUILDING_TYPE);
	return COMMAND_OK;
}

PCMD:addpickup[MAPPER](playerid, params[])
{
	new type[256];
	new string[256];
	new Float:posX;
	new Float:posY;
	new Float:posZ;
	if (sscanf(params, "s", type))
	{
		CmdUsageMsg(playerid, "addpickup", "GASSTATION");
		return COMMAND_USAGE;
	}
	Format:type("%s", strtoupper(type));
	if (!strcmp(type, "GASSTATION", true))
	{
		GetPlayerPos(playerid, posX, posY, posZ);
		new id = AddPickup(-1, type, posX, posY, posZ, true);
		if (id > 0)
		{
			Format:string("Das Pickup %s wurde unter der ID %d gespeichert", type, id);
			SendClientMessage(playerid, COLOR_INFO, string);
			return COMMAND_OK;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_ERROR, "Ung�ltiger Typ!");
	}
	return COMMAND_ERROR;
}

PCMD:saveveh[MAPPER](playerid, params[])
{
	new price;
	if (sscanf(params, "d", price))
	{
		CmdUsageMsg(playerid, "saveveh", "Preis");
		return COMMAND_USAGE;
	}
	if (price >= 0)
	{
		if (IsPlayerInAnyVehicle(playerid))
		{
			new string[256];
			new Float:posX;
			new Float:posY;
			new Float:posZ;
			new Float:angle;
			new vehicleID = GetPlayerVehicleID(playerid);
			new modelID = GetVehicleModel(vehicleID);
			GetVehiclePos(vehicleID, posX, posY, posZ);
			GetVehicleZAngle(vehicleID, angle);
			MySQLQuery("INSERT INTO `savedvehicles` (`PosX`, `PosY`, `PosZ`, `Angle`, `Interior`, `ModelID`, `Price`, `CurrentFuel`) VALUES('%f', '%f', '%f', '%f', '%d', '%d', '%d', '%f')", posX, posY, posZ, angle, GetPlayerInterior(playerid), modelID, price, vehicleModels[modelID - 400][VEHICLEMODEL_MAXFUEL]);
			Format:string("Fahrzeug wurde unter der ID %d gespeichert", mysql_insert_id());
			SendClientMessage(playerid, COLOR_INFO, string);
			return COMMAND_OK;
		}
		else
		{
			return COMMAND_NOT_IN_VEHICLE;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_ERROR, "Der Preis darf nicht negativ sein!");
	}
	return COMMAND_ERROR;
}

PCMD:setexit[MAPPER](playerid, params[])
{
	new buildingID;
	if (sscanf(params, "d", buildingID))
	{
		buildingID = GetPVarInt(playerid, "LastAddedBuilding");
	}
	if (buildingID)
	{
		if (strval(GetMySQLValue("buildings", "ID", "ID", val2str(buildingID))))
		{
			new string[256];
			new Float:posX;
			new Float:posY;
			new Float:posZ;
			GetPlayerPos(playerid, posX, posY, posZ);
			MySQLQuery("UPDATE `buildings` SET `ExitPosX` = '%f', `ExitPosY` = '%f', `ExitPosZ` = '%f' WHERE `ID` = '%d'", posX, posY, posZ, buildingID);
			Format:string("Die Ausgangsposition f�r das Geb�ude %s (ID: %d) wurde gespeichert", GetMySQLValue("buildings", "Name", "ID", val2str(buildingID)), buildingID);
			SendClientMessage(playerid, COLOR_INFO, string);
			return COMMAND_OK;
		}
		else
		{
			SendClientMessage(playerid, COLOR_ERROR, "Ung�ltige ID!");
			return COMMAND_ERROR;
		}
	}
	else
	{
		CmdUsageMsg(playerid, "setexit", "[BuildingID]");
		return COMMAND_USAGE;
	}
}

PCMD:veh[MAPPER](playerid, params[])
{
	new vehicleName[256];
	new modelID;
	new color1;
	new color2;
	if (sscanf(params, "ddd", modelID, color1, color2))
	{
		if (!sscanf(params, "d", modelID))
		{
			color1 = random(126);
			color2 = random(126);
		}
		else
		{
			if (sscanf(params, "sdd", vehicleName, color1, color2))
			{
				if (!sscanf(params, "s", vehicleName))
				{
					color1 = random(126);
					color2 = random(126);
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
		if (color1 >= 0 && color1 <= 126 && color2 >= 0 && color2 <= 126)
		{
			new Float:posX;
			new Float:posY;
			new Float:posZ;
			GetPlayerPos(playerid, posX, posY, posZ);
			new vehicleID = CreateVehicle(modelID, posX, posY, posZ, 0.0, color1, color2, -1);
			vehicles[vehicleID][VEHICLE_CURRENTFUEL] = vehicleModels[GetVehicleModel(vehicleID) - 400][VEHICLEMODEL_MAXFUEL];
			LinkVehicleToInterior(vehicleID, GetPlayerInterior(playerid));
			SetVehicleVirtualWorld(vehicleID, GetPlayerVirtualWorld(playerid));
			PutPlayerInVehicle(playerid, vehicleID, 0);
			printf("%s spawned a vehicle (ModelID: %d)", GetPlayerNameEx(playerid), modelID);
			SendClientMessage(playerid, COLOR_INFO, "Das Fahrzeug wurde gespawnt");
			return COMMAND_OK;
		}
		else
		{
			SendClientMessage(playerid, COLOR_ERROR, "Die Farbe muss zwischen 0 und 126 sein!");
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