GetMissionData(sourceData[], targetArray[][][])
{
	new tmpMissionData[20][64];

	explode(sourceData, tmpMissionData, ',');
	Foreach(arrayIndex, tmpMissionData)
	{
		sscanf(tmpMissionData[arrayIndex], "p<:>s[64]s[64]", targetArray[arrayIndex][0], targetArray[arrayIndex][1]);
	}
}