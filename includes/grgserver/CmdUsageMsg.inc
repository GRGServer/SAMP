CmdUsageMsg(playerID, command[], ...)
{
	new value[256];
	new parameters;
	parameters = numargs();
	FormatNew:string[256]("Verwendung: /%s", command);
	for (new index = 2; index < parameters; index++)
	{
		GetStringArg(index, value);
		Format:string("%s %s", string, value);
	}
	SendClientMessage(playerID, COLOR_USAGE, string);
}