ShowDialog:Bank_DepositMoney(playerID)
{
	CreateDialog(playerID, "Bank_DepositMoney", DIALOG_STYLE_INPUT, LanguageString(playerID, StringID:208("")), LanguageString(playerID, StringID:212("")), "OK", LanguageString(playerID, StringID:165("")));
}

DialogResponse:Bank_DepositMoney(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (!strlen(inputText))
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:19(""));
			ShowDialog:Bank_DepositMoney(playerID);
		}
		else
		{
			new Float:money = floatstr(inputText);
			if(money > PVar:playerID[MONEY])
			{
				SendClientMessageEx(playerID, COLOR_ERROR, StringID:14(""));
				ShowDialog:Bank_DepositMoney(playerID);
			}
			else
			{
				SetPlayerMoney(playerID, MONEY_BANK, money, true);
				SetPlayerMoney(playerID, MONEY_CASH, -money, true);
				SendClientMessageEx(playerID, COLOR_INFO, StringID:21(""), money);
				ShowDialog:Bank_HasAccount(playerID);
			}
		}
	}
	else
	{
		ShowDialog:Bank_HasAccount(playerID);
	}
}