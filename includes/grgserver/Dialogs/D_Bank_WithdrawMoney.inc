ShowDialog:Bank_WithdrawMoney(playerID)
{
	CreateDialog(playerID, "Bank_WithdrawMoney", DIALOG_STYLE_INPUT, LanguageString(playerID, "207"), LanguageString(playerID, "213"), "OK", LanguageString(playerID, "165"));
}

DialogResponse:Bank_WithdrawMoney(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (!strlen(inputText))
		{
			SendClientMessageEx(playerID, COLOR_ERROR, "19");
			ShowDialog:Bank_WithdrawMoney(playerID);
		}
		else
		{
			new Float:money = floatstr(inputText);
			new Float:bankMoney = GetBankMoney(playerID);
			if(money > bankMoney)
			{
				SendClientMessageEx(playerID, COLOR_ERROR, "25");
				ShowDialog:Bank_WithdrawMoney(playerID);
			}
			else
			{
				new Float:newMoney = floatadd(PVar:playerID[MONEY], money);
				if (newMoney > MAX_MONEY)
				{
					newMoney = MAX_MONEY;
					SendClientMessageEx(playerID, COLOR_ERROR, "492", MAX_MONEY);
				}
				money = floatsub(newMoney, PVar:playerID[MONEY]);
				SetPlayerMoney(playerID, MONEY_BANK, -money, true);
				SetPlayerMoney(playerID, MONEY_CASH, money, true);
				SendClientMessageEx(playerID, COLOR_INFO, "26", money);
				ShowDialog:Bank_HasAccount(playerID);
			}
		}
	}
	else
	{
		ShowDialog:Bank_HasAccount(playerID);
	}
}