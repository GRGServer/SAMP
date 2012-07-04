ShowDialog:Bank_HasAccount(playerID)
{
	new query[256];
	format(query,sizeof(query),"SELECT `accountPIN` FROM `bankaccounts` WHERE id = '%d'", PVar:playerID[USERID]);
	new BANK_PIN = mysql_query(query);
	if(PVar:playerID[BANKPIN] == BANK_PIN)
	{
		new options[1024];
		AddLine(options, LanguageString(playerID, 206));// Bank balance
		AddLine(options, LanguageString(playerID, 207));// Withdraw money
		AddLine(options, LanguageString(playerID, 208));// Deposit money
		AddLine(options, LanguageString(playerID, 209));// Cancel account
		CreateDialog(playerID, "Bank_HasAccount", DIALOG_STYLE_LIST, "Bank", options, "OK", LanguageString(playerID, 165));
	}
}

DialogResponse:Bank_HasAccount(playerID, response, listItem, inputText[])
{
	if (response)
	{
		switch (listItem)
		{
			case 0:// Bank balance
			{
				SendClientMessageEx(playerID, COLOR_INFO, 23, PVar:playerID[BANKMONEY]);
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
				if (PVar:playerID[BANKMONEY] > 0)
				{
					SendClientMessageEx(playerID, COLOR_ERROR, 215);
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