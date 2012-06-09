TeleportToProperty(playerID, propertyID)
{
	new interiorID = strval(GetMySQLValue("properties", "interiorId", "id", val2str(propertyID)));
	if (interiorID)
	{
		if (TeleportToInterior(playerID, interiorID))
		{
			PVar:playerID[CURRENTPROPERTYID] = propertyID;
			SetPlayerVirtualWorld(playerID, propertyID);
			return true;
		}
	}
	return false;
}