public OnPlayerPickUpPickup(playerid, pickupid)
{
	KillTimer(PVar:playerid[PICKUPTIMEOUT]);
	PVar:playerid[PICKUPTIMEOUT] = SetTimerEx("Timer_PickupTimeout", TIMER_PICKUPTIMEOUT, false, "i", playerid);
	if (PVar:playerid[LASTPICKUP] != pickupid)
	{
		PVar:playerid[LASTPICKUP] = pickupid;
		SendClientMessage(playerid, COLOR_INFO, LanguageString(playerid, "Press ~k~~CONVERSATION_YES~ to use this pickup"));
	}
}