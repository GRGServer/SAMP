PCMD:setjob[MAPPER](playerID, params[], StringID:609("Link the current vehicle to a job"))
{
	if (!IsPlayerInAnyVehicle(playerID))
	{
		return COMMAND_NOT_IN_VEHICLE;
	}
	ShowDialog:SetVehicleJob(playerID);
	return COMMAND_OK;
}