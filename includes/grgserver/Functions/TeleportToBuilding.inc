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