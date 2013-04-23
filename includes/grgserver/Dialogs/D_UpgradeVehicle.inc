ShowDialog:UpgradeVehicle(playerID)
{
	new options[1024];
	AddLine(options, LanguageString(playerID, StringID:395("")));
	AddLine(options, LanguageString(playerID, StringID:375("")));
	CreateDialog(playerID, "UpgradeVehicle", DIALOG_STYLE_LIST, LanguageString(playerID, StringID:374("")), options, LanguageString(playerID, StringID:177("")), LanguageString(playerID, StringID:165("")));
}

DialogResponse:UpgradeVehicle(playerID, response, listItem, inputText[])
{
	if (!strcmp(inputText, LanguageString(playerID, StringID:395(""))))// Front headlights
	{
		PVar:playerID[UPGRADEVEHICLE_LIGHTTYPE] = 1;
		ShowDialog:UpgradeVehicle_Light(playerID);
	}
	if (!strcmp(inputText, LanguageString(playerID, StringID:375(""))))// Neon lights
	{
		PVar:playerID[UPGRADEVEHICLE_LIGHTTYPE] = 2;
		ShowDialog:UpgradeVehicle_Light(playerID);
	}
}