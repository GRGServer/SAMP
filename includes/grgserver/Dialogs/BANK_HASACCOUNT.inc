ShowDialog:BANK_HASACCOUNT(playerID)
{
	new options[1024];
	AddLine(options, LanguageString(playerID, 206));// Bank balance
	AddLine(options, LanguageString(playerID, 207));// Withdraw money
	AddLine(options, LanguageString(playerID, 208));// Deposit money
	AddLine(options, LanguageString(playerID, 209));// Cancel account
	CreateDialog(playerID, "BANK_HASACCOUNT", DIALOG_STYLE_LIST, "Bank", options, "OK", LanguageString(playerID, 165));
}

DialogResponse:BANK_HASACCOUNT(playerID, response, listItem, inputText[])
{
	if (response)
	{
		switch (listItem)
		{
			case 0:// Bank balance
			{
				SendClientMessageEx(playerID, COLOR_INFO, 23, PVar:playerID[BANKMONEY]);
				ShowDialog:BANK_HASACCOUNT(playerID);
			}
			case 1:// Withdraw money
			{
				ShowDialog:BANK_WITHDRAWMONEY(playerID);
			}
			case 2:// Deposit money
			{
				ShowDialog:BANK_DEPOSITMONEY(playerID);
			}
			case 3:// Cancel account
			{
				if (PVar:playerID[BANKMONEY] > 0)
				{
					SendClientMessageEx(playerID, COLOR_ERROR, 215);
					ShowDialog:BANK_HASACCOUNT(playerID);
				}
				else
				{
					ShowDialog:BANK_CANCELACCOUNT(playerID);
				}
			}
		}
	}
	else
	{
		LeaveProperty(playerID);
	}
}