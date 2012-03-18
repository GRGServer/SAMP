PayDay(playerID)
{
	new Float:salaryWithTax;
	new Float:salaryWithoutTax;
	new vehicleTax = 120 + random(180);
	new powerTax = 120 + random(280);
	new Float:tax = float(vehicleTax + powerTax);
	if (strval(GetMySQLValue("jobs", "OwnerUserID", "ID", val2str(PVar:playerID[JOBID]))) == PVar:playerID[USERID])
	{
		salaryWithTax = floatstr(GetMySQLValue("jobs", "EmployerSalary", "ID", val2str(PVar:playerID[JOBID])));
	}
	else
	{
		salaryWithTax = floatstr(GetMySQLValue("jobs", "EmployeeSalary", "ID", val2str(PVar:playerID[JOBID])));
	}
	salaryWithoutTax = floatsub(salaryWithTax, tax);
	PVar:playerID[BANKMONEY] += salaryWithoutTax;
	MoneyTransaction(playerID, CASHTRANS_VEHICLETAX, 0, 0, -vehicleTax);
	MoneyTransaction(playerID, CASHTRANS_POWERTAX, 0, 0, -powerTax);
	MoneyTransaction(playerID, CASHTRANS_PAYDAY, 0, 0, salaryWithoutTax);
	SendClientMessageEx(playerID, COLOR_INFO, 133, salaryWithoutTax);
}