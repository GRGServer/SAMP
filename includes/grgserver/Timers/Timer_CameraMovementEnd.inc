Timer:CameraMovementEnd(playerID, movementID)
{
	MySQLQuery("SELECT * FROM `cameramovements` WHERE `ID` = '%d'", movementID);
	mysql_store_result();
	new resetOnEnd = strval(GetMySQLField("ResetOnEnd"));
	new callOnEnd[32];
	strcat(callOnEnd, GetMySQLField("CallOnEnd"));
	mysql_free_result();
	if (resetOnEnd)
	{
		SetCameraBehindPlayer(playerID);
	}
	TogglePlayerControllable(playerID, true);
	if (strlen(callOnEnd))
	{
		if (callOnEnd[0] == '#')
		{
			strdel(callOnEnd, 0, 1);
			PlayCameraMovement(playerID, strval(callOnEnd));
		}
		else
		{
			CallLocalFunction(callOnEnd, "ii", playerID, movementID);
		}
	}
}