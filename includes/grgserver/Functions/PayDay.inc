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
		salaryWithoutTax = floatsub(salaryWithTax, tax);
	}
	else
	{
		salaryWithTax = floatstr(GetMySQLValue("jobs", "EmployeeSalary", "ID", val2str(PVar:playerID[JOBID])));
		salaryWithoutTax = floatsub(salaryWithTax, tax);
	}
	PVar:playerID[BANKMONEY] += salaryWithoutTax;
	FormatNew:string[110]("Es ist Zahltag! Du bekommst $%s (Brutto) bzw. $%s (Netto) auf deinem Konto gutgeschrieben.", FormatMoney(salaryWithTax), FormatMoney(salaryWithoutTax));
	SendClientMessage(playerID, COLOR_INFO, string);
}