/**
 * <summary>
 *	This callback gets called once the player selects an interior from the interior selection dialog (SelectInterior).
 * </summary>
 *
 * <param name="playerID">
 *	The ID of the player which selected the interior.
 * </param>
 *
 * <param name="dialogID">
 *	An unique ID for the interior dialog.
 * </param>
 *
 * <param name="interiorID">
 *	The ID of the selected interior (This is the ID from the <b>interiors</b> table!)
 * </param>
 */

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