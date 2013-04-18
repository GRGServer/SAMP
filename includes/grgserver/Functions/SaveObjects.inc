/**
 * <summary>
 *	Save the specified objects file
 * </summary>
 *
 * <param name="filename">
 *	The name of the file in scriptfiles directory
 * </param>
 */

SaveObjects(filename[])
{
	new value[100];

	FormatNew:filePath[STRINGLENGTH_OBJECTFILENAME]("objects/%s.xml", filename);

	new XMLNode:document = XML_CreateDocument(filePath);
	new XMLNode:rootNode = XML_CreateNode(document, "objects");

	new count = CountDynamicObjects();
	Count(arrayIndex, count)
	{
		if (Streamer_GetIntData(STREAMER_TYPE_OBJECT, arrayIndex + 1, E_STREAMER_EXTRA_ID) == OBJECTTYPE_NORMAL && !strcmp(filename, dynamicObjects[arrayIndex][OBJECT_FILENAME], true))
		{
			new XMLNode:objectNode = XML_CreateNode(rootNode, "object");

			Format:value("%d", dynamicObjects[arrayIndex][OBJECT_ID]);
			XML_CreateNode(XML_CreateNode(objectNode, "id"), value, e_XML_NODE_TEXT);

			Format:value("%d", Streamer_GetIntData(STREAMER_TYPE_OBJECT, arrayIndex + 1, E_STREAMER_MODEL_ID));
			XML_CreateNode(XML_CreateNode(objectNode, "modelId"), value, e_XML_NODE_TEXT);

			Format:value("%d", Streamer_GetIntData(STREAMER_TYPE_OBJECT, arrayIndex + 1, E_STREAMER_INTERIOR_ID));
			XML_CreateNode(XML_CreateNode(objectNode, "interior"), value, e_XML_NODE_TEXT);

			new XMLNode:positionNode = XML_CreateNode(objectNode, "position");
			Format:value("%f", dynamicObjects[arrayIndex][OBJECT_POS][0]);
			XML_CreateNode(XML_CreateNode(positionNode, "x"), value, e_XML_NODE_TEXT);
			Format:value("%f", dynamicObjects[arrayIndex][OBJECT_POS][1]);
			XML_CreateNode(XML_CreateNode(positionNode, "y"), value, e_XML_NODE_TEXT);
			Format:value("%f", dynamicObjects[arrayIndex][OBJECT_POS][2]);
			XML_CreateNode(XML_CreateNode(positionNode, "z"), value, e_XML_NODE_TEXT);

			new XMLNode:rotationNode = XML_CreateNode(objectNode, "rotation");
			Format:value("%f", dynamicObjects[arrayIndex][OBJECT_ROT][0]);
			XML_CreateNode(XML_CreateNode(rotationNode, "x"), value, e_XML_NODE_TEXT);
			Format:value("%f", dynamicObjects[arrayIndex][OBJECT_ROT][1]);
			XML_CreateNode(XML_CreateNode(rotationNode, "y"), value, e_XML_NODE_TEXT);
			Format:value("%f", dynamicObjects[arrayIndex][OBJECT_ROT][2]);
			XML_CreateNode(XML_CreateNode(rotationNode, "z"), value, e_XML_NODE_TEXT);

			if (dynamicObjects[arrayIndex][OBJECT_MOVESPEED])
			{
				new XMLNode:moveNode = XML_CreateNode(objectNode, "move");

				positionNode = XML_CreateNode(moveNode, "position");
				Format:value("%f", dynamicObjects[arrayIndex][OBJECT_MOVEPOS][0]);
				XML_CreateNode(XML_CreateNode(positionNode, "x"), value, e_XML_NODE_TEXT);
				Format:value("%f", dynamicObjects[arrayIndex][OBJECT_MOVEPOS][1]);
				XML_CreateNode(XML_CreateNode(positionNode, "y"), value, e_XML_NODE_TEXT);
				Format:value("%f", dynamicObjects[arrayIndex][OBJECT_MOVEPOS][2]);
				XML_CreateNode(XML_CreateNode(positionNode, "z"), value, e_XML_NODE_TEXT);

				rotationNode = XML_CreateNode(moveNode, "rotation");
				Format:value("%f", dynamicObjects[arrayIndex][OBJECT_MOVEROT][0]);
				XML_CreateNode(XML_CreateNode(rotationNode, "x"), value, e_XML_NODE_TEXT);
				Format:value("%f", dynamicObjects[arrayIndex][OBJECT_MOVEROT][1]);
				XML_CreateNode(XML_CreateNode(rotationNode, "y"), value, e_XML_NODE_TEXT);
				Format:value("%f", dynamicObjects[arrayIndex][OBJECT_MOVEROT][2]);
				XML_CreateNode(XML_CreateNode(rotationNode, "z"), value, e_XML_NODE_TEXT);

				Format:value("%f", dynamicObjects[arrayIndex][OBJECT_MOVESPEED]);
				XML_CreateNode(XML_CreateNode(moveNode, "speed"), value, e_XML_NODE_TEXT);
			}
		}
	}

	XML_SaveDocument(document);
}