PCMD:flycam[MAPPER](playerID, params[], StringID:271("Fly trough San Andreas"))
{
	if (PVar:playerID[FLYCAM_DUMMYOBJECT])
	{
		if (IsStr(params, "goto"))
		{
			new Float:posX;
			new Float:posY;
			new Float:posZ;
			GetPlayerCameraPos(playerID, posX, posY, posZ);
			SetPlayerPos(playerID, posX, posY, posZ);
		}
		KillTimer(PVar:playerID[FLYCAM_TIMER]);
		DestroyDynamicObject(PVar:playerID[FLYCAM_DUMMYOBJECT]);
		SetCameraBehindPlayer(playerID);
		ClearAnimations(playerID);
		SendClientMessageEx(playerID, COLOR_INFO, StringID:273("Fly mode deactivated"));
		PVar:playerID[FLYCAM_DUMMYOBJECT] = 0;
	}
	else
	{
		new Float:posX;
		new Float:posY;
		new Float:posZ;
		ApplyAnimation(playerID, "CARRY", "crry_prtial", 1.0, 0, 0, 0, 1, 0);
		GetPlayerCameraPos(playerID, posX, posY, posZ);
		new objectID = CreateDynamicObject(19300, posX, posY, posZ, 0, 0, 0, -1, -1, playerID);
		Streamer_Update(playerID);
		PVar:playerID[FLYCAM_DUMMYOBJECT] = objectID;
		AttachCameraToDynamicObject(playerID, objectID);
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_EXTRA_ID, OBJECTTYPE_FLYCAMDUMMY);
		PVar:playerID[FLYCAM_TIMER] = SetTimerEx("Timer_FlyCam", TIMER_FLYCAM, true, "d", playerID);
		SendClientMessageEx(playerID, COLOR_INFO, StringID:272("Fly mode activated"));
		SendClientMessageEx(playerID, COLOR_INFO, StringID:428("Speed: ~k~~PED_JUMPING~, ~k~~SNEAK_ABOUT~"));
		SendClientMessageEx(playerID, COLOR_INFO, StringID:429("Up / Down: ~k~~PED_SPRINT~, ~k~~PED_DUCK~"));
		SendClientMessageEx(playerID, COLOR_INFO, StringID:430("Move camera: ~k~~GO_FORWARD~, ~k~~GO_BACK~, ~k~~GO_LEFT~, ~k~~GO_RIGHT~"));
	}
	return COMMAND_OK;
}