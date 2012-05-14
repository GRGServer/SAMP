ShowDialog:BANK_DEPOSITMONEY(playerID)
{
	CreateDialog(playerID, "BANK_DEPOSITMONEY", DIALOG_STYLE_INPUT, LanguageString(playerID, 208), LanguageString(playerID, 212), "OK", LanguageString(playerID, 165));
}

DialogResponse:BANK_DEPOSITMONEY(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (!strlen(inputText))
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 19);
			ShowDialog:BANK_DEPOSITMONEY(playerID);
		}
		else
		{
			new Float:money = floatstr(inputText);
			if(money > PVar:playerID[MONEY])
			{
				SendClientMessageEx(playerID, COLOR_ERROR, 14);
				ShowDialog:BANK_DEPOSITMONEY(playerID);
			}
			else
			{
				SetPlayerMoney(playerID, MONEY_BANK, floatadd(PVar:playerID[BANKMONEY], money));
				SetPlayerMoney(playerID, MONEY_CASH, floatsub(PVar:playerID[MONEY], money));
				SendClientMessageEx(playerID, COLOR_INFO, 21, money);
				ShowDialog:BANK_HASACCOUNT(playerID);
			}
		}
	}
	else
	{
		ShowDialog:BANK_HASACCOUNT(playerID);
	}
}