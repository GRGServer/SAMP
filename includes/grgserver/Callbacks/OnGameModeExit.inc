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
	for (new vehicleID = 0; vehicleID < MAX_VEHICLES; vehicleID++)
	{
		SaveVehicle(vehicleID, 0);// TODO: Get interior of the vehicle?
	}
	print("* Disconnecting from MySQL server...");
	mysql_close();
	print("* Disconnecting from IRC server...");
	IRC_Quit(ircBot, "SAMP-Server IRC chat relay");
	print("* Gamemode will now end");
	return true;
}