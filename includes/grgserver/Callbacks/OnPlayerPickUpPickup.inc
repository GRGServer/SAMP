public OnPlayerPickUpPickup(playerid, pickupid)
{
	KillTimer(PVar:playerid[PICKUPTIMEOUT]);
	PVar:playerid[PICKUPTIMEOUT] = SetTimerEx("Timer_PickupTimeout", TIMER_PICKUPTIMEOUT, false, "i", playerid);
	if (PVar:playerid[LASTPICKUP] != pickupid)
	{
		PVar:playerid[LASTPICKUP] = pickupid;
		PickupEvent(playerid, pickupid, PICKUPEVENT_PICKUP);
		return true;
	}
	return false;
}