void BubbleSort(int a[], int aSize) 
{
	int i, j, temp;
	for (i = 0; i < aSize - 1; ++i)          
		for (j = 0; j < aSize - 1 - i; ++j)  
			if (a[j] > a[j + 1])       
			{
                // swap 
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
}