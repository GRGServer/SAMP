public OnPlayerSelectDynamicObject(playerid, objectid, modelid, Float:x, Float:y, Float:z)
{
	PVar:playerid[OBJEDITOR_CURRENTOBJECTID] = objectid;
	GetDynamicObjectPos(objectid, PVar:playerid[OBJEDITOR_LASTPOSX], PVar:playerid[OBJEDITOR_LASTPOSY], PVar:playerid[OBJEDITOR_LASTPOSZ]);
	GetDynamicObjectRot(objectid, PVar:playerid[OBJEDITOR_LASTROTX], PVar:playerid[OBJEDITOR_LASTROTY], PVar:playerid[OBJEDITOR_LASTROTZ]);
	EditDynamicObject(playerid, objectid);
	SendClientMessageEx(playerid, COLOR_INFO, 204);
}