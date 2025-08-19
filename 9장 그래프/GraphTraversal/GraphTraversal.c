#include "GraphTraversal.h"

void DFS(Vertex* V)
{
	Edge* E = NULL;

	printf("%d ", V->Data);

	V->Visited = Visited;  // �湮�� ������ '�湮����'�̶�� ǥ��

	E = V->AdjacencyList;

	while (E != NULL) // ���� ������ ��� ���� ������ ���� DFS()�� ��� ȣ��
	{
		if (E->Target != NULL && E->Target->Visited == NotVisited)
			DFS(E->Target);  // ���� ������ �������� �ٽ� ���� �켱 Ž�� ����

		E = E->Next;
	}
}

void BFS(Vertex* V, LinkedQueue* Queue)
{
	Edge* E = NULL;

	printf("%d ", V->Data); 
	V->Visited = Visited;

	LQ_Enqueue(Queue, LQ_CreateNode(V));  // ���� ������ ť�� ����

	while (!LQ_IsEmpty(Queue)) // ť�� ����ִ��� �˻�
	{
		Node* Popped = LQ_Dequeue(Queue); // ť���� ���� ����
		V = Popped->Data;
		E = V->AdjacencyList;

		while (E != NULL)  // ť���� ���� ������ ���� ������ ����
		{
			V = E->Target;

			if (V != NULL && V->Visited == NotVisited)  // �̹湮 ������ �湮
			{
				printf("%d ", V->Data);
				V->Visited = Visited;
				LQ_Enqueue(Queue, LQ_CreateNode(V));
			}
			E = E->Next;
		}
	}
}