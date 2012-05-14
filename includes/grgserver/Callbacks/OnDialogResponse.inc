public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (!strlen(PVar:playerid[CURRENTDIALOG]))
	{
		return false;
	}
	FormatNew:functionName[MAX_FUNCTION_NAME]("DR_%s", PVar:playerid[CURRENTDIALOG]);// DR = DialogResponse
	if (funcidx(functionName) == -1)
	{
		printf("[DialogResponse] Undefined dialog: %s", PVar:playerid[CURRENTDIALOG]);
		SetPVarStr:playerid[CURRENTDIALOG][STRINGLENGTH_DIALOGNAME]("");
		return false;
	}
	SetPVarStr:playerid[CURRENTDIALOG][STRINGLENGTH_DIALOGNAME]("");
	if (!strlen(inputtext))
	{
		inputtext[0] = '\1';
	}
	CallLocalFunction(functionName, "ddds", playerid, response, listitem, inputtext);
	return true;
}