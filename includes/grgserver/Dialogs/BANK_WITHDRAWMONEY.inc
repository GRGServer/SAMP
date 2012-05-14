ShowDialog:BANK_WITHDRAWMONEY(playerID)
{
	CreateDialog(playerID, "BANK_WITHDRAWMONEY", DIALOG_STYLE_INPUT, LanguageString(playerID, 207), LanguageString(playerID, 213), "OK", LanguageString(playerID, 165));
}

DialogResponse:BANK_WITHDRAWMONEY(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (!strlen(inputText))
		{
			SendClientMessageEx(playerID, COLOR_ERROR, 19);
			ShowDialog:BANK_WITHDRAWMONEY(playerID);
		}
		else
		{
			new Float:money = floatstr(inputText);
			if(money > PVar:playerID[BANKMONEY])
			{
				SendClientMessageEx(playerID, COLOR_ERROR, 25);
				ShowDialog:BANK_WITHDRAWMONEY(playerID);
			}
			else
			{
				SetPlayerMoney(playerID, MONEY_BANK, floatsub(PVar:playerID[BANKMONEY], money));
				SetPlayerMoney(playerID, MONEY_CASH, floatadd(PVar:playerID[MONEY], money));
				SendClientMessageEx(playerID, COLOR_INFO, 26, money);
				ShowDialog:BANK_HASACCOUNT(playerID);
			}
		}
	}
	else
	{
		ShowDialog:BANK_HASACCOUNT(playerID);
	}
}