CMD:changepw(playerid, params[], "Accountpasswort ändern")
{
	ShowDialog(playerid, DIALOG_CHANGEPASSWORD_STEP1);
	return COMMAND_OK;
}