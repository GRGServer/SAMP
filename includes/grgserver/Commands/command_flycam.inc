PCMD:flycam[MAPPER](playerID, params, 271)
{
	if (PVar:playerID[FLYCAM])
	{
		KillTimer(PVar:playerID[FLYCAM]);
		SetPlayerVirtualWorld(playerID, playerID);
		PVar:playerID[FLYCAM] = 0;
		SendClientMessageEx(playerID, COLOR_INFO, 273);
	}
	else
	{
		GetPlayerCameraPos(playerID, PVar:playerID[FLYCAM_POSX], PVar:playerID[FLYCAM_POSY], PVar:playerID[FLYCAM_POSZ]);
		PVar:playerID[FLYCAM] = SetTimerEx("Timer_FlyCam", 50, true, "d", playerID);
		SendClientMessageEx(playerID, COLOR_INFO, 272);
		SendClientMessage(playerID, COLOR_INFO, "X: ~k~~GO_LEFT~, ~k~~GO_RIGHT~");
		SendClientMessage(playerID, COLOR_INFO, "Y: ~k~~GO_FORWARD~, ~k~~GO_BACK~");
		SendClientMessage(playerID, COLOR_INFO, "Z: ~k~~PED_JUMPING~, ~k~~PED_SPRINT~");
	}
	return COMMAND_OK;
}