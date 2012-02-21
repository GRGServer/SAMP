#include <a_samp>

public OnFilterScriptInit()
{
	print("RCON Proxy Filterscript loaded");
	return true;
}

public OnFilterScriptExit()
{
	print("RCON Proxy Filterscript unloaded");
	return true;
}

public OnRconCommand(cmd[])
{
	new pos;
	new functionName[32];
	while (cmd[pos] > ' ')
	{
		functionName[pos] = tolower(cmd[pos]);
		pos++;
	}
	format(functionName, sizeof(functionName), "rcmd_%s", functionName);
	while (cmd[pos] == ' ')
	{
		pos++;
	}
	if (!cmd[pos])
	{
		return CallRemoteFunction(functionName, "s", "\1");
	}
	return CallRemoteFunction(functionName, "s", cmd[pos]);
}