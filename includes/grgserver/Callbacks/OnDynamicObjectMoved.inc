/**
 * <summary>
 *	Called once a dynamic object stops moving.
 * </summary>
 *
 * <param name="objectid">
 *	The ID of the object which stopped moving.
 * </param>
 *
 * <remarks>
 *	The timer MoveObject gets called if a timeout is defined for the object and the current position is the move target position
 * </remarks>
 */

public OnDynamicObjectMoved(objectid)
{
	new arrayIndex = objectid - 1;

	new Float:position[3];
	new Float:rotation[3];

	GetDynamicObjectPos(objectid, position[0], position[1], position[2]);
	GetDynamicObjectRot(objectid, rotation[0], rotation[1], rotation[2]);

	if (dynamicObjects[arrayIndex][OBJECT_MOVETIMEOUT])
	{
		if (dynamicObjects[arrayIndex][OBJECT_MOVEPOS][0] == position[0] && dynamicObjects[arrayIndex][OBJECT_MOVEPOS][1] == position[1] && dynamicObjects[arrayIndex][OBJECT_MOVEPOS][2] == position[2])
		{
			if (dynamicObjects[arrayIndex][OBJECT_MOVEROT][0] == rotation[0] && dynamicObjects[arrayIndex][OBJECT_MOVEROT][1] == rotation[1] && dynamicObjects[arrayIndex][OBJECT_MOVEROT][2] == rotation[2])
			{
				SetTimerEx("Timer_MoveObject", dynamicObjects[arrayIndex][OBJECT_MOVETIMEOUT], false, "dd", objectid, false);
			}
		}
	}

	return true;
}