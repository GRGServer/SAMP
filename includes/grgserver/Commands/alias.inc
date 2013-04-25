/**
 * <summary>
 *	Create or remove an user command alias.
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player which executed the command.
 * </param>
 *
 * <param name="params">
 *	<title>The passed parameters</title>
 *	<item name="Name">The name for the alias</item>
 *	<item name="Command">The command which should be aliased (Omit to remove the alias)</item>
 * </param>
 *
 * <remarks>
 *	An already existing alias will be replaced with the new alias (If the command parameter was not omitted).
 * </remarks>
 */

CMD:alias(playerID, params[], StringID:515("Create or remove a command alias"))
{
	new name[32];
	new command[256];
	if (sscanf(params, "s[32]s[256]", name, command))
	{
		if (sscanf(params, "s[32]", name))
		{
			CmdUsageMsg(playerID, "alias", "Name", "Command");
			SendClientMessageEx(playerID, COLOR_INFO, StringID:540("Command is the command without the slash ( / )!"));
			SendClientMessageEx(playerID, COLOR_INFO, StringID:541("Example usage: %s"), "/alias inf spawnvehicle infernus");
			SendClientMessageEx(playerID, COLOR_INFO, StringID:516("Use /alias <name> to remove an alias."));
			return COMMAND_USAGE;
		}
		MySQLQuery("DELETE FROM `cmdaliases` WHERE `userId` = '%d' AND `name` = '%s'", PVar:playerID[USERID], MySQLEscapeString(name));
		if (mysql_affected_rows())
		{
			SendClientMessageEx(playerID, COLOR_INFO, StringID:518("The alias /%s has been removed"), name);
			return COMMAND_OK;
		}
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:519("Alias /%s not found!"), name);
		return COMMAND_ERROR;
	}
	MySQLQuery("REPLACE INTO `cmdaliases` (`userId`, `name`, `command`) VALUES('%d', '%s', '%s')", PVar:playerID[USERID], MySQLEscapeString(name), MySQLEscapeString(command));
	SendClientMessageEx(playerID, COLOR_INFO, StringID:517("The alias /%s has been created"), name);
	return COMMAND_OK;
}