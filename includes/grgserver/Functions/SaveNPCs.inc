/**
 * <summary>
 *	Save all NPCs
 * </summary>
 */

SaveNPCs()
{
	new XMLNode:document = XML_CreateDocument(FILE_NPCS);
	new XMLNode:rootNode = XML_CreateNode(document, "npcs");

	Foreach(arrayIndex, npcs)
	{
		new XMLNode:npcNode = XML_CreateNode(rootNode, "npc");

		XML_SetAttribute(npcNode, "name", npcs[arrayIndex][NPC_NAME]);
		XML_SetAttribute(npcNode, "skin", val2str(npcs[arrayIndex][NPC_SKIN]));

		if (StrNotNull(npcs[arrayIndex][NPC_RECORDING]))
		{
			new XMLNode:recordingNode = XML_CreateNode(npcNode, "recording");

			XML_SetAttribute(recordingNode, "name", npcs[arrayIndex][NPC_RECORDING]);
			XML_SetAttribute(recordingNode, "startDelay", val2str(npcs[arrayIndex][NPC_STARTDELAY]));
			XML_SetAttribute(recordingNode, "autoStart", val2str(npcs[arrayIndex][NPC_AUTOSTART]));
			XML_SetAttribute(recordingNode, "autoRepeat", val2str(npcs[arrayIndex][NPC_AUTOREPEAT]));
		}

		if (npcs[arrayIndex][NPC_VEHICLEID])
		{
			new XMLNode:vehicleNode = XML_CreateNode(npcNode, "vehicle");

			XML_SetAttribute(vehicleNode, "model", val2str(GetVehicleModel(npcs[arrayIndex][NPC_VEHICLEID])));
			XML_SetAttribute(vehicleNode, "color1", val2str(GetVehicleModel(npcs[arrayIndex][NPC_VEHICLECOLORS][0])));
			XML_SetAttribute(vehicleNode, "color2", val2str(GetVehicleModel(npcs[arrayIndex][NPC_VEHICLECOLORS][1])));
		}

		if (npcs[arrayIndex][NPC_SPAWNPOS][0] || npcs[arrayIndex][NPC_SPAWNPOS][1] || npcs[arrayIndex][NPC_SPAWNPOS][2])
		{
			new XMLNode:spawnNode = XML_CreateNode(npcNode, "spawn");

			XML_SetAttribute(spawnNode, "posX", float2str(npcs[arrayIndex][NPC_SPAWNPOS][0]));
			XML_SetAttribute(spawnNode, "posY", float2str(npcs[arrayIndex][NPC_SPAWNPOS][1]));
			XML_SetAttribute(spawnNode, "posZ", float2str(npcs[arrayIndex][NPC_SPAWNPOS][2]));
			XML_SetAttribute(spawnNode, "angle", float2str(npcs[arrayIndex][NPC_SPAWNANGLE]));
		}
	}

	XML_SaveDocument(document);
}