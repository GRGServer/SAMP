PayDay(playerID)
{
	new Float:salaryWithTax;
	new Float:salaryWithoutTax;
	if (strval(GetMySQLValue("jobs", "OwnerUserID", "ID", val2str(PVar:playerID[JOBID]))) == PVar:playerID[USERID])
	{
		salaryWithTax = floatstr(GetMySQLValue("jobs", "EmployerSalary", "ID", val2str(PVar:playerID[JOBID])));
		printf("%s is employer and gets $%s", GetPlayerNameEx(playerID), FormatMoney(salaryWithTax));
	}
	else
	{
		salaryWithTax = floatstr(GetMySQLValue("jobs", "EmployeeSalary", "ID", val2str(PVar:playerID[JOBID])));
		printf("%s is employee and gets $%s", GetPlayerNameEx(playerID), FormatMoney(salaryWithTax));
	}
	salaryWithoutTax = salaryWithTax; // TODO: Substract tax from salary
	PVar:playerID[BANKMONEY] += salaryWithoutTax;
	FormatNew:string[110]("Es ist Zahltag! Du bekommst $%s (Brutto) bzw. $%s (Netto) auf deinem Konto gutgeschrieben.", FormatMoney(salaryWithTax), FormatMoney(salaryWithoutTax));
	SendClientMessage(playerID, COLOR_INFO, string);
}