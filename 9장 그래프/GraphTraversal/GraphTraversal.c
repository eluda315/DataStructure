#include "GraphTraversal.h"

void DFS(Vertex* V)
{
	Edge* E = NULL;

	printf("%d ", V->Data);

	V->Visited = Visited;  // 방문한 정점에 '방문했음'이라고 표시

	E = V->AdjacencyList;

	while (E != NULL) // 현재 정점의 모든 인접 정점에 대해 DFS()를 재귀 호출
	{
		if (E->Target != NULL && E->Target->Visited == NotVisited)
			DFS(E->Target);  // 인접 정점을 시작으로 다시 깊이 우선 탐색 수행

		E = E->Next;
	}
}

void BFS(Vertex* V, LinkedQueue* Queue)
{
	Edge* E = NULL;

	printf("%d ", V->Data); 
	V->Visited = Visited;

	LQ_Enqueue(Queue, LQ_CreateNode(V));  // 시작 정점을 큐에 삽입

	while (!LQ_IsEmpty(Queue)) // 큐가 비어있는지 검사
	{
		Node* Popped = LQ_Dequeue(Queue); // 큐에서 전단 제거
		V = Popped->Data;
		E = V->AdjacencyList;

		while (E != NULL)  // 큐에서 꺼낸 정점의 인접 정점을 조사
		{
			V = E->Target;

			if (V != NULL && V->Visited == NotVisited)  // 미방문 정점만 방문
			{
				printf("%d ", V->Data);
				V->Visited = Visited;
				LQ_Enqueue(Queue, LQ_CreateNode(V));
			}
			E = E->Next;
		}
	}
}