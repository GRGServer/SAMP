GetXYFromAngle(&Float:posX, &Float:posY, Float:angle, Float:distance)
{
	posX += (distance * floatsin(-angle, degrees));
	posY += (distance * floatcos(-angle, degrees));
}