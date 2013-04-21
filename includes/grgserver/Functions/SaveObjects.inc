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
		new objectID = arrayIndex + 1;
		if (Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_EXTRA_ID) == OBJECTTYPE_NORMAL && !strcmp(filename, dynamicObjects[arrayIndex][OBJECT_FILENAME], true))
		{
			new XMLNode:objectNode = XML_CreateNode(rootNode, "object");

			Format:value("%d", dynamicObjects[arrayIndex][OBJECT_ID]);
			XML_SetAttribute(objectNode, "id", value);

			Format:value("%d", Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_MODEL_ID));
			XML_SetAttribute(objectNode, "model", value);

			Format:value("%d", Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_INTERIOR_ID));
			XML_SetAttribute(objectNode, "interior", value);

			Format:value("%f", dynamicObjects[arrayIndex][OBJECT_POS][0]);
			XML_SetAttribute(objectNode, "posX", value);

			Format:value("%f", dynamicObjects[arrayIndex][OBJECT_POS][1]);
			XML_SetAttribute(objectNode, "posY", value);

			Format:value("%f", dynamicObjects[arrayIndex][OBJECT_POS][2]);
			XML_SetAttribute(objectNode, "posZ", value);

			Format:value("%f", dynamicObjects[arrayIndex][OBJECT_ROT][0]);
			XML_SetAttribute(objectNode, "rotX", value);

			Format:value("%f", dynamicObjects[arrayIndex][OBJECT_ROT][1]);
			XML_SetAttribute(objectNode, "rotY", value);

			Format:value("%f", dynamicObjects[arrayIndex][OBJECT_ROT][2]);
			XML_SetAttribute(objectNode, "rotZ", value);

			if (dynamicObjects[arrayIndex][OBJECT_MOVESPEED])
			{
				new XMLNode:moveNode = XML_CreateNode(objectNode, "move");

				Format:value("%f", dynamicObjects[arrayIndex][OBJECT_MOVEPOS][0]);
				XML_SetAttribute(moveNode, "posX", value);

				Format:value("%f", dynamicObjects[arrayIndex][OBJECT_MOVEPOS][1]);
				XML_SetAttribute(moveNode, "posY", value);

				Format:value("%f", dynamicObjects[arrayIndex][OBJECT_MOVEPOS][2]);
				XML_SetAttribute(moveNode, "posZ", value);

				Format:value("%f", dynamicObjects[arrayIndex][OBJECT_MOVEROT][0]);
				XML_SetAttribute(moveNode, "rotX", value);

				Format:value("%f", dynamicObjects[arrayIndex][OBJECT_MOVEROT][1]);
				XML_SetAttribute(moveNode, "rotY", value);

				Format:value("%f", dynamicObjects[arrayIndex][OBJECT_MOVEROT][2]);
				XML_SetAttribute(moveNode, "rotZ", value);

				Format:value("%f", dynamicObjects[arrayIndex][OBJECT_MOVESPEED]);
				XML_SetAttribute(moveNode, "speed", value);

				Format:value("%d", dynamicObjects[arrayIndex][OBJECT_MOVETIMEOUT]);
				XML_SetAttribute(moveNode, "timeout", value);
			}

			if (Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectID, E_STREAMER_MODEL_ID) == SPEEDCAMERA_OBJECTMODEL)// This object has the speed camera model
			{
				new XMLNode:speedcameraNode = XML_CreateNode(objectNode, "speedcamera");

				Foreach(speedCameraArrayIndex, speedCameras)
				{
					if (speedCameras[speedCameraArrayIndex][SPEEDCAMERA_OBJECTID] == objectID)
					{
						Format:value("%d", speedCameras[speedCameraArrayIndex][SPEEDCAMERA_SPEEDLIMIT]);
						XML_SetAttribute(speedcameraNode, "speedLimit", value);
						break;
					}
				}
			}
		}
	}

	XML_SaveDocument(document);
}