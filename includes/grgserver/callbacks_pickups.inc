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
			new Float:posX;
			new Float:posY;
			new Float:posZ;
			new buildingID = strval(GetMySQLValue("buildings", "ID", "PickupID", val2str(pickups[pickupid][PICKUP_ID])));
			new ownerUserID = strval(GetMySQLValue("buildings", "OwnerUserID", "PickupID", val2str(pickups[pickupid][PICKUP_ID])));
			GetPlayerPos(playerid, posX, posY, posZ);
			SetPVarFloat(playerid, "Hotel_PreviousPosition_X", posX);
			SetPVarFloat(playerid, "Hotel_PreviousPosition_Y", posY);
			SetPVarFloat(playerid, "Hotel_PreviousPosition_Z", posZ);
			SetPlayerPos(playerid, HOTEL_RECEPTION_POSX, HOTEL_RECEPTION_POSY, HOTEL_RECEPTION_POSZ);
			SetPlayerFacingAngle(playerid, HOTEL_RECEPTION_ANGLE);
			SetPlayerInterior(playerid, HOTEL_RECEPTION_INTERIOR);
			SetPlayerVirtualWorld(playerid, buildingID);
			if (ownerUserID)
			{
				if (ownerUserID == GetUserID(playerid))
				{
					SetPVarInt(playerid, "DialogBuildingID", buildingID);
					ShowDialog(playerid, DIALOG_HOTEL_MAIN_OWNER);
				}
				else
				{
					ShowDialog(playerid, DIALOG_HOTEL_MAIN_BOUGHT);
				}
			}
			else
			{
				ShowDialog(playerid, DIALOG_HOTEL_MAIN_AVAILABLE);
			}
		}
		case PICKUPTYPE_HOUSE:
		{
			new ownerUserID = strval(GetMySQLValue("buildings", "OwnerUserID", "PickupID", val2str(pickups[pickupid][PICKUP_ID])));
			if (ownerUserID)
			{
				if (ownerUserID == GetUserID(playerid))
				{
					SetPVarInt(playerid, "DialogBuildingID", strval(GetMySQLValue("buildings", "ID", "PickupID", val2str(pickups[pickupid][PICKUP_ID]))));
					ShowDialog(playerid, DIALOG_HOUSEOPTIONS);
				}
				else
				{
					new string[256];
					Format:string("Dieses Haus wurde bereits von %s gekauft.", GetMySQLValue("users", "Username", "UserID", val2str(ownerUserID)));
					SendClientMessage(playerid, COLOR_ERROR, string);
				}
			}
			else
			{
				new string[256];
				new Float:price = floatstr(GetMySQLValue("buildings", "Price", "PickupID", val2str(pickups[pickupid][PICKUP_ID])));
				if (price <= GetPlayerMoneyEx(playerid))
				{
					SetPVarInt(playerid, "DialogBuildingID", strval(GetMySQLValue("buildings", "ID", "PickupID", val2str(pickups[pickupid][PICKUP_ID]))));
					ShowDialog(playerid, DIALOG_BUYHOUSE, FormatMoney(price));
				}
				else
				{
					Format:string("Du hast nicht gen�gend Geld, um dieses Haus zu kaufen! Du ben�tigst mindestens $%s.", FormatMoney(price));
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