public OnPlayerPickUpPickup(playerid, pickupid)
{
	switch (pickups[pickupid][PICKUP_TYPE])
	{
		case PICKUPTYPE_HOTEL:
		{
			printf("Pickup %d is a hotel");
		}
		case PICKUPTYPE_HOUSE:
		{
			printf("Pickup %d is a house");
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
					ShowDialog(playerid, DIALOG_BUYHOUSE, FormatPrice(price));
				}
				else
				{
					format(string, sizeof(string), "Du hast nicht genügend Geld, um dieses Haus zu kaufen! Du benötigst mindestens $%s.", FormatPrice(price));
					SendClientMessage(playerid, COLOR_ERROR, string);
				}
			}
		}
		case PICKUPTYPE_BANK:
		{
			printf("Pickup %d is a bank");
			TeleportToBuilding(playerid, strval(GetMySQLValue("buildings", "ID", "PickupID", val2str(pickups[pickupid][PICKUP_ID]))));
		}
		case PICKUPTYPE_GASSTATION:
		{
			printf("Pickup %d is a gas station");
			new vehicleID = GetPlayerVehicleID(playerid);
			new Float:maximum = floatsub(vehicleModels[GetVehicleModel(vehicleID) - 400][VEHICLEMODEL_MAXFUEL], vehicles[vehicleID][VEHICLE_CURRENTFUEL]);
			if (maximum > 0)
			{
				ShowDialog(playerid, DIALOG_REFUEL, FormatPrice(maximum));
			}
			else
			{
				SendClientMessage(playerid, COLOR_ERROR, "Der Tank ist bereits voll!");
			}
		}
		default:
		{
			printf("Invalid pickup type: %d", pickups[pickupid][PICKUP_TYPE]);
		}
	}
	return true;
}