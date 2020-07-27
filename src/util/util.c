int get_digit_number(int num)
{
	int i;
	if (num < 0)
		num = num * (-1);
	for (i = 0; num / 10 != 0; i++) {
		num /= 10;
	}
	return i + 1;
}
