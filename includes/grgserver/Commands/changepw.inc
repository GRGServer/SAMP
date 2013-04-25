CMD:changepw(playerID, params[], StringID:98("Change account password"))
{
	ShowDialog:ChangePassword_Step1(playerID);
	return COMMAND_OK;
}