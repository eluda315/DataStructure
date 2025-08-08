#include "LinkedQueue.h"

void LQ_CreateQueue(LinkedQueue** Queue)
{
	(*Queue) = (LinkedQueue*)malloc(sizeof(LinkedQueue));

	(*Queue)->Front = NULL;
	(*Queue)->Rear = NULL;
	(*Queue)->size = 0;
}

void LQ_DestroyQueue(LinkedQueue* Queue)
{
	while (!LQ_IsEmpty(Queue))
	{
		Node* Popped = LQ_Dequeue(Queue);
		LQ_DestroyNode(Popped);
	}

	free(Queue);
}

Node* LQ_CreateNode(char* Data)
{
	Node* NewNode = (Node*)malloc(sizeof(Node));

	NewNode->Data = (char*)malloc(strlen(Data) + 1);
	strcpy(NewNode->Data, Data);
	NewNode->NextNode = NULL;

	return NewNode;
}

void LQ_DestroyNode(Node* _Node)
{
	free(_Node->Data);  // ���ڿ� �����͵� ����
	free(_Node);
}

void LQ_Enqueue(LinkedQueue* Queue, Node* NewNode)
{
	if (Queue->Front == NULL) // �� ť�̸�
	{
		Queue->Front = NewNode;
		Queue->Rear = NewNode;
	}
	else // ��� �����ϸ�
	{
		Queue->Rear->NextNode = NewNode;
		Queue->Rear = NewNode; // �Ĵ� ����
	}
	Queue->size++;
}

Node* LQ_Dequeue(LinkedQueue* Queue)
{
	Node* Popped = Queue->Front; // ���� �̸� ����
	
	if (Queue->size == 0) // �� ť��
	{
		printf("! Queue is empty !\n");
		return NULL;  // ��������� NULL ��ȯ
	}
	else if (Queue->size == 1) // ���� ����
	{
		Queue->Front = NULL;
		Queue->Rear = NULL;
		Queue->size--;
	}
	else // ���� ��� ����
	{
		Queue->Front = Queue->Front->NextNode; // ���� ����
		Queue->size--;
	}

	return Popped;
}

int LQ_IsEmpty(LinkedQueue* Queue)
{
	return (Queue->Front == NULL);
}