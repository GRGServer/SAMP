CMD:changepw(playerID, params[], 98)
{
	ShowDialog:ChangePassword_Step1(playerID);
	return COMMAND_OK;
}