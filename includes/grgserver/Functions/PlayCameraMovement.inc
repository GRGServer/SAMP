PlayCameraMovement(playerID, movementID)
{
	MySQLQuery("SELECT * FROM `cameramovements` WHERE `ID` = '%d'", movementID);
	mysql_store_result();
	new Float:startMoveX = floatstr(GetMySQLField("StartMoveX"));
	new Float:startMoveY = floatstr(GetMySQLField("StartMoveY"));
	new Float:startMoveZ = floatstr(GetMySQLField("StartMoveZ"));
	new Float:startLookX = floatstr(GetMySQLField("StartLookX"));
	new Float:startLookY = floatstr(GetMySQLField("StartLookY"));
	new Float:startLookZ = floatstr(GetMySQLField("StartLookZ"));
	new waitStart = strval(GetMySQLField("WaitStart"));
	mysql_free_result();
	SetPlayerCameraPos(playerID, startMoveX, startMoveY, startMoveZ);
	SetPlayerCameraLookAt(playerID, startLookX, startLookY, startLookZ);
	TogglePlayerControllable(playerID, false);
	SetTimerEx("Timer_PlayCameraMovement", waitStart, false, "dd", playerID, movementID);
}