PCMD:selectbuilding[MAPPER](playerID, params[], 335)
{
	if (PVar:playerID[CURRENTBUILDINGID])
	{
		PVar:playerID[SELECTEDBUILDINGID] = PVar:playerID[CURRENTBUILDINGID];
		SendClientMessageEx(playerID, COLOR_INFO, 142, GetMySQLValue("buildings", "Name", "ID", val2str(PVar:playerID[CURRENTBUILDINGID])));
		return COMMAND_OK;
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 61);
		return COMMAND_ERROR;
	}
}