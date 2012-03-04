Teleport(playerID, Float:posX, Float:posY, Float:posZ, Float:angle, interior, virtualWorld)
{
	if (TeleportTo(playerID, posX, posY, posZ, angle, interior, virtualWorld))
	{
		return true;
	}
	else
	{
		SendClientMessage(playerID, COLOR_ERROR, "Beim Teleportieren ist ein Fehler aufgetreten! Bitte versuche es erneut.");
		return false;
	}
}

TeleportTo(playerID, Float:posX, Float:posY, Float:posZ, Float:angle, interior, virtualWorld)
{
	switch (GetPlayerState(playerID))
	{
		case PLAYER_STATE_ONFOOT:
		{
			SetPlayerPos(playerID, posX, posY, posZ);
			SetPlayerFacingAngle(playerID, angle);
			SetPlayerInterior(playerID, interior);
			SetPlayerVirtualWorld(playerID, virtualWorld);
			return true;
		}
		case PLAYER_STATE_DRIVER, PLAYER_STATE_PASSENGER:
		{
			new vehicleID = GetPlayerVehicleID(playerID);
			SetVehiclePos(vehicleID, posX, posY, posZ);
			LinkVehicleToInterior(vehicleID, interior);
			SetVehicleVirtualWorld(vehicleID, virtualWorld);
			return true;
		}
	}
	return false;
}

TeleportToBuilding(playerID, buildingID)
{
	new interiorID = strval(GetMySQLValue("buildings", "InteriorID", "ID", val2str(buildingID)));
	if (interiorID)
	{
		if (TeleportToInterior(playerID, interiorID))
		{
			SetPVar:playerID[CURRENTBUILDINGID](buildingID);
			SetPlayerVirtualWorld(playerID, buildingID);
			return true;
		}
	}
	return false;
}

TeleportToInterior(playerID, interiorID)
{
	new result;
	MySQLQuery("SELECT * FROM `interiors` WHERE `ID` = '%d'", interiorID);
	mysql_store_result();
	if (strval(GetMySQLField("ID")))
	{
		SetPlayerPos(playerID, floatstr(GetMySQLField("PosX")), floatstr(GetMySQLField("PosY")), floatstr(GetMySQLField("PosZ")));
		SetPlayerFacingAngle(playerID, floatstr(GetMySQLField("Angle")));
		SetPlayerInterior(playerID, strval(GetMySQLField("Interior")));
		result = true;
	}
	mysql_free_result();
	return result;
}