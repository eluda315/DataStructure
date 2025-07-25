#include "DoublyLinkedList.h"

// ��� ����
Node* DLL_CreateNode(ElementType data)
{
	Node* NewNode = (Node*)malloc(sizeof(Node));

	NewNode->Data = data;
	NewNode->PrevNode = NULL;
	NewNode->NextNode = NULL;

	return NewNode;
}

// ��� �Ҹ�
void DLL_DestroyNode(Node* destroy)
{
	free(destroy);
}

// ��� �߰�
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

// ��� �ڿ� ����
void DLL_InsertAfter(Node* Current, Node* NewNode)
{
	Node* After = Current->NextNode; // �̸� ���� ��� ����

	// Current �ڿ� NewNode ����
	Current->NextNode = NewNode;
	NewNode->PrevNode = Current;
	NewNode->NextNode = NULL; // Ȥ�� �� ���¸� ���� NULLó��(����)

	if (After != NULL)  // ��, Current�� Tail�� �ƴϸ� After�� NewNode�� ����
	{
		After->PrevNode = NewNode;
		NewNode->NextNode = After;
	}
}

// ��� ����
void DLL_RemoveNode(Node** Head, Node* Remove)
{
	Node* Before = Remove->PrevNode;
	Node* After = Remove->NextNode;

	// Remove�� Head�� ���
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

	// Remove ������ �ʱ�ȭ (������ ���·� �и�)
	Remove->PrevNode = NULL;
	Remove->NextNode = NULL;
}

// ��� Ž��
Node* DLL_GetNodeAt(Node* Head, int index)
{
	Node* Current = Head;
	while (Current != NULL && (--index) >= 0)
	{
		Current = Current->NextNode;
	}

	return Current;
}

// ��� ���� ����
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