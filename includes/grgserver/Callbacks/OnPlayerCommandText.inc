public OnPlayerCommandText(playerid, cmdtext[])
{
	new cmdText[256];
	new command[MAX_FUNCTION_NAME];
	new parameters[256];
	strcat(cmdText, cmdtext);
	strdel(cmdText, 0, 1);// Remove the slash before the command
	if (sscanf(cmdText, "ss", command, parameters))
	{
		sscanf(cmdText, "s", command);
	}
	return ExecuteCommand(playerid, command, parameters, false);
}