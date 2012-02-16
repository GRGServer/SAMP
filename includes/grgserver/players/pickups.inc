public OnPlayerPickUpPickup(playerid,pickupid)
{
	switch (pickups[pickupid][pickups_type])
	{
		case PICKUPTYPE_HOUSE:
		{
			new ownerUserID = strval(GetMySQLValue("houses", "OwnerUserID", "PickupID", val2str(pickupid)));
			// if (ownerUserID)   Crashing Compiler
			// {
				// if (ownerUserID == GetPVarInt(playerid, "UserID"))
				// {
					ShowDialog(playerid, DIALOG_HOUSEOPTIONS);
				// }
				/* else
				{
					new string[256];
					format(string, sizeof(string), "Dieses Haus wurde bereits von %s gekauft.", GetMySQLValue("users", "Username", "UserID", val2str(ownerUserID)));
					SendClientMessage(playerid, COLOR_ERROR, string);
				}
			}
			else
			{
				new string[256];
				new Float:price = floatstr(GetMySQLValue("houses", "Price", "PickupID", val2str(pickupid)));
				if (price <= GetPVarFloat(playerid, "Money"))
				{
					ShowDialog(playerid, DIALOG_BUYHOUSE, FormatNumber(price, 2, '.', ','));
				}
				else
				{
					format(string, sizeof(string), "Du hast nicht genügend Geld, um dieses Haus zu kaufen! Du benötigst mindestens $%s.", FormatNumber(price, 2, '.', ','));
					SendClientMessage(playerid, COLOR_ERROR, string);
				}
			}*/
		}
		case PICKUPTYPE_BANK:
		{
			mysql_query("SELECT * FROM `interiors`");
			mysql_store_result();
			while (FetchMySQLRow())
			{
				new Float:PosX = floatstr(GetMySQLField("PosX"));
				new Float:PosY = floatstr(GetMySQLField("PosY"));
				new Float:PosZ = floatstr(GetMySQLField("PosZ"));
				new interior = strval(GetMySQLField("Interior"));
				SetPlayerPos(playerid,PosX,PosY,PosZ);
				SetPlayerInterior(playerid, interior);
			}
			mysql_query("SELECT * FROM `banks`");
			mysql_store_result();
			while (FetchMySQLRow())
			{
				new bankID = strval(GetMySQLField("ID"));
				SetPlayerVirtualWorld(playerid, bankID);
			}
		}
		case PICKUPTYPE_GASSTATION:
		{
			new vehicleID = GetPlayerVehicleID(playerid);
			new Float:maximum = floatsub(vehicleModels[GetVehicleModel(vehicleID) - 400][vehicleModels_maxFuel], vehicles[vehicleID][vehicles_currentFuel]);
			if (maximum > 0)
			{
				ShowDialog(playerid, DIALOG_REFUEL, FormatNumber(maximum, 2, 0, '.'));
			}
			else
			{
				SendClientMessage(playerid, COLOR_ERROR, "Der Tank ist bereits voll!");
			}
		}
	}
	return true;
}