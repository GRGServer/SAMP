/**
 * <summary>
 *	Load all objects from the given XML file
 * </summary>
 *
 * <param name="filename">
 *	The name of the file in scriptfiles directory
 * </param>
 *
 * <remarks>
 *	The XML file must have the following structure:
 *	<objects>
 *		<object>
 *			<id>The internal ID</id>
 *			<modelId>ID of the model</modelId>
 *			<position>
 *				<x>0</x>
 *				<y>0</y>
 *				<z>0</z>
 *			</position>
 *			<rotation>
 *				<x>0</x>
 *				<y>0</y>
 *				<z>0</z>
 *			</rotation>
 *			<interior>0</interior>
 *		</object>
 *	</objects>
 * </remarks>
 */

LoadObjectsFromFile(filename[])
{
	new count;
	new value[100];

	FormatNew:filePath[100]("objects/%s", filename);

	new XMLNode:xml = XML_LoadDocument(filePath);
	xml = XML_GetFirstChild(xml, "objects");
	new XMLNode:objectNode = XML_GetFirstChild(xml, "object");
	while (objectNode)
	{
		// Arrays holding X, Y, Z for position and rotation
		new Float:position[3];
		new Float:rotation[3];

		// Arrays holding X, Y, Z for position and rotation of move target
		new Float:movePosition[3];
		new Float:moveRotation[3];

		XML_GetValue(XML_GetFirstChild(XML_GetFirstChild(objectNode, "id")), value);
		new id = strval(value);

		XML_GetValue(XML_GetFirstChild(XML_GetFirstChild(objectNode, "modelId")), value);
		new modelId = strval(value);

		XML_GetValue(XML_GetFirstChild(XML_GetFirstChild(objectNode, "interior")), value);
		new interior = strval(value);

		// Read position
		new XMLNode:positionNode = XML_GetFirstChild(objectNode, "position");
		XML_GetValue(XML_GetFirstChild(XML_GetFirstChild(positionNode, "x")), value);
		position[0] = floatstr(value);
		XML_GetValue(XML_GetFirstChild(XML_GetFirstChild(positionNode, "y")), value);
		position[1] = floatstr(value);
		XML_GetValue(XML_GetFirstChild(XML_GetFirstChild(positionNode, "z")), value);
		position[2] = floatstr(value);

		// Read rotation
		new XMLNode:rotationNode = XML_GetFirstChild(objectNode, "rotation");
		XML_GetValue(XML_GetFirstChild(XML_GetFirstChild(rotationNode, "x")), value);
		rotation[0] = floatstr(value);
		XML_GetValue(XML_GetFirstChild(XML_GetFirstChild(rotationNode, "y")), value);
		rotation[1] = floatstr(value);
		XML_GetValue(XML_GetFirstChild(XML_GetFirstChild(rotationNode, "z")), value);
		rotation[2] = floatstr(value);

		new XMLNode:moveNode = XML_GetFirstChild(objectNode, "move");

		new Float:moveSpeed;

		if (moveNode)
		{
			// Read move target position
			positionNode = XML_GetFirstChild(moveNode, "position");
			XML_GetValue(XML_GetFirstChild(XML_GetFirstChild(positionNode, "x")), value);
			movePosition[0] = floatstr(value);
			XML_GetValue(XML_GetFirstChild(XML_GetFirstChild(positionNode, "y")), value);
			movePosition[1] = floatstr(value);
			XML_GetValue(XML_GetFirstChild(XML_GetFirstChild(positionNode, "z")), value);
			movePosition[2] = floatstr(value);

			// Read move target rotation
			rotationNode = XML_GetFirstChild(moveNode, "rotation");
			XML_GetValue(XML_GetFirstChild(XML_GetFirstChild(rotationNode, "x")), value);
			moveRotation[0] = floatstr(value);
			XML_GetValue(XML_GetFirstChild(XML_GetFirstChild(rotationNode, "y")), value);
			moveRotation[1] = floatstr(value);
			XML_GetValue(XML_GetFirstChild(XML_GetFirstChild(rotationNode, "z")), value);
			moveRotation[2] = floatstr(value);

			// Read move speed
			XML_GetValue(XML_GetFirstChild(XML_GetFirstChild(moveNode, "speed")), value);
			moveSpeed = floatstr(value);
		}

		new objectID = CreateDynamicObject(modelId, position[0], position[1], position[2], rotation[0], rotation[1], rotation[2], -1, interior, -1, STREAMER_OBJECTDISTANCE);
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_EXTRA_ID, OBJECTTYPE_NORMAL);

		new arrayIndex = objectID - 1;// The first object created with CreateDynamicObject gets ID 1, but the first array index in dynamicObjects array is 0

		// Basic object data
		strmid(dynamicObjects[arrayIndex][OBJECT_FILENAME], filename, 0, strlen(filename) - 4, STRINGLENGTH_OBJECTFILENAME);
		dynamicObjects[arrayIndex][OBJECT_ID] = id;
		dynamicObjects[arrayIndex][OBJECT_POS] = position;
		dynamicObjects[arrayIndex][OBJECT_ROT] = rotation;

		// Moveable objects data
		dynamicObjects[arrayIndex][OBJECT_MOVEPOS] = movePosition;
		dynamicObjects[arrayIndex][OBJECT_MOVEROT] = moveRotation;
		dynamicObjects[arrayIndex][OBJECT_MOVESPEED] = moveSpeed;

		if (id >= nextDynamicObjectID)
		{
			nextDynamicObjectID = id + 1;
		}

		objectNode = XML_GetNextSibling(objectNode, "object");

		count++;
	}

	return count;
}