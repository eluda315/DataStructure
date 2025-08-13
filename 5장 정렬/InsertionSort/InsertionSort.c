#include <stdio.h>

// �� ���(���������� ���� �����̶�� �Ѵ�^^)
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

// å �ڵ�
void BookInsertionSort(int DataSet[], int Length)
{
    int i = 0;
    int j = 0;
    int value = 0;

    for (i = 1; i < Length; i++)
    {
        if (DataSet[i - 1] <= DataSet[i]) // �̹� ���ĵ� ��� �н�
            continue;

        value = DataSet[i]; // ���� �� ����
        
        for (j = 0; j < i; j++) // �տ������� ���� ��ġ ã��
        {
            if (DataSet[j] > value) // ��ġ �߰�
            {
                // memmove(���� �����Ͱ� �Űܰ� ���ο� �޸��� �ּ�, ���� �����Ͱ� �ִ� �ּ�, �̵���ų �������� ��)
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