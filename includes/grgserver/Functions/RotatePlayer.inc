RotatePlayer(playerID, Float:rotation)
{
	new Float:angle;
	GetPlayerFacingAngle(playerID, angle);
	angle = floatsub(angle, rotation);
	if (angle < 0)
	{
		angle = floatsub(360, angle);
	}
	SetPlayerFacingAngle(playerID, angle);
}