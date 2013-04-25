PCMD:showpos[ADMIN](playerID, params[], StringID:412("Show/Hide your current position"))
{
	if (PVar:playerID[SHOWPOS])
	{
		PVar:playerID[SHOWPOS] = false;
		PlayerTextDrawHide(playerID, PTextDraw:playerID[SHOWPOS]);
	}
	else
	{
		PVar:playerID[SHOWPOS] = true;
		PlayerTextDrawShow(playerID, PTextDraw:playerID[SHOWPOS]);
	}
	return COMMAND_OK;
}