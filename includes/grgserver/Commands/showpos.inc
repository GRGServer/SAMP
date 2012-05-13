PCMD:showpos[ADMIN](playerID, params[], 412)
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