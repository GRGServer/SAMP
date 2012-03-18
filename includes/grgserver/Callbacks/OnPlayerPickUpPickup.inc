public OnPlayerPickUpPickup(playerid, pickupid)
{
	KillTimer(PVar:playerid[PICKUPTIMEOUT]);
	PVar:playerid[PICKUPTIMEOUT] = SetTimerEx("Timer_PickupTimeout", TIMER_PICKUPTIMEOUT, false, "i", playerid);
	if (PVar:playerid[LASTPICKUP] != pickupid)
	{
		PVar:playerid[LASTPICKUP] = pickupid;
		SendClientMessageEx(playerid, COLOR_INFO, 7);
	}
}