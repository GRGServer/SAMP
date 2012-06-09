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
		return true;
	}
	printf("%s connected from %s", GetPlayerNameEx(playerid), GetPlayerCountryName(playerid));
	MySQLQuery("SELECT * FROM `users` WHERE `username` = '%s'", MySQLEscapeString(GetPlayerNameEx(playerid)));
	mysql_store_result();
	if (strval(GetMySQLField("id")))
	{
		PVar:playerid[LANGUAGE] = strval(GetMySQLField("language"));
		TogglePlayerSpectating(playerid, true);
		PVar:playerid[REGISTERED] = true;
	}
	else
	{
		new countryCode[2];
		strcat(countryCode, GetPlayerCountryCode(playerid));
		if (strlen(countryCode) && (!strcmp(countryCode, "AT", true) || !strcmp(countryCode, "CH", true) || !strcmp(countryCode, "DE", true)))
		{
			PVar:playerid[LANGUAGE] = LANGUAGE_GERMAN;
		}
		else
		{
			PVar:playerid[LANGUAGE] = LANGUAGE_ENGLISH;
		}
		PVar:playerid[REGISTERED] = false;
		PlaySound(playerid, musicSoundIDs[random(sizeof(musicSoundIDs))]);
	}
	mysql_free_result();
	ShowDialog:PreviewInfo(playerid);
	SendDeathMessage(INVALID_PLAYER_ID, playerid, 200);
	SendClientMessageEx(playerid, COLOR_SYSTEM, 138);
	SendClientMessageEx(playerid, COLOR_SYSTEM, 5, COMPILER_SVN_REVISION);
	PlayerLoop(playerID)
	{
		if (!IsPlayerNPC(playerID) && playerID != playerid)
		{
			SendClientMessageEx(playerID, COLOR_JOINLEAVE, 3, playerid);
		}
	}
	FormatNew:string[MAX_PLAYER_NAME + 30]("%s has joined the server", GetPlayerNameEx(playerid));
	IRC_Say(ircBot, ircChannel, string);
	ReloadTextDraws(playerid);
	return true;
}