OnInteriorDialogSelect(playerID, dialogID, interiorID)
{
	switch (dialogID)
	{
		case INTERIORDIALOG_ADDPROPERTY:
		{
			if (interiorID)
			{
				PVar:playerID[ADDPROPERTY_INTERIORID] = interiorID;
				ShowDialog:AddProperty_Name(playerID);
			}
			else
			{
				ShowDialog:AddProperty_Type(playerID);
			}
		}
		case INTERIORDIALOG_SHOWINTERIOR:
		{
			if (interiorID)
			{
				if (TeleportToInterior(playerID, interiorID))
				{
					SetPlayerVirtualWorld(playerID, 0);
				}
			}
		}
	}
}