CMD:teststart(playerid, params[], 0)
{
	TeleportTo(playerid, 1.7414, 31.6997, 1199.6012, 177.4850, 1, playerid);
	SetPlayerCheckpointEx(playerid, CHECKPOINT_WALKTOSEAT);
	return COMMAND_OK;
}