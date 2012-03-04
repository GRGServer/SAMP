PlayRadioStation(playerID, id)
{
	if (id)
	{
		SetPVar:playerID[RADIOON](true);
		SetPVar:playerID[LASTRADIOSTATION](id);
		FormatNew:string[100]("%s", GetMySQLValue("radiostations", "Name", "ID", val2str(id)));
		PlayAudioStreamForPlayer(playerID, GetMySQLValue("radiostations", "URL", "ID", val2str(id)));
		TextDrawSetString(textDrawRadioStation[playerID], string);
		TextDrawShowForPlayer(playerID, textDrawRadioStation[playerID]);
		Format:string("Du hörst jetzt %s", string);
		SendClientMessage(playerID, COLOR_INFO, string);
	}
	else
	{
		SendClientMessage(playerID, COLOR_ERROR, "Ungültiger Radiosender!");
	}
}