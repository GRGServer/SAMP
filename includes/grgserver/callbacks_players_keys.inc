public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (IsKeyPressed(KEY_YES))
	{
		Count(pickupID, MAX_PICKUPS)
		{
			if (GetPlayerDistanceFromPoint(playerid, pickups[pickupID][PICKUP_POSX], pickups[pickupID][PICKUP_POSY], pickups[pickupID][PICKUP_POSZ]) <= 1)
			{
				switch (pickups[pickupID][PICKUP_TYPE])
				{
					case PICKUPTYPE_BANK:
					{
						TeleportToBuilding(playerid, strval(GetMySQLValue("buildings", "ID", "PickupID", val2str(pickups[pickupID][PICKUP_ID]))));
					}
					case PICKUPTYPE_GASSTATION:
					{
						new vehicleID = GetPlayerVehicleID(playerid);
						new Float:maximum = floatsub(vehicleModels[GetVehicleModel(vehicleID) - 400][VEHICLEMODEL_MAXFUEL], vehicles[vehicleID][VEHICLE_CURRENTFUEL]);
						if (maximum > 0)
						{
							SetPVarFloat(playerid, "CurrentGasPrice", gasPrice);
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
						new buildingID = strval(GetMySQLValue("buildings", "ID", "PickupID", val2str(pickups[pickupID][PICKUP_ID])));
						new ownerUserID = strval(GetMySQLValue("buildings", "OwnerUserID", "PickupID", val2str(pickups[pickupID][PICKUP_ID])));
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
						new ownerUserID = strval(GetMySQLValue("buildings", "OwnerUserID", "PickupID", val2str(pickups[pickupID][PICKUP_ID])));
						if (ownerUserID)
						{
							if (ownerUserID == GetUserID(playerid))
							{
								SetPVarInt(playerid, "DialogBuildingID", strval(GetMySQLValue("buildings", "ID", "PickupID", val2str(pickups[pickupID][PICKUP_ID]))));
								ShowDialog(playerid, DIALOG_HOUSEOPTIONS);
							}
							else
							{
								FormatNew:string[MAX_PLAYER_NAME + 40]("Dieses Haus wurde bereits von %s gekauft.", GetMySQLValue("users", "Username", "UserID", val2str(ownerUserID)));
								SendClientMessage(playerid, COLOR_ERROR, string);
							}
						}
						else
						{
							new Float:price = floatstr(GetMySQLValue("buildings", "Price", "PickupID", val2str(pickups[pickupID][PICKUP_ID])));
							if (price <= GetPlayerMoneyEx(playerid))
							{
								SetPVarInt(playerid, "DialogBuildingID", strval(GetMySQLValue("buildings", "ID", "PickupID", val2str(pickups[pickupID][PICKUP_ID]))));
								ShowDialog(playerid, DIALOG_BUYHOUSE, FormatMoney(price));
							}
							else
							{
								FormatNew:string[100]("Du hast nicht genügend Geld, um dieses Haus zu kaufen! Du benötigst mindestens $%s.", FormatMoney(price));
								SendClientMessage(playerid, COLOR_ERROR, string);
							}
						}
					}
					case PICKUPTYPE_INBANK:
					{
						if (GetJobID(playerid) == JOB_BANK)
						{
							ShowDialog(playerid, DIALOG_INBANK_OPTIONS);
						}
						else
						{
							ShowDialog(playerid, DIALOG_INBANK_JOB);
						}
					}
					case PICKUPTYPE_POLICE:
					{
						if (GetJobID(playerid) == JOB_POLICE)
						{
							ShowDialog(playerid, DIALOG_POLICE_OPTIONS);
						}
						else
						{
							ShowDialog(playerid, DIALOG_POLICE_JOB);
						}
					}
					case PICKUPTYPE_TRUCKER:
					{
						if (GetJobID(playerid) == JOB_TRUCKER)
						{
							ShowDialog(playerid, DIALOG_TRUCKER_OPTIONS);
						}
						else
						{
							ShowDialog(playerid, DIALOG_TRUCKER_JOB);
						}
					}
					case PICKUPTYPE_VEHICLEDEALER:
					{
						if (GetJobID(playerid) == JOB_VEHICLEDEALER)
						{
							ShowDialog(playerid, DIALOG_VEHICLEDEALER_OPTIONS);
						}
						else
						{
							ShowDialog(playerid, DIALOG_VEHICLEDEALER_JOB);
						}
					}
					default:
					{
						printf("Invalid pickup type: %d", pickups[pickupID][PICKUP_TYPE]);
					}
				}
				return true;
			}
		}
	}
	return false;
}