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

CMD:alias(playerID, params[], 515)
{
	new name[32];
	new command[256];
	if (sscanf(params, "ss", name, command))
	{
		if (sscanf(params, "s", name))
		{
			CmdUsageMsg(playerID, "alias", "Name", "[Command]");
			SendClientMessageEx(playerID, COLOR_INFO, 516);
			return COMMAND_USAGE;
		}
		MySQLQuery("DELETE FROM `cmdaliases` WHERE `userId` = '%d' AND `name` = '%s'", PVar:playerID[USERID], MySQLEscapeString(name));
		if (mysql_affected_rows())
		{
			SendClientMessageEx(playerID, COLOR_INFO, 518, name);
			return COMMAND_OK;
		}
		SendClientMessageEx(playerID, COLOR_ERROR, 519, name);
		return COMMAND_ERROR;
	}
	MySQLQuery("REPLACE INTO `cmdaliases` (`userId`, `name`, `command`) VALUES('%d', '%s', '%s')", PVar:playerID[USERID], MySQLEscapeString(name), MySQLEscapeString(command));
	SendClientMessageEx(playerID, COLOR_INFO, 517, name);
	return COMMAND_OK;
}