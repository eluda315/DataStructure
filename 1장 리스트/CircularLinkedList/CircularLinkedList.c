#include "CircularLinkedList.h"

// ��� ����
Node* CDLL_CreateNode(ElementType NewData)
{
	Node* NewNode = (Node*)malloc(sizeof(Node));

	NewNode->Data = NewData;
	NewNode->PrevNode = NULL;
	NewNode->NextNode = NULL;

	return NewNode;
}

// ��� �Ҹ�
void CDLL_DestroyNode(Node* Destroy)
{
	free(Destroy);
}

// ��� �߰�
void CDLL_AppendNode(Node** Head, Node* NewNode)
{
	if ((*Head) == NULL)  // �� ����Ʈ���
	{
		NewNode->NextNode = NewNode;
		NewNode->PrevNode = NewNode;
		*Head = NewNode;
	}
	else // ��尡 �ִٸ�
	{
		Node* Tail = (*Head)->PrevNode;

		NewNode->PrevNode = Tail;
		NewNode->NextNode = *Head;
		Tail->NextNode = NewNode;
		(*Head)->PrevNode = NewNode;
	}
}

// ��� ����
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

// ��� ����
void CDLL_RemoveNode(Node** Head, Node* Remove)
{
	Node* Before = Remove->PrevNode;
	Node* After = Remove->NextNode;

	After->PrevNode = Before;
	Before->NextNode = After;
	
	if ((*Head) == Remove)
	{
		if (After == Remove) // ���� ���
		{
			*Head = NULL;
		}
		else // ���� ���
		{
			*Head = After;
		}
	}

	Remove->NextNode = NULL;
	Remove->PrevNode = NULL;
}

// ��� Ž��
Node* CDLL_GetNodeAt(Node* Head, int index)
{
	Node* Current = Head;

	// ���� ����Ʈ ���̸� �Ѵ� index�� �Է� �� �׻� ������ ��� ��ȯ
	while (Current->NextNode != Head && (--index >= 0))  
	{
		Current = Current->NextNode;
	}

	return Current;
}

// ��� ���� ����
int CDLL_GetNodeCount(Node* Head)
{
	if (Head == NULL) return 0;  // �� ����Ʈ
	
	Node* Current = Head;
	int cnt = 1;  // �� �������� Head�� ������ �� �� ����

	while (Current->NextNode != Head)
	{
		Current = Current->NextNode;
		cnt++;
	}

	return cnt;
}

// ��� ��ü ���
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