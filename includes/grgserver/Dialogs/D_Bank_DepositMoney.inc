ShowDialog:Bank_DepositMoney(playerID)
{
	CreateDialog(playerID, "Bank_DepositMoney", DIALOG_STYLE_INPUT, LanguageString(playerID, "208"), LanguageString(playerID, "212"), "OK", LanguageString(playerID, "165"));
}

DialogResponse:Bank_DepositMoney(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (!strlen(inputText))
		{
			SendClientMessageEx(playerID, COLOR_ERROR, "19");
			ShowDialog:Bank_DepositMoney(playerID);
		}
		else
		{
			new Float:money = floatstr(inputText);
			if(money > PVar:playerID[MONEY])
			{
				SendClientMessageEx(playerID, COLOR_ERROR, "14");
				ShowDialog:Bank_DepositMoney(playerID);
			}
			else
			{
				SetPlayerMoney(playerID, MONEY_BANK, money, true);
				SetPlayerMoney(playerID, MONEY_CASH, -money, true);
				SendClientMessageEx(playerID, COLOR_INFO, "21", money);
				ShowDialog:Bank_HasAccount(playerID);
			}
		}
	}
	else
	{
		ShowDialog:Bank_HasAccount(playerID);
	}
}