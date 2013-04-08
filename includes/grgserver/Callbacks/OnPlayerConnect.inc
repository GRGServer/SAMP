/**
 * <summary>
 *	This callback is called when a player connects to the server.
 * </summary>
 *
 * <param name="playerid">
 *	The ID of the player which connected.
 * </param>
 *
 * <remarks>
 *	<title>The following task are done in this callback:</title>
 *	<item>Reset all player variables</item>
 *	<item>Check if the player is banned (Kick if banned)</item>
 *	<item>If the player is a NPC: Check if the NPC connects from 127.0.0.1 (Ban the IP address if the NPC connects from another IP address)</item>
 *	<item>Check if the player is already registered (True: Show login dialog, false: Show register dialog)</item>
 *	<item>Send join message to all players and IRC channel</item>
 * </remarks>
 */

public OnPlayerConnect(playerid)
{
	ResetPlayerVariables(playerid);
	if (IsBanned(playerid, true))
	{
		Kick(playerid);
		return false;
	}
	if (IsPlayerNPC(playerid))
	{
		new ip[16];
		GetPlayerIp(playerid, ip, sizeof(ip));
		if (strcmp(ip, "127.0.0.1", true))
		{
			MySQLBan(INVALID_PLAYER_ID, playerid, "External NPC connection", true);
			return false;
		}
		SetSpawnInfo(playerid, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);// Always spawn NPCs in a not visible area (At position 0 x 0 x 0)
		return true;
	}
	printf("%s connected from %s", GetPlayerNameEx(playerid), GetPlayerCountryName(playerid));
	Count(index, sizeof(removedStandardObjects))
	{
		RemoveBuildingForPlayer(playerid, removedStandardObjects[index][STDOBJ_MODELID], removedStandardObjects[index][STDOBJ_POSX], removedStandardObjects[index][STDOBJ_POSY], removedStandardObjects[index][STDOBJ_POSZ], removedStandardObjects[index][STDOBJ_RADIUS]);
	}
	printf("* Textdraw loading....");
	TextDrawShowForPlayer(playerid, Komma);
    TextDrawShowForPlayer(playerid, Food[playerid]);
    TextDrawShowForPlayer(playerid, Drink[playerid]);
	TextDrawShowForPlayer(playerid, Pee[playerid]);
	printf("* Texdraw was loading");
	printf("* Timers PlayerConnect loading...");
	StartTimer:EAT("Timer_Eat", true);
	StartTimer:DRINK("Timer_Drink", true);
	StartTimer:PEE("Timer_Handrang", true);
	printf("* Timer was PlayerConnect loading");
	return true;
}