UpdateGasPrice()
{
	gasPrice = float(GASSTATION_MINPRICE + random(GASSTATION_MAXDIFFERENCE)) / 100;
	printf("Updated gas price to $%s", FormatMoney(gasPrice));
}