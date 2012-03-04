CalculateAge(birthDate)
{
	return (gettime() - birthDate) / 60 / 60 / 24 / 365;
}