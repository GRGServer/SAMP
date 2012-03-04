UpdateGasPrice()
{
	gasPrice = float(155 + random(15)) / 100;
	printf("Updated gas price to $%s", FormatMoney(gasPrice));
}