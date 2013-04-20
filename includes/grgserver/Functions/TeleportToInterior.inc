TeleportToInterior(playerID, interiorID)
{
	new result;
	if (interiorID > 0 && interiorID < sizeof(interiors))
	{
		SetPlayerPosEx(playerID, interiors[interiorID][INTERIOR_POS][0], interiors[interiorID][INTERIOR_POS][1], interiors[interiorID][INTERIOR_POS][2]);
		SetPlayerFacingAngle(playerID, interiors[interiorID][INTERIOR_ANGLE]);
		SetPlayerInterior(playerID, interiors[interiorID][INTERIOR_ID]);
		SetCameraBehindPlayer(playerID);
		PVar:playerID[CURRENTINTERIOR] = interiorID;
		result = true;
	}
	return result;
}