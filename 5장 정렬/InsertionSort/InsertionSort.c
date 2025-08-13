#include <stdio.h>

// 내 답안(교과서적인 삽입 정렬이라고 한다^^)
void MyInsertionSort(int DataSet[], int Length)
{
	for (int i = 0; i < Length - 1; i++)
	{
		for (int j = i + 1; j > 0; j--)
		{
			if (DataSet[j] < DataSet[j - 1])
			{
				int temp = DataSet[j];
				DataSet[j] = DataSet[j - 1];
				DataSet[j - 1] = temp;
			}
			else break;
		}
	}
}

// 책 코드
void BookInsertionSort(int DataSet[], int Length)
{
    int i = 0;
    int j = 0;
    int value = 0;

    for (i = 1; i < Length; i++)
    {
        if (DataSet[i - 1] <= DataSet[i]) // 이미 정렬된 경우 패스
            continue;

        value = DataSet[i]; // 현재 값 설정
        
        for (j = 0; j < i; j++) // 앞에서부터 삽입 위치 찾기
        {
            if (DataSet[j] > value) // 위치 발견
            {
                // memmove(원본 데이터가 옮겨갈 새로운 메모리의 주소, 원본 데이터가 있는 주소, 이동시킬 데이터의 양)
                memmove(&DataSet[j + 1], &DataSet[j], sizeof(DataSet[0]) * (i - j));
                DataSet[j] = value;
                break;
            }
        }
    }
}

int main(void)
{
    int DataSet[] = { 6, 4, 2, 3, 1, 5 };
    int Length = sizeof DataSet / sizeof DataSet[0];
    int i = 0;

    MyInsertionSort(DataSet, Length);

    for (i = 0; i < Length; i++)
    {
        printf("%d ", DataSet[i]);
    }

    printf("\n");

    return 0;

}