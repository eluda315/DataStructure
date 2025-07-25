#include "DoublyLinkedList.h"

// 노드 생성
Node* DLL_CreateNode(ElementType data)
{
	Node* NewNode = (Node*)malloc(sizeof(Node));

	NewNode->Data = data;
	NewNode->PrevNode = NULL;
	NewNode->NextNode = NULL;

	return NewNode;
}

// 노드 소멸
void DLL_DestroyNode(Node* destroy)
{
	free(destroy);
}

// 노드 추가
void DLL_AppendNode(Node** Head, Node* NewNode)
{
	if ((*Head) == NULL)
	{
		*Head = NewNode;
	}
	else
	{
		Node* Tail = *Head;
		while (Tail->NextNode != NULL)
		{
			Tail = Tail->NextNode;
		}
		Tail->NextNode = NewNode;
		NewNode->PrevNode = Tail;
	}
}

// 노드 뒤에 삽입
void DLL_InsertAfter(Node* Current, Node* NewNode)
{
	Node* After = Current->NextNode; // 미리 다음 노드 저장

	// Current 뒤에 NewNode 연결
	Current->NextNode = NewNode;
	NewNode->PrevNode = Current;
	NewNode->NextNode = NULL; // 혹시 모를 사태를 위한 NULL처리(공통)

	if (After != NULL)  // 즉, Current가 Tail이 아니면 After를 NewNode와 연결
	{
		After->PrevNode = NewNode;
		NewNode->NextNode = After;
	}
}

// 노드 제거
void DLL_RemoveNode(Node** Head, Node* Remove)
{
	Node* Before = Remove->PrevNode;
	Node* After = Remove->NextNode;

	// Remove가 Head인 경우
	if (*Head == Remove)
	{
		*Head = After;
		if (After != NULL)
		{
			After->PrevNode = NULL;
		}
	}
	else
	{
		if (Before != NULL) Before->NextNode = After;
		if (After != NULL) After->PrevNode = Before;
	}

	// Remove 포인터 초기화 (안전한 상태로 분리)
	Remove->PrevNode = NULL;
	Remove->NextNode = NULL;
}

// 노드 탐색
Node* DLL_GetNodeAt(Node* Head, int index)
{
	Node* Current = Head;
	while (Current != NULL && (--index) >= 0)
	{
		Current = Current->NextNode;
	}

	return Current;
}

// 노드 개수 세기
int DLL_GetNodeCount(Node* Head)
{
	Node* Current = Head;
	int cnt = 0;

	while (Current != NULL)
	{
		Current = Current->NextNode;
		cnt++;
	}
	return cnt;
}