Timer:RandomCameraCutsFader(playerID)
{
	if (!PVar:playerID[PLAYRANDOMCAMERACUTS])
	{
		return false;
	}
	PlayRandomCameraCuts(playerID);// Remove this line if you use the line below
	// TODO: Not working perfect yet...
	//StartScreenFader(playerID, 0, 0, 0, 5, 0, FADE_RANDOMCAMERACUTS, 0);
	return true;
}