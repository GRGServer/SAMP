float2str(Float:value)
{
	FormatNew:string[30]("%f", value);
	return string;
}