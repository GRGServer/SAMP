public OnPlayerSelectDynamicObject(playerid, objectid, modelid, Float:x, Float:y, Float:z)
{
	PVar:playerid[OBJEDITOR_CURRENTOBJECTID] = objectid;
	PVar:playerid[LASTOBJECT] = objectid;
	GetDynamicObjectPos(objectid, PVar:playerid[OBJEDITOR_LASTPOSX], PVar:playerid[OBJEDITOR_LASTPOSY], PVar:playerid[OBJEDITOR_LASTPOSZ]);
	GetDynamicObjectRot(objectid, PVar:playerid[OBJEDITOR_LASTROTX], PVar:playerid[OBJEDITOR_LASTROTY], PVar:playerid[OBJEDITOR_LASTROTZ]);
	EditDynamicObject(playerid, objectid);
	SendClientMessageEx(playerid, COLOR_INFO, StringID:204("Object %d (%s) from file '%s' selected"), dynamicObjects[objectid - 1][OBJECT_ID], objectModels[Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_MODEL_ID)], dynamicObjects[objectid - 1][OBJECT_FILENAME]);
	SendClientMessageEx(playerid, COLOR_INFO, StringID:18("You can now edit the object using the GUI, clone it (Key ~k~~SNEAK_ABOUT~) or remove it (Key ~k~~CONVERSATION_NO~)"));
}