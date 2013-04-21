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
 *		<object id="The internal ID" model="ID of the model" posX="0" posY="0" posZ="0" rotX="0" rotY="0" rotZ="0" interior="0">
 *			<move posX="0" posY="0" posZ="0" rotX="0" rotY="0" rotZ="0" speed="0.1" timeout="1000"/>
 *			<speedcamera speedLimit="50"/>
 *		</object>
 *	</objects>
 *	The move-element is optional (Required if you want to move the object using MoveObjectEx)
 *	The speedcamera-Element is only used and required for speed camera objects (Model 18880)
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

		XML_GetAttribute(objectNode, "id", value);
		new id = strval(value);

		XML_GetAttribute(objectNode, "model", value);
		new modelID = strval(value);

		XML_GetAttribute(objectNode, "interior", value);
		new interior = strval(value);

		// Read position
		XML_GetAttribute(objectNode, "posX", value);
		position[0] = floatstr(value);
		XML_GetAttribute(objectNode, "posY", value);
		position[1] = floatstr(value);
		XML_GetAttribute(objectNode, "posZ", value);
		position[2] = floatstr(value);

		// Read rotation
		XML_GetAttribute(objectNode, "rotX", value);
		rotation[0] = floatstr(value);
		XML_GetAttribute(objectNode, "rotY", value);
		rotation[1] = floatstr(value);
		XML_GetAttribute(objectNode, "rotZ", value);
		rotation[2] = floatstr(value);

		new XMLNode:moveNode = XML_GetFirstChild(objectNode, "move");

		new Float:moveSpeed;
		new moveTimeout;

		if (moveNode)
		{
			// Read move target position
			XML_GetAttribute(moveNode, "posX", value);
			movePosition[0] = floatstr(value);
			XML_GetAttribute(moveNode, "posY", value);
			movePosition[1] = floatstr(value);
			XML_GetAttribute(moveNode, "posZ", value);
			movePosition[2] = floatstr(value);

			// Read move target rotation
			XML_GetAttribute(moveNode, "rotX", value);
			moveRotation[0] = floatstr(value);
			XML_GetAttribute(moveNode, "rotY", value);
			moveRotation[1] = floatstr(value);
			XML_GetAttribute(moveNode, "rotZ", value);
			moveRotation[2] = floatstr(value);

			// Read move speed
			XML_GetAttribute(moveNode, "speed", value);
			moveSpeed = floatstr(value);

			// Read move timeout
			XML_GetAttribute(moveNode, "timeout", value);
			moveTimeout = strval(value);
		}

		new objectID = CreateDynamicObject(modelID, position[0], position[1], position[2], rotation[0], rotation[1], rotation[2], -1, interior, -1, STREAMER_OBJECTDISTANCE);
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
		dynamicObjects[arrayIndex][OBJECT_MOVETIMEOUT] = moveTimeout;

		if (modelID == SPEEDCAMERA_OBJECTMODEL)// This object has the speed camera model
		{
			new XMLNode:speedcameraNode = XML_GetFirstChild(objectNode, "speedcamera");
			if (speedcameraNode)
			{
				XML_GetAttribute(speedcameraNode, "speedLimit", value);
				new speedLimit = strval(value);

				Foreach(speedCamerasArrayIndex, speedCameras)
				{
					if (!speedCameras[speedCamerasArrayIndex][SPEEDCAMERA_OBJECTID])
					{
						speedCameras[speedCamerasArrayIndex][SPEEDCAMERA_OBJECTID] = objectID;
						speedCameras[speedCamerasArrayIndex][SPEEDCAMERA_SPEEDLIMIT] = speedLimit;
						break;
					}
				}
			}
			else
			{
				printf("Missing speedcamera element for object %d!", id);
			}
		}

		if (id >= nextDynamicObjectID)
		{
			nextDynamicObjectID = id + 1;
		}

		objectNode = XML_GetNextSibling(objectNode, "object");

		count++;
	}

	return count;
}