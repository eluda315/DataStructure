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
	int CurrentPosition = H->UsedSize; // 최고 깊이 맨 우측의 인덱스 저장
	int ParentPosition = HEAP_GetParent(CurrentPosition);

	// 용량 부족 시 2배 늘리기
	if (H->Capacity == H->UsedSize)
	{
		H->Capacity *= 2;
		H->Nodes = (HeapNode*)realloc(H->Nodes, sizeof(HeapNode) * H->Capacity); // 공간 재할당
	}

	H->Nodes[CurrentPosition].Data = NewData; // 새 노드의 데이터 저장

	// 삽입 후 뒤처리
	// 뿌리 노드가 되거나 힙 순서 속성이 지켜질 때까지
	while (CurrentPosition > 0 && (H->Nodes[CurrentPosition].Data < H->Nodes[ParentPosition].Data))
	{
		HEAP_SwapNodes(H, CurrentPosition, ParentPosition);
		CurrentPosition = ParentPosition;
		ParentPosition = HEAP_GetParent(CurrentPosition);
	}

	H->UsedSize++; // 사용한 노드 1개 증가
}

void HEAP_DeleteMin(Heap* H, HeapNode* Root)
{
	memcpy(Root, &H->Nodes[0], sizeof(HeapNode)); // 삭제할 최솟값을 Root 매개변수에 복사하여 백업
	memset(&H->Nodes[0], 0, sizeof(HeapNode)); // 원래 루트 노드의 데이터를 0으로 초기화(선택사항)
	
	int ParentPosition = 0;
	int LeftPosition = HEAP_GetLeftChild(0);
	int RightPosition = LeftPosition + 1;

	H->UsedSize--;
	HEAP_SwapNodes(H, 0, H->UsedSize); // 마지막 노드를 루트로 이동

	while (1) // 힙 속성 복원
	{
		int SelectedChild = 0;

		// 자식 노드가 없다면(잎 노드라면) 종료
		if (LeftPosition >= H->UsedSize) break;

		// 왼쪽 자식만 있다면
		if (RightPosition >= H->UsedSize) SelectedChild = LeftPosition;
		else 
		{
			// 양쪽 자식이 다 있다면 둘 중 작은 걸 선택
			if (H->Nodes[LeftPosition].Data > H->Nodes[RightPosition].Data) SelectedChild = RightPosition;
			else SelectedChild = LeftPosition;
		}

		// 부모vs자식: 자식이 더 작으면 교환, 아니면 힙 속성 만족으로 종료
		if (H->Nodes[SelectedChild].Data < H->Nodes[ParentPosition].Data)
		{
			HEAP_SwapNodes(H, SelectedChild, ParentPosition);
			ParentPosition = SelectedChild; // 타멧이 한 레벨 내려갔으니 부모위치 갱신
			LeftPosition = HEAP_GetLeftChild(ParentPosition); // 자식 위치도 갱신
			RightPosition = LeftPosition + 1;
		}
		else break;

		// 메모리 재조정(선택사항)
		// 힙에 데이터가 계속 삭제되어 배열 공간이 너무 많이 남게 되면 메모리 절반으로 줄이기
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

// 처음 내 답안. 현재 Data 하나만 가지고 있는 구조체에선 괜찮음. but! 멤버를 추가할 시를 대비하면 모범답안이 더 굿
void HEAP_SwapNodes(Heap* H, int Index1, int Index2)
{
	int temp = H->Nodes[Index1].Data;
	H->Nodes[Index1].Data = H->Nodes[Index2].Data;
	H->Nodes[Index2].Data = temp;
}

// 모범답안(노드를 통째로 교환)
//void HEAP_SwapNodes(Heap* H, int Index1, int Index2)
//{
//	int CopySize = sizeof(HeapNode);
//	HeapNode* Temp = (HeapNode*)malloc(CopySize);
//
//  // memcpy를 이용해 세 단계로 노드를 교환합니다. (메모리 복사)
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