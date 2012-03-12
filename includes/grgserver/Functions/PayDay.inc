PayDay(playerID)
{
	new Float:salaryWithTax;
	new Float:salaryWithoutTax;
	vehicle = float(120 + random(180));
	power = float(120 + random(280));
	withouttax = vehicle+power;
	if (strval(GetMySQLValue("jobs", "OwnerUserID", "ID", val2str(PVar:playerID[JOBID]))) == PVar:playerID[USERID])
	{
		salaryWithTax = floatstr(GetMySQLValue("jobs", "EmployerSalary", "ID", val2str(PVar:playerID[JOBID])));
		salaryWithoutTax = floatstr(GetMySQLValue("jobs", "EmployerSalary", "ID", val2str(PVar:playerID[JOBID])))-withouttax;
		printf("%s is employer and gets $%s Brutto and Netto $%s", GetPlayerNameEx(playerID), FormatMoney(salaryWithTax), FormatMoney(salaryWithoutTax));
	}
	else
	{
		salaryWithTax = floatstr(GetMySQLValue("jobs", "EmployeeSalary", "ID", val2str(PVar:playerID[JOBID])));
		salaryWithoutTax = floatstr(GetMySQLValue("jobs", "EmployeeSalary", "ID", val2str(PVar:playerID[JOBID])))-withouttax;
		printf("%s is employee and gets $%s Brutto and Netto $%s", GetPlayerNameEx(playerID), FormatMoney(salaryWithTax), FormatMoney(salaryWithoutTax));
	}
	PVar:playerID[BANKMONEY] += salaryWithoutTax;
	FormatNew:string[110]("Es ist Zahltag! Du bekommst $%s (Brutto) bzw. $%s (Netto) auf deinem Konto gutgeschrieben.", FormatMoney(salaryWithTax), FormatMoney(salaryWithoutTax));
	SendClientMessage(playerID, COLOR_INFO, string);
}