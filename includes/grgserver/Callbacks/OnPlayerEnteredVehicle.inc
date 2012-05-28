/**
 * <summary>
 *	This callback gets called every time a player entered a vehicle.
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player which entered the vehicle.
 * </param>
 *
 * <param name="vehicleID">
 *	The ID of the vehicle which was entered by the player.
 * </param>
 *
 * <param name="isPassenger">
 *	<item name="true">The player entered the vehicle as a passenger</item>
 *	<item name="false">The player entered the vehicle as the driver</item>
 * </param>
 *
 * <remarks>
 *	<title>Difference between OnPlayerEnterVehicle and OnPlayerEnteredVehicle:</title>
 *	<item name="OnPlayerEnterVehicle">The player is while entering the vehicle (Not already in the vehicle)</item>
 *	<item name="OnPlayerEnteredVehicle">The player is already in the vehicle</item>
 * </remarks>
 */

OnPlayerEnteredVehicle(playerID, vehicleID, isPassenger)
{
	if (IsPlayerNPC(playerID))
	{
		return true;
	}
	new modelID = GetVehicleModel(vehicleID);
	if (modelID == 420)
	{
		new npcPlayerID;
		MySQLQuery("SELECT * FROM `npcs` WHERE `VehicleID` = '%d'", VehicleProperty:vehicleID[SAVEID]);
		mysql_store_result();
		if (mysql_num_rows())
		{
			npcPlayerID = GetPlayerID(GetMySQLField("Name"));
		}
		mysql_free_result();
		if (npcPlayerID != INVALID_PLAYER_ID)
		{
			if (isPassenger)
			{
				SendNPCCommand(npcPlayerID, "start");
				return true;
			}
			else
			{
				RemovePlayerFromVehicle(playerID);
				return false;
			}
		}
	}
	if (!isPassenger && !GetVehicleEngineState(vehicleID))
	{
		SendClientMessageEx(playerID, COLOR_INFO, 424);
	}
	return true;
}