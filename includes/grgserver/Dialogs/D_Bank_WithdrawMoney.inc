ShowDialog:Bank_WithdrawMoney(playerID)
{
	CreateDialog(playerID, "Bank_WithdrawMoney", DIALOG_STYLE_INPUT, LanguageString(playerID, StringID:207("Withdraw money")), LanguageString(playerID, StringID:213("Enter the amount how much money you want to withdraw from your account.")), "OK", LanguageString(playerID, StringID:165("Cancel")));
}

DialogResponse:Bank_WithdrawMoney(playerID, response, listItem, inputText[])
{
	if (response)
	{
		if (!strlen(inputText))
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:19("You have to enter the amount!"));
			ShowDialog:Bank_WithdrawMoney(playerID);
		}
		else
		{
			new Float:money = floatstr(inputText);
			if(money > PVar:playerID[BANK_MONEY])
			{
				SendClientMessageEx(playerID, COLOR_ERROR, StringID:25("You don't have enough money at your bank!"));
				ShowDialog:Bank_WithdrawMoney(playerID);
			}
			else
			{
				new Float:newMoney = floatadd(PVar:playerID[MONEY], money);
				if (newMoney > MAX_MONEY)
				{
					newMoney = MAX_MONEY;
					SendClientMessageEx(playerID, COLOR_ERROR, StringID:492("You have exceeded the cash limit of %m!"), MAX_MONEY);
				}
				money = floatsub(newMoney, PVar:playerID[MONEY]);
				SetPlayerMoney(playerID, MONEY_BANK, -money, true);
				SetPlayerMoney(playerID, MONEY_CASH, money, true);
				SendClientMessageEx(playerID, COLOR_INFO, StringID:26("You got %m from your bank account"), money);
				ShowDialog:Bank_HasAccount(playerID);
			}
		}
	}
	else
	{
		ShowDialog:Bank_HasAccount(playerID);
	}
}