PickupEvent:LINK(playerID, pickupID, eventType)
{
	switch (eventType)
	{
		case PICKUPEVENT_PICKUP:
		{
			MySQLQuery("SELECT * FROM `tplinks` WHERE `pickupId` = '%d'", pickups[pickupID][PICKUP_ID]);
			mysql_store_result();
			PVar:playerID[TELEPORT_LINKID] = strval(GetMySQLField("id"));
			new Float:posX = floatstr(GetMySQLField("posX"));
			new Float:posY = floatstr(GetMySQLField("posY"));
			new Float:posZ = floatstr(GetMySQLField("posZ"));
			new Float:angle = floatstr(GetMySQLField("angle"));
			new interior = strval(GetMySQLField("interior"));
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
				MySQLQuery("INSERT INTO `tplinks` (`pickupId`) VALUES('%d')", pickups[pickupID][PICKUP_ID]);
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