ShowDialog:Bank_PIN(playerID)
{
	CreateDialog(playerID, "Bank_PIN", DIALOG_STYLE_PASSWORD, LanguageString(playerID, StringID:580("Enter PIN")), LanguageString(playerID, StringID:581("Enter the PIN of your bank account.")), "OK", LanguageString(playerID, StringID:165("Cancel")));
}

DialogResponse:Bank_PIN(playerID, response, listItem, inputText[])
{
	if (!response)
	{
		LeaveProperty(playerID);
		return false;
	}

	new pin = strval(inputText);
	if (pin < BANK_PIN_MIN || pin > BANK_PIN_MAX)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:582("The PIN must be between %d and %d!"), BANK_PIN_MIN, BANK_PIN_MAX);
		ShowDialog:Bank_PIN(playerID);
		return false;
	}

	if (PVar:playerID[BANK_PIN_ATTEMPTS] >= BANK_PIN_MAXATTEMPTS)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:585("You have reached the maximum number of wrong tries! Your bank account has been blocked!"));
		LeaveProperty(playerID);
		return false;
	}

	if (PVar:playerID[BANK_PIN] == pin)
	{
		PVar:playerID[BANK_PIN_ATTEMPTS] = 0;
		ShowDialog:Bank_HasAccount(playerID);
		return true;
	}

	SendClientMessageEx(playerID, COLOR_ERROR, StringID:583("The entered PIN is not correct!"));
	if (PVar:playerID[BANK_PIN_ATTEMPTS] >= BANK_PIN_MAXATTEMPTS)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:585("You have reached the maximum number of wrong tries! Your bank account has been blocked!"));
		LeaveProperty(playerID);
		return false;
	}

	PVar:playerID[BANK_PIN_ATTEMPTS]++;
	if (PVar:playerID[BANK_PIN_ATTEMPTS] >= BANK_PIN_MAXATTEMPTS)
	{
		SendClientMessageEx(playerID, COLOR_ERROR, StringID:585("You have reached the maximum number of wrong tries! Your bank account has been blocked!"));
		LeaveProperty(playerID);
		return false;
	}

	SendClientMessageEx(playerID, COLOR_ERROR, StringID:584("You have %d more tries"), BANK_PIN_MAXATTEMPTS - PVar:playerID[BANK_PIN_ATTEMPTS]);
	ShowDialog:Bank_PIN(playerID);
	return false;
}