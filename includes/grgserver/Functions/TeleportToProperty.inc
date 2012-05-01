TeleportToProperty(playerID, buildingID)
{
	new interiorID = strval(GetMySQLValue("properties", "InteriorID", "ID", val2str(buildingID)));
	if (interiorID)
	{
		if (TeleportToInterior(playerID, interiorID))
		{
			PVar:playerID[CURRENTPROPERTYID] = buildingID;
			SetPlayerVirtualWorld(playerID, buildingID);
			return true;
		}
	}
	return false;
}