ExecuteCommand(playerID, command[], parameters[], isAlias)
{
	FormatNew:functionName[MAX_FUNCTION_NAME]("cmd_%s", command);
	new returnCode = COMMAND_NOT_FOUND;
	if (funcidx(functionName) != -1)
	{
		if (StrNotNull(parameters))
		{
			returnCode = CallLocalFunction(functionName, "ds", playerID, parameters);
		}
		else
		{
			returnCode = CallLocalFunction(functionName, "ds", playerID, "\1");
		}
	}
	return OnPlayerCommandPerformed(playerID, command, parameters, returnCode, isAlias);
}