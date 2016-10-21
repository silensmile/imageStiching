int max(int *a)
{
	int length = sizeof(a);
	int max = a[0];
	for (int i = 0; i < length; i++)
		max = (a[i] > max) ? a[i] : max;
	return max;
}