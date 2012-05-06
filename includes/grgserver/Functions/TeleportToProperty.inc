TeleportToProperty(playerID, propertyID)
{
	new interiorID = strval(GetMySQLValue("properties", "InteriorID", "ID", val2str(propertyID)));
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