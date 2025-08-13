#include <stdio.h>

void Swap(int* A, int* B)
{
	int Temp = *A;
	*A = *B;
	*B = Temp;
}

int Partition(int DataSet[], int Left, int Right)
{
	int First = Left;
	int Pivot = DataSet[First]; // 기준을 첫 번째 요소로 설정
	++Left;

	while (Left <= Right)
	{
		while (DataSet[Left] <= Pivot && Left < Right) ++Left;
		while (DataSet[Right] >= Pivot && Left <= Right) --Right;
		
		if (Left < Right) Swap(&DataSet[Left], &DataSet[Right]);
		else break;
	}

	// 왼쪽 그룹 마지막 요소와 기준을 swap
	Swap(&DataSet[First], &DataSet[Right]);

	return Right; // 기준이 있는 인덱스 반환
}

void QuickSort(int DataSet[], int Left, int Right)
{
	if (Left < Right)
	{
		int Index = Partition(DataSet, Left, Right); // 나누어진 기준 인덱스 반환받아서

		// 다시 새로운 기준을 중심으로 왼,오 정렬
		QuickSort(DataSet, Left, Index - 1); // 왼쪽그룹 정렬
		QuickSort(DataSet, Index + 1, Right); // 오른쪽 그룹 정렬
	}
}

int main(void)
{
	int DataSet[] = { 6, 4, 2, 3, 1, 5 };
	int Length = sizeof DataSet / sizeof DataSet[0];
	int i = 0;

	QuickSort(DataSet, 0, Length - 1);

	for (i = 0; i < Length; i++)
	{
		printf("%d ", DataSet[i]);
	}

	printf("\n");

	return 0;

}