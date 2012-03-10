UpdatePayDay(playerid)
{
	if (PVar:playerid[JOBID] == JOB_BANK)
	{
		// TODO: Muss überprüft werden Welcher Job
		// TODO: Muss überprüft werden ob ihm der Job Gehört
		// TODO: Float Money auf den preis (Wen normaler mitarbeiter = Merit) (Wen Boss also dem es gehört = BossMerit) setzen
		new Float:money = 5600.21;
		SendClientMessage(playerid, COLOR_INFO, "PayDay!");
		FormatNew:string[30]("Dein Lohn beträgt $%s", money);
		SendClientMessage(playerid, COLOR_INFO, string);
		SetUserDBValue(playerid, "BankMoney", Float2Str(floatadd(floatstr(GetUserDBValue(playerid, "BankMoney")), money)));
		printf ("Loading UpdatePayDay");
	}
}