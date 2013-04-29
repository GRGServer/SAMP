ShowDialog:Bank_HasAccount(playerID)
{
	new options[1024];
	AddLine(options, LanguageString(playerID, StringID:206("Bank balance")));// Bank balance
	AddLine(options, LanguageString(playerID, StringID:207("Withdraw money")));// Withdraw money
	AddLine(options, LanguageString(playerID, StringID:208("Deposit money")));// Deposit money
	AddLine(options, LanguageString(playerID, StringID:209("Cancel account")));// Cancel account
	CreateDialog(playerID, "Bank_HasAccount", DIALOG_STYLE_LIST, "Bank", options, "OK", LanguageString(playerID, StringID:165("Cancel")));
}

DialogResponse:Bank_HasAccount(playerID, response, listItem, inputText[])
{
	if (response)
	{
		switch (listItem)
		{
			case 0:// Bank balance
			{
				SendClientMessageEx(playerID, COLOR_INFO, StringID:23("Your current bank balance is %m"), PVar:playerID[BANK_MONEY]);
				ShowDialog:Bank_HasAccount(playerID);
			}
			case 1:// Withdraw money
			{
				ShowDialog:Bank_WithdrawMoney(playerID);
			}
			case 2:// Deposit money
			{
				ShowDialog:Bank_DepositMoney(playerID);
			}
			case 3:// Cancel account
			{
				if (PVar:playerID[BANK_MONEY] > 0)
				{
					SendClientMessageEx(playerID, COLOR_ERROR, StringID:215("Your bank account must be empty in order to cancel your account."));
					ShowDialog:Bank_HasAccount(playerID);
				}
				else
				{
					ShowDialog:Bank_CancelAccount(playerID);
				}
			}
		}
	}
	else
	{
		LeaveProperty(playerID);
	}
}