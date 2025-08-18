#include "Heap.h"

Heap* HEAP_Create(int InitialSize)
{
	Heap* H = (Heap*)malloc(sizeof(Heap));

	H->Capacity = InitialSize;
	H->UsedSize = 0;
	H->Nodes = (HeapNode*)malloc(sizeof(HeapNode) * H->Capacity);

	printf("size: %d\n", sizeof(HeapNode));

	return H;
}

void HEAP_Destroy(Heap* H)
{
	free(H->Nodes);
	free(H);
}

void HEAP_Insert(Heap* H, ElementType NewData)
{
	int CurrentPosition = H->UsedSize; // �ְ� ���� �� ������ �ε��� ����
	int ParentPosition = HEAP_GetParent(CurrentPosition);

	// �뷮 ���� �� 2�� �ø���
	if (H->Capacity == H->UsedSize)
	{
		H->Capacity *= 2;
		H->Nodes = (HeapNode*)realloc(H->Nodes, sizeof(HeapNode) * H->Capacity); // ���� ���Ҵ�
	}

	H->Nodes[CurrentPosition].Data = NewData; // �� ����� ������ ����

	// ���� �� ��ó��
	// �Ѹ� ��尡 �ǰų� �� ���� �Ӽ��� ������ ������
	while (CurrentPosition > 0 && (H->Nodes[CurrentPosition].Data < H->Nodes[ParentPosition].Data))
	{
		HEAP_SwapNodes(H, CurrentPosition, ParentPosition);
		CurrentPosition = ParentPosition;
		ParentPosition = HEAP_GetParent(CurrentPosition);
	}

	H->UsedSize++; // ����� ��� 1�� ����
}

void HEAP_DeleteMin(Heap* H, HeapNode* Root)
{
	memcpy(Root, &H->Nodes[0], sizeof(HeapNode)); // ������ �ּڰ��� Root �Ű������� �����Ͽ� ���
	memset(&H->Nodes[0], 0, sizeof(HeapNode)); // ���� ��Ʈ ����� �����͸� 0���� �ʱ�ȭ(���û���)
	
	int ParentPosition = 0;
	int LeftPosition = HEAP_GetLeftChild(0);
	int RightPosition = LeftPosition + 1;

	H->UsedSize--;
	HEAP_SwapNodes(H, 0, H->UsedSize); // ������ ��带 ��Ʈ�� �̵�

	while (1) // �� �Ӽ� ����
	{
		int SelectedChild = 0;

		// �ڽ� ��尡 ���ٸ�(�� �����) ����
		if (LeftPosition >= H->UsedSize) break;

		// ���� �ڽĸ� �ִٸ�
		if (RightPosition >= H->UsedSize) SelectedChild = LeftPosition;
		else 
		{
			// ���� �ڽ��� �� �ִٸ� �� �� ���� �� ����
			if (H->Nodes[LeftPosition].Data > H->Nodes[RightPosition].Data) SelectedChild = RightPosition;
			else SelectedChild = LeftPosition;
		}

		// �θ�vs�ڽ�: �ڽ��� �� ������ ��ȯ, �ƴϸ� �� �Ӽ� �������� ����
		if (H->Nodes[SelectedChild].Data < H->Nodes[ParentPosition].Data)
		{
			HEAP_SwapNodes(H, SelectedChild, ParentPosition);
			ParentPosition = SelectedChild; // Ÿ���� �� ���� ���������� �θ���ġ ����
			LeftPosition = HEAP_GetLeftChild(ParentPosition); // �ڽ� ��ġ�� ����
			RightPosition = LeftPosition + 1;
		}
		else break;

		// �޸� ������(���û���)
		// ���� �����Ͱ� ��� �����Ǿ� �迭 ������ �ʹ� ���� ���� �Ǹ� �޸� �������� ���̱�
		if (H->UsedSize < (H->Capacity / 2))
		{
			H->Capacity /= 2;
			H->Nodes = (HeapNode*)realloc(H->Nodes, sizeof(HeapNode) * H->Capacity);
		}
	}
}

int HEAP_GetParent(int Index)
{
	return (int)((Index - 1) / 2);
}

int HEAP_GetLeftChild(int Index)
{
	return (2 * Index) + 1;
}

// ó�� �� ���. ���� Data �ϳ��� ������ �ִ� ����ü���� ������. but! ����� �߰��� �ø� ����ϸ� �������� �� ��
void HEAP_SwapNodes(Heap* H, int Index1, int Index2)
{
	int temp = H->Nodes[Index1].Data;
	H->Nodes[Index1].Data = H->Nodes[Index2].Data;
	H->Nodes[Index2].Data = temp;
}

// ������(��带 ��°�� ��ȯ)
//void HEAP_SwapNodes(Heap* H, int Index1, int Index2)
//{
//	int CopySize = sizeof(HeapNode);
//	HeapNode* Temp = (HeapNode*)malloc(CopySize);
//
//  // memcpy�� �̿��� �� �ܰ�� ��带 ��ȯ�մϴ�. (�޸� ����)
//	memcpy(Temp, &H->Nodes[Index1], CopySize);
//	memcpy(&H->Nodes[Index1], &H->Nodes[Index2], CopySize);
//	memcpy(&H->Nodes[Index2], Temp, CopySize);
//
//	free(Temp);
//}

void HEAP_PrintNodes(Heap* H)
{
	for (int i = 0; i < H->UsedSize; i++)
	{
		printf("%d ", H->Nodes[i].Data);
	}
	printf("\n");
}