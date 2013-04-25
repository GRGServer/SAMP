ShowDialog:UpgradeVehicle(playerID)
{
	new options[1024];
	AddLine(options, LanguageString(playerID, StringID:395("Front headlights")));
	AddLine(options, LanguageString(playerID, StringID:375("Neon lights")));
	CreateDialog(playerID, "UpgradeVehicle", DIALOG_STYLE_LIST, LanguageString(playerID, StringID:374("Upgrade your vehicle")), options, LanguageString(playerID, StringID:177("Next")), LanguageString(playerID, StringID:165("Cancel")));
}

DialogResponse:UpgradeVehicle(playerID, response, listItem, inputText[])
{
	if (!strcmp(inputText, LanguageString(playerID, StringID:395("Front headlights"))))// Front headlights
	{
		PVar:playerID[UPGRADEVEHICLE_LIGHTTYPE] = 1;
		ShowDialog:UpgradeVehicle_Light(playerID);
	}
	if (!strcmp(inputText, LanguageString(playerID, StringID:375("Neon lights"))))// Neon lights
	{
		PVar:playerID[UPGRADEVEHICLE_LIGHTTYPE] = 2;
		ShowDialog:UpgradeVehicle_Light(playerID);
	}
}