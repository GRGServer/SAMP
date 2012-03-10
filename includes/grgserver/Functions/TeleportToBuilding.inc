TeleportToBuilding(playerID, buildingID)
{
	new interiorID = strval(GetMySQLValue("buildings", "InteriorID", "ID", val2str(buildingID)));
	if (interiorID)
	{
		if (TeleportToInterior(playerID, interiorID))
		{
			PVar:playerID[CURRENTBUILDINGID] = buildingID;
			SetPlayerVirtualWorld(playerID, buildingID);
			return true;
		}
	}
	return false;
}