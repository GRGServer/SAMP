GetXYZFromAngle(&Float:posX, &Float:posY, &Float:posZ, Float:angle, Float:elevation, Float:distance)
{
	posX += (distance * floatsin(angle, degrees) * floatcos(elevation, degrees));
	posY += (distance * floatcos(angle, degrees) * floatcos(elevation, degrees));
	posZ += (distance * floatsin(elevation, degrees));
}