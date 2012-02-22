public OnPlayerPickUpPickup(playerid, pickupid)
{
	switch (pickups[pickupid][PICKUP_TYPE])
	{
		case PICKUPTYPE_BANK:
		{
			TeleportToBuilding(playerid, strval(GetMySQLValue("buildings", "ID", "PickupID", val2str(pickups[pickupid][PICKUP_ID]))));
		}
		case PICKUPTYPE_GASSTATION:
		{
			new vehicleID = GetPlayerVehicleID(playerid);
			new Float:maximum = floatsub(vehicleModels[GetVehicleModel(vehicleID) - 400][VEHICLEMODEL_MAXFUEL], vehicles[vehicleID][VEHICLE_CURRENTFUEL]);
			if (maximum > 0)
			{
				ShowDialog(playerid, DIALOG_REFUEL, FormatMoney(maximum));
			}
			else
			{
				SendClientMessage(playerid, COLOR_ERROR, "Der Tank ist bereits voll!");
			}
		}
		case PICKUPTYPE_HOTEL:
		{
			// Hotel
			new ownerUserID = strval(GetMySQLValue("buildings", "OwnerUserID", "PickupID", val2str(pickups[pickupid][PICKUP_ID])));
			if (ownerUserID)
			{
				if (ownerUserID == GetPVarInt(playerid, "UserID"))
				{
					SetPVarInt(playerid, "DialogBuildingID", strval(GetMySQLValue("buildings", "ID", "PickupID", val2str(pickups[pickupid][PICKUP_ID]))));
					ShowDialog(playerid, DIALOG_HOTELOPTIONS);
				}
				else
				{
					ShowDialog(playerid, DIALOG_HOTELOPTIONS_NOTOWNER);
				}
			}
			else
			{
				ShowDialog(playerid, DIALOG_HOTEL);
			}
		}
		case PICKUPTYPE_HOUSE:
		{
			new ownerUserID = strval(GetMySQLValue("buildings", "OwnerUserID", "PickupID", val2str(pickups[pickupid][PICKUP_ID])));
			if (ownerUserID)
			{
				if (ownerUserID == GetPVarInt(playerid, "UserID"))
				{
					SetPVarInt(playerid, "DialogBuildingID", strval(GetMySQLValue("buildings", "ID", "PickupID", val2str(pickups[pickupid][PICKUP_ID]))));
					ShowDialog(playerid, DIALOG_HOUSEOPTIONS);
				}
				else
				{
					new string[256];
					format(string, sizeof(string), "Dieses Haus wurde bereits von %s gekauft.", GetMySQLValue("users", "Username", "UserID", val2str(ownerUserID)));
					SendClientMessage(playerid, COLOR_ERROR, string);
				}
			}
			else
			{
				new string[256];
				new Float:price = floatstr(GetMySQLValue("buildings", "Price", "PickupID", val2str(pickups[pickupid][PICKUP_ID])));
				if (price <= GetPVarFloat(playerid, "Money"))
				{
					SetPVarInt(playerid, "DialogBuildingID", strval(GetMySQLValue("buildings", "ID", "PickupID", val2str(pickups[pickupid][PICKUP_ID]))));
					ShowDialog(playerid, DIALOG_BUYHOUSE, FormatMoney(price));
				}
				else
				{
					format(string, sizeof(string), "Du hast nicht genügend Geld, um dieses Haus zu kaufen! Du benötigst mindestens $%s.", FormatMoney(price));
					SendClientMessage(playerid, COLOR_ERROR, string);
				}
			}
		}
		default:
		{
			printf("Invalid pickup type: %d", pickups[pickupid][PICKUP_TYPE]);
		}
	}
	return true;
}