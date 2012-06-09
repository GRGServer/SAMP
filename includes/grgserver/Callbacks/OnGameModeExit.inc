/**
 * <summary>
 *	This callback gets called once the gamemode ends.
 * </summary>
 *
 * <remarks>
 *	In this callback players and vehicles are forced to get saved.
 *	Every NPC gets kicked so no more NPCs are connected at the end of the gamemode.
 *	The MySQL connection gets disconnected if this callback gets called!
 * </remarks>
 */

public OnGameModeExit()
{
	print("* Unloading Gamemode...");
	PlayerLoop(playerID)
	{
		StopAudioStreamForPlayer(playerID);
		if (IsPlayerNPC(playerID))
		{
			Kick(playerID);
		}
	}
	print("* Saving vehicles...");
	Count1(vehicleID, MAX_VEHICLES)
	{
		SaveVehicle(vehicleID, 0);// TODO: Get interior of the vehicle?
	}
	print("* Disconnecting from MySQL server...");
	mysql_close();
	print("* Gamemode will now end");
	return true;
}