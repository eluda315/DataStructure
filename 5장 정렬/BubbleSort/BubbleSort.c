#include <stdio.h>

void BubbleSort(int DataSet[], int Length)
{
	for (int i = 0; i < Length - 1; i++) // 전체 반복 횟수
	{
		for (int j = 0; j < Length - 1 - i; j++) // 비교하는 직접적인 범위
		{
			if (DataSet[j] > DataSet[j + 1]) // 스왑
			{
				int temp = DataSet[j];
				DataSet[j] = DataSet[j + 1];
				DataSet[j + 1] = temp;
			}
		}
	}
}

int main(void)
{
	int DataSet[] = { 6,4,2,3,1,5 };
	int Length = sizeof(DataSet) / sizeof(DataSet[0]);

	BubbleSort(DataSet, Length);

	for (int i = 0; i < Length; i++)
	{
		printf("%d ", DataSet[i]);
	}
	printf("\n");

	return 0;
}