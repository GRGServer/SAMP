PCMD:dettachobject[ADMIN](playerID, params[], 394)
{
	new slot;
	if (sscanf(params, "d", slot))
	{
		CmdUsageMsg(playerID, "dettachobject", "slot[0-9]");
		return COMMAND_USAGE;
	}
	if (slot < 0 || slot > VEHICLE_MAXATTACHEDOBJECTS - 1)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 389);
		return COMMAND_ERROR;
	}
	if (attachedObjects[playerID][slot])
	{
		DestroyDynamicObject(attachedObjects[playerID][slot]);
		attachedObjects[playerID][slot] = 0;
	}
	SendClientMessageEx(playerID, COLOR_INFO, 391);
	return COMMAND_OK;
}