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
		if (PVar:playerID[BANK_ID])
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
			vehicleTax = floatsub(vehicleTax, 12);// Tax is stored per year, but this should be the per month value

			new Float:salaryWithTax;
			new Float:salaryWithoutTax;
			new powerTax = 50 + random(50);
			new Float:tax = floatadd(vehicleTax, float(powerTax));

			MySQLQuery("SELECT `ownerUserId`, `employerSalary`, `employeeSalary` FROM `users` LEFT JOIN `jobs` ON `jobs`.`id` = `users`.`jobId` WHERE `users`.`id` = '%d'", PVar:playerID[USERID]);
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

			SendClientMessageEx(playerID, COLOR_INFO, StringID:133("It's pay day! You get %m deposited into your bank account."), salaryWithoutTax);
			SendClientMessageEx(playerID, COLOR_INFO, StringID:625("See /payday for more details"));
		}
		else
		{
			SendClientMessageEx(playerID, COLOR_ERROR, StringID:225("It's pay day but you can't receive money because you don't have a bank account! Get a bank account!"));
		}
	}
}