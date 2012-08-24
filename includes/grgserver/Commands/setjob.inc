PCMD:setjob[MAPPER](playerID, params[], 609)
{
	if (!IsPlayerInAnyVehicle(playerID))
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
	ShowDialog:SetVehicleJob(playerID);
	return COMMAND_OK;
}