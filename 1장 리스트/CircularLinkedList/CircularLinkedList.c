#include "CircularLinkedList.h"

// 노드 생성
Node* CDLL_CreateNode(ElementType NewData)
{
	Node* NewNode = (Node*)malloc(sizeof(Node));

	NewNode->Data = NewData;
	NewNode->PrevNode = NULL;
	NewNode->NextNode = NULL;

	return NewNode;
}

// 노드 소멸
void CDLL_DestroyNode(Node* Destroy)
{
	free(Destroy);
}

// 노드 추가
void CDLL_AppendNode(Node** Head, Node* NewNode)
{
	if ((*Head) == NULL)  // 빈 리스트라면
	{
		NewNode->NextNode = NewNode;
		NewNode->PrevNode = NewNode;
		*Head = NewNode;
	}
	else // 노드가 있다면
	{
		Node* Tail = (*Head)->PrevNode;

		NewNode->PrevNode = Tail;
		NewNode->NextNode = *Head;
		Tail->NextNode = NewNode;
		(*Head)->PrevNode = NewNode;
	}
}

// 노드 삽입
void CDLL_InsertAfter(Node* Before, Node* NewNode)
{
	NewNode->NextNode = Before->NextNode;
	NewNode->PrevNode = Before;
	
	if (Before->NextNode != NULL)
	{
		NewNode->NextNode->PrevNode = NewNode;
		Before->NextNode = NewNode;
	}
}

// 노드 제거
void CDLL_RemoveNode(Node** Head, Node* Remove)
{
	Node* Before = Remove->PrevNode;
	Node* After = Remove->NextNode;

	After->PrevNode = Before;
	Before->NextNode = After;
	
	if ((*Head) == Remove)
	{
		if (After == Remove) // 단일 노드
		{
			*Head = NULL;
		}
		else // 여러 노드
		{
			*Head = After;
		}
	}

	Remove->NextNode = NULL;
	Remove->PrevNode = NULL;
}

// 노드 탐색
Node* CDLL_GetNodeAt(Node* Head, int index)
{
	Node* Current = Head;

	// 만약 리스트 길이를 넘는 index를 입력 시 항상 마지막 노드 반환
	while (Current->NextNode != Head && (--index >= 0))  
	{
		Current = Current->NextNode;
	}

	return Current;
}

// 노드 개수 세기
int CDLL_GetNodeCount(Node* Head)
{
	if (Head == NULL) return 0;  // 빈 리스트
	
	Node* Current = Head;
	int cnt = 1;  // 위 조건으로 Head가 있음을 알 수 있음

	while (Current->NextNode != Head)
	{
		Current = Current->NextNode;
		cnt++;
	}

	return cnt;
}

// 노드 전체 출력
void CDLL_PrintNode(Node* Head)
{
	Node* Current = Head;
	int i = 0;

	if (Current != NULL)
	{
		do {
			printf("CDLL[%d]: %d\n", i, Current->Data);
			Current = Current->NextNode;
			i++;
		} while (Current != Head);
	}
}