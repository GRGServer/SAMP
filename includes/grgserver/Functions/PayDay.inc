PayDay(playerID)
{
	if (strval(GetMySQLValue("users", "bankAccountId", "id", val2str(PVar:playerID[USERID]))))
	{
		new Float:salaryWithTax;
		new Float:salaryWithoutTax;
		new vehicleTax = 120 + random(180);
		new powerTax = 120 + random(280);
		new Float:tax = float(vehicleTax + powerTax);
		MySQLQuery("SELECT * FROM `jobs` WHERE `id` = '%d'", PVar:playerID[JOBID]);
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
		PVar:playerID[BANKMONEY] += salaryWithoutTax;
		MoneyTransaction(playerID, CASHTRANS_VEHICLETAX, 0, 0, -vehicleTax);
		MoneyTransaction(playerID, CASHTRANS_POWERTAX, 0, 0, -powerTax);
		MoneyTransaction(playerID, CASHTRANS_PAYDAY, 0, 0, salaryWithoutTax);
		SendClientMessageEx(playerID, COLOR_INFO, 133, salaryWithoutTax);
	}
	else
	{
		SendClientMessageEx(playerID, COLOR_ERROR, 225);
	}
}