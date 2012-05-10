PickupEvent:LINK(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_PICKUP:
		{
			MySQLQuery("SELECT * FROM `tplinks` WHERE `PickupID` = '%d'", pickups[pickupID][PICKUP_ID]);
			mysql_store_result();
			PVar:playerID[TELEPORT_LINKID] = strval(GetMySQLField("ID"));
			new Float:posX = floatstr(GetMySQLField("PosX"));
			new Float:posY = floatstr(GetMySQLField("PosY"));
			new Float:posZ = floatstr(GetMySQLField("PosZ"));
			new Float:angle = floatstr(GetMySQLField("Angle"));
			new interior = strval(GetMySQLField("Interior"));
			mysql_free_result();
			if (PVar:playerID[TELEPORT_LINKID])
			{
				if (posX || posY || posZ)
				{
					Teleport(playerID, posX, posY, posZ, angle, interior, 0);
				}
			}
			else
			{
				MySQLQuery("INSERT INTO `tplinks` (`PickupID`) VALUES('%d')", pickups[pickupID][PICKUP_ID]);
				PVar:playerID[TELEPORT_LINKID] = mysql_insert_id();
			}
			if (permissions[playerID][PERMISSION_MAPPER])
			{
				SendClientMessageEx(playerID, COLOR_INFO, 136, PVar:playerID[TELEPORT_LINKID]);
			}
			return true;
		}
	}
	return false;
}

PickupModelID:LINK(pickupID)
{
	return 19197;
}