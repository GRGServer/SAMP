LoadPlayer(playerID)
{
	PVar:playerID[LANGUAGE] = 0;

	MySQLQuery("SELECT * FROM `users` WHERE `id` = '%d'", PVar:playerID[USERID]);
	mysql_store_result();

	new bankAccountId = strval(GetMySQLField("bankAccountId"));
	new Float:cashMoney = floatstr(GetMySQLField("money"));
	
	SetPVarStr:playerID[CHATMODE][STRINGLENGTH_CHATMODE](GetMySQLField("chatMode"));
	PVar:playerID[CHATMODE_USERID] = strval(GetMySQLField("chatModeUserId"));
	PVar:playerID[CURRENTPROPERTYID] = strval(GetMySQLField("currentPropertyId"));
	PVar:playerID[DEATHS] = strval(GetMySQLField("deaths"));
	PVar:playerID[GODMODE] = strval(GetMySQLField("godMode"));
	PVar:playerID[INTUTORIAL] = strval(GetMySQLField("inTutorial"));
	PVar:playerID[JOBID] = strval(GetMySQLField("jobId"));
	strcat(PVar:playerID[LANGUAGE], GetMySQLField("language"), STRINGLENGTH_LANGUAGE);
	PVar:playerID[LASTNEWSID] = strval(GetMySQLField("lastNewsId"));
	PVar:playerID[LASTPAYDAY] = strval(GetMySQLField("lastPayDay"));
	PVar:playerID[NEEDS_BLADDER] = floatstr(GetMySQLField("bladder"));
	PVar:playerID[NEEDS_ENERGY] = floatstr(GetMySQLField("energy"));
	PVar:playerID[NEEDS_HUNGER] = floatstr(GetMySQLField("hunger"));
	PVar:playerID[NEEDS_THIRST] = floatstr(GetMySQLField("thirst"));
	PVar:playerID[ONLINESINCE] = gettime();
	PVar:playerID[ONLINETIME] = strval(GetMySQLField("onlineTime"));
	PVar:playerID[SKIN] = strval(GetMySQLField("skin"));
	PVar:playerID[SHOWCLOCK] = strval(GetMySQLField("showClock"));
	
	PVar:playerID[VEHICLEBOUGHT] = strval(GetMySQLField("vehicleBought"));

	SetPlayerSkin(playerID, PVar:playerID[SKIN]);
	SetPlayerWantedLevel(playerID, strval(GetMySQLField("wantedLevel")));

	new Float:health = floatstr(GetMySQLField("health"));
	if (!health)
	{
		health = 100;
	}
	SetPlayerHealth(playerID, health);

	if (PVar:playerID[NEEDS_BLADDER] <= 0)
	{
		PVar:playerID[NEEDS_BLADDER] = 0;
	}

	if (PVar:playerID[NEEDS_ENERGY] <= 0)
	{
		PVar:playerID[NEEDS_ENERGY] = 0;
	}

	if (PVar:playerID[NEEDS_HUNGER] <= 0)
	{
		PVar:playerID[NEEDS_HUNGER] = 0;
	}

	if (PVar:playerID[NEEDS_THIRST] <= 0)
	{
		PVar:playerID[NEEDS_THIRST] = 0;
	}

	mysql_free_result();

	MySQLQuery("SELECT `money` FROM `bankaccounts` WHERE `id` = '%d'", bankAccountId);
	mysql_store_result();

	new Float:bankMoney = floatstr(GetMySQLField("money"));
	mysql_free_result();

	SetPlayerMoney(playerID, MONEY_BANK, bankMoney);
	SetPlayerMoney(playerID, MONEY_CASH, cashMoney);

	MySQLQuery("SELECT * FROM `permissions` WHERE `userId` = '%d'", PVar:playerID[USERID]);
	mysql_store_result();

	if (mysql_num_rows())
	{
		LoadPlayerPermissions(playerID);
	}

	mysql_free_result();

	TextDrawShowForPlayer(playerID, decimalPoint);
}