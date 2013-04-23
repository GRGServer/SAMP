CMD:playcam(playerID, params[], StringID:0(""))
{
	new Float:startPosX;
	new Float:startPosY;
	new Float:startPosZ;
	new Float:startLookX;
	new Float:startLookY;
	new Float:startLookZ;
	new Float:endPosX;
	new Float:endPosY;
	new Float:endPosZ;
	new Float:endLookX;
	new Float:endLookY;
	new Float:endLookZ;
	new time;
	new cutType;
	if (sscanf(params, "ffffffffffffdd", startPosX, startPosY, startPosZ, startLookX, startLookY, startLookZ, endPosX, endPosY, endPosZ, endLookX, endLookY, endLookZ, time, cutType))
	{
		CmdUsageMsg(playerID, "playcam", "startPosX startPosY startPosZ startLookX startLookY startLookZ endPosX endPosY endPosZ endLookX endLookY endLookZ time cutType");
		return COMMAND_USAGE;
	}
	InterpolateCameraPos(playerID, startPosX, startPosY, startPosZ, endPosX, endPosY, endPosZ, time, cutType);
	InterpolateCameraLookAt(playerID, startLookX, startLookY, startLookZ, endLookX, endLookY, endLookZ, time, cutType);
	return COMMAND_OK;
}