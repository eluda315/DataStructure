#include "Point.h"

int ComparePoint(const void* _elem1, const void* _elem2)
{
	int* elem1 = (int*)_elem1;
	int* elem2 = (int*)_elem2;

	if (*elem1 > *elem2) return 1;
	else if (*elem1 < *elem2) return -1;
	else return 0;
}

int main(void)
{
	int Length = sizeof(DataSet) / sizeof(DataSet[0]);
	
	qsort((void*)DataSet, Length, sizeof(int), ComparePoint);

	printf("14142번째 고객의 ID: %d\n", DataSet[14142].id);
	printf("14142번째 고객의 구매포인트: %f\n", DataSet[14142].point);

	return 0;
}