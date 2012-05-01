ReloadPermissions(playerID = INVALID_PLAYER_ID)
{
	AdminPrint(playerID, COLOR_INFO, "* Reloading permissions...");
	mysql_query("SELECT * FROM `permissions`");
	mysql_store_result();
	while (FetchMySQLRow())
	{
		new userID = strval(GetMySQLField("UserID"));
		if (userID)
		{
			PlayerLoop(currentPlayerID)
			{
				if (PVar:currentPlayerID[USERID] == userID)
				{
					LoadPlayerPermissions(currentPlayerID);
				}
			}
		}
	}
	mysql_free_result();
	AdminPrint(playerID, COLOR_INFO, "  done");
}