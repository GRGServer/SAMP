/**
 * <summary>
 *	Do PayDay for the given player.
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player
 * </param>
 */

PayDay(playerID)
{
	if (IsLoggedIn(playerID))
	{
		MySQLQuery("SELECT `bankAccountId` FROM `users` WHERE `id` = '%d'", PVar:playerID[USERID]);
		mysql_store_result();
		new bankAccountID = strval(GetMySQLField("bankAccountId"));
		mysql_free_result();
		if (bankAccountID)
		{
			new Float:vehicleTax;
			Count1(vehicleID, MAX_VEHICLES)
			{
				if (VehicleProperty:vehicleID[OWNERUSERID] == PVar:playerID[USERID])
				{
					new modelIndex = GetVehicleModel(vehicleID) - 400;
					if (modelIndex >= 0 && modelIndex < sizeof(vehicleModels))
					{
						vehicleTax = floatadd(vehicleTax, vehicleModels[modelIndex][VEHICLEMODEL_TAX]);
					}
				}
			}
			vehicleTax = floatsub(vehicleTax, 12);
			new Float:salaryWithTax;
			new Float:salaryWithoutTax;
			new powerTax = 50 + random(50);
			new Float:tax = floatadd(vehicleTax, float(powerTax));
			MySQLQuery("SELECT `jobs`.* FROM `users` LEFT JOIN `jobs` ON `jobs`.`id` = `users`.`jobId` WHERE `users`.`id` = '%d'", PVar:playerID[USERID]);
			mysql_store_result();
			if (strval(GetMySQLField("ownerUserId")) == PVar:playerID[USERID])
			{
				salaryWithTax = floatstr(GetMySQLField("employerSalary"));
			}
			else
			{
				salaryWithTax = floatstr(GetMySQLField("employeeSalary"));
			}
			mysql_free_result();
			salaryWithoutTax = floatsub(salaryWithTax, tax);
			SetPlayerMoney(playerID, MONEY_BANK, salaryWithoutTax, true);
			MoneyTransaction(playerID, CASHTRANS_VEHICLETAX, 0, 0, -vehicleTax);
			MoneyTransaction(playerID, CASHTRANS_POWERTAX, 0, 0, -powerTax);
			MoneyTransaction(playerID, CASHTRANS_PAYDAY, 0, 0, salaryWithoutTax);
			SendClientMessageEx(playerID, COLOR_INFO, StringID:133(""), salaryWithoutTax);
			SendClientMessageEx(playerID, COLOR_INFO, StringID:625(""));
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:225(""));
		}
	}
}