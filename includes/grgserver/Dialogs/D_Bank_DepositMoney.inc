ShowDialog:Bank_DepositMoney(playerID)
{
	CreateDialog(playerID, "Bank_DepositMoney", DIALOG_STYLE_INPUT, LanguageString(playerID, StringID:208("Deposit money")), LanguageString(playerID, StringID:212("Enter the amount how much money you want to deposit to your account.")), "OK", LanguageString(playerID, StringID:165("Cancel")));
}

DialogResponse:Bank_DepositMoney(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (!strlen(inputText))
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:19("You have to enter the amount!"));
			ShowDialog:Bank_DepositMoney(playerID);
		}
		else
		{
			new Float:money = floatstr(inputText);
			if(money > PVar:playerID[MONEY])
			{
				SendClientMessageEx(playerID, COLOR_ERROR, StringID:14("You don't have enough money!"));
				ShowDialog:Bank_DepositMoney(playerID);
			}
			else
			{
				SetPlayerMoney(playerID, MONEY_BANK, money, true);
				SetPlayerMoney(playerID, MONEY_CASH, -money, true);
				SendClientMessageEx(playerID, COLOR_INFO, StringID:21("You have transferred %m to your bank account"), money);
				ShowDialog:Bank_HasAccount(playerID);
			}
		}
	}
	else
	{
		ShowDialog:Bank_HasAccount(playerID);
	}
}