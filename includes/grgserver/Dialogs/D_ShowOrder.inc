ShowDialog:ShowOrder(playerID)
{
	FormatNew:title[20](LanguageString(playerID, StringID:553("Trucker missions")));
	new options[1024];
	AddLine(options, LanguageString(playerID, StringID:546("Cannabis plantations transportation")));// Item 1
	AddLine(options, LanguageString(playerID, StringID:547("Cole transport")));// Item 2
	AddLine(options, LanguageString(playerID, StringID:548("Tank Transport")));// Item 3
	AddLine(options, LanguageString(playerID, StringID:549("Attach your trailer and drive to the checkpoint")));// Item 4
	CreateDialog(playerID, "ShowOrder", DIALOG_STYLE_LIST, title, options, LanguageString(playerID, StringID:164("Accept")), LanguageString(playerID, StringID:165("Cancel")));
}

DialogResponse:ShowOrder(playerID, response, listItem, inputText[])
{
	if (response)
	{
		switch (listItem)
		{
			case 0:
			{
				SendClientMessageEx(playerID, COLOR_INFO, StringID:550("grain transport"));
				SetPlayerCheckpointEx(playerID, CHECKPOINT_TRAILER1, -1636.9059, 1298.2018, 7.0326, 10.0);
			}
			case 1:
			{
				SendClientMessageEx(playerID, COLOR_INFO, StringID:550("grain transport"));
				SetPlayerCheckpointEx(playerID, CHECKPOINT_TRAILER2, -1633.2474, 1294.5585, 7.0391, 10.0);
			}
			case 2:
			{
				SendClientMessageEx(playerID, COLOR_INFO, StringID:550("grain transport"));
				SetPlayerCheckpointEx(playerID, CHECKPOINT_TRAILER3, -1640.5248, 1301.9790, 7.0277, 10.0);
			}
			case 3: 
			{
				SendClientMessageEx(playerID, COLOR_INFO, StringID:550("grain transport"));
				SetPlayerCheckpointEx(playerID, CHECKPOINT_TRAILER4, -1645.7511, 1303.5062, 7.0295, 10.0);
			}
		}
	}
}