#include "RedBlackTree.h"
#include <string.h>

extern RBTNode* Nil;

RBTNode* RBT_CreateNode(ElementType NewData)
{
	RBTNode* NewNode = (RBTNode*)malloc(sizeof(RBTNode));

	NewNode->Data = NewData;
	NewNode->Parent = NULL;
	NewNode->Left = NULL;
	NewNode->Right = NULL;
	NewNode->Color = BLACK;

	return NewNode;
}

void RBT_DestroyNode(RBTNode* Node)
{
	free(Node);
}

void RBT_DestroyTree(RBTNode* Tree)
{
	if (Tree->Right != Nil)
		RBT_DestroyTree(Tree->Right);

	if (Tree->Left != Nil)
		RBT_DestroyTree(Tree->Left);

	Tree->Left = Nil;
	Tree->Right = Nil;

	RBT_DestroyNode(Tree);
}

RBTNode* RBT_SearchNode(RBTNode* Tree, ElementType Target)
{
	if (Tree == Nil)
		return NULL;

	if (Tree->Data > Target)
		return RBT_SearchNode(Tree->Left, Target);
	else if (Tree->Data < Target)
		return RBT_SearchNode(Tree->Right, Target);
	else
		return Tree;
}

RBTNode* RBT_SearchMinNode(RBTNode* Tree)
{
	if (Tree == Nil)
		return Nil;

	if (Tree->Left == Nil)
		return Tree;
	else
		return RBT_SearchMinNode(Tree->Left);
}

void RBT_InsertNode(RBTNode** Tree, RBTNode* NewNode)
{
	RBT_InsertNodeHelper(Tree, NewNode);  // 이진 탐색 트리의 노드 삽입을 수행

	// 새 노드는 빨간색으로 칠하고 Nil을 양쪽 자식으로 연결
	NewNode->Color = RED;
	NewNode->Left = Nil;
	NewNode->Right = Nil;

	RBT_RebuildAfterInsert(Tree, NewNode); // 무너진 레드 블랙 트리 규칙 바로잡기
}

void RBT_InsertNodeHelper(RBTNode** Tree, RBTNode* NewNode)
{
	if ((*Tree) == NULL)
		(*Tree) = NewNode;

	if ((*Tree)->Data < NewNode->Data)
	{
		if ((*Tree)->Right == Nil)
		{
			(*Tree)->Right = NewNode;
			NewNode->Parent = (*Tree);
		}
		else
			RBT_InsertNodeHelper(&(*Tree)->Right, NewNode);

	}
	else if ((*Tree)->Data > NewNode->Data)
	{
		if ((*Tree)->Left == Nil)
		{
			(*Tree)->Left = NewNode;
			NewNode->Parent = (*Tree);
		}
		else
			RBT_InsertNodeHelper(&(*Tree)->Left, NewNode);
	}
}

RBTNode* RBT_RemoveNode(RBTNode** Root, ElementType Data)
{
	RBTNode* Removed = NULL; // 물리적으로 연결이 끊어질 노드
	RBTNode* Successor = NULL; // 삭제된 자리에 대체될 노드
	RBTNode* Target = RBT_SearchNode((*Root), Data); // 삭제할 노드

	if (Target == NULL) return NULL;

	// 자식이 없거나 한 개인 경우 직접 제거
	if (Target->Left == Nil || Target->Right == Nil) Removed = Target;
	else // 양쪽 자식이 다 있는 경우
	{
		Removed = RBT_SearchMinNode(Target->Right);
		Target->Data = Removed->Data;
	}
	// 이 과정 후 Removed의 자식은 무조건 1개 이하가 됨.

	if (Removed->Left != Nil) Successor = Removed->Left;
	else Successor = Removed->Right;
	Successor->Parent = Removed->Parent;

	if (Removed->Parent == NULL) (*Root) = Successor;
	else
	{
		if (Removed == Removed->Parent->Left) Removed->Parent->Left = Successor;
		else Removed->Parent->Right = Successor;
	}

	if (Removed->Color == BLACK) RBT_RebuildAfterRemove(Root, Successor);

	return Removed;
}

void RBT_RebuildAfterInsert(RBTNode** Tree, RBTNode* NewNode)
{
	// 4번 규칙을 위반하는 동안 계속 반복
	// 위반 조건: NewNode가 뿌리가 아니면서 부모가 빨간색인 경우
	while (NewNode != (*Tree) && NewNode->Parent->Color == RED)
	{
		// 부모 노드가 할아버지 노드의 왼쪽 자식인 경우
		if (NewNode->Parent == NewNode->Parent->Parent->Left)
		{
			RBTNode* Uncle = NewNode->Parent->Parent->Right;

			// 1. 삼촌도 빨간색인 경우
			if (Uncle->Color == RED)
			{
				// 부모, 삼촌: 검, 할아버지: 빨강을 색 변경
				NewNode->Parent->Color = BLACK;
				Uncle->Color = BLACK;
				NewNode->Parent->Parent->Color = RED;

				NewNode = NewNode->Parent->Parent; // 할아버지 기준으로 계속 4번 규칙 위반 뒤처리 반복
			}
			else
			{
				// 2. 삼촌이 검은색이면서 새로 삽입한 노드가 부모의 오른쪽 자식인 경우
				if (NewNode == NewNode->Parent->Right)
				{
					// 부모 기준 좌회전해서 3번 경우로 바꾸기
					RBT_RotateLeft(Tree, NewNode->Parent);
				}
				// 3. 삼촌이 검은색이면서 새로 삽입한 노드가 부모의 왼쪽 자식인 경우
				// 부모: 검, 할아버지: 빨강으로 색깔 변경 후 할아버지 기준 우회전
				NewNode->Parent->Color = BLACK;
				NewNode->Parent->Parent->Color = RED;
				RBT_RotateRight(Tree, NewNode->Parent->Parent);
			}
		}
		else // 부모 노드가 할아버지 노드의 오른쪽 자식인 경우: 왼<->오
		{
			RBTNode* Uncle = NewNode->Parent->Parent->Left;

			if (Uncle->Color == RED)
			{
				NewNode->Parent->Parent->Color = RED;
				NewNode->Parent->Color = BLACK;
				Uncle->Color = BLACK;

				NewNode = NewNode->Parent->Parent;
			}
			else
			{
				if (NewNode == NewNode->Parent->Left)
				{
					RBT_RotateRight(Tree, NewNode->Parent);
				}
				NewNode->Parent->Color = BLACK;
				NewNode->Parent->Parent->Color = RED;
				RBT_RotateLeft(Tree, NewNode->Parent->Parent);
			}
		}
	}

	// 공통적으로 뿌리 노드 검은색 처리
	(*Tree)->Color = BLACK;
}

void RBT_RebuildAfterRemove(RBTNode** Root, RBTNode* Successor)
{
	RBTNode* Sibling = NULL;

	// 뿌리 노드이거나 빨간색 노드로 검은색이 넘어가면 루프 종료
	while (Successor->Parent != NULL && Successor->Color == BLACK)
	{
		if (Successor == Successor->Parent->Left)
		{
			// 이중 흑색 노드가 부모 노드의 왼쪽 자식인 경우
			Sibling = Successor->Parent->Right;

			if (Sibling->Color == RED) // 1. 형제가 빨간색인 경우
			{
				Sibling->Color = BLACK;
				Successor->Parent->Color = RED;
				RBT_RotateLeft(Root, Successor->Parent);
			}
			else // 2. 형제가 검은색이고
			{
				// (A). 양쪽 자식이 모두 검은색인 경우
				if (Sibling->Left->Color == BLACK && Sibling->Right->Color == BLACK)
				{
					Sibling->Color = RED;
					Successor = Successor->Parent;
				}
				else
				{
					// (B). 왼쪽 자식이 빨간색인 경우
					if (Sibling->Left->Color == RED)
					{
						Sibling->Left->Color = BLACK;
						Sibling->Color = RED;

						RBT_RotateRight(Root, Sibling);
						Sibling = Successor->Parent->Right;
					}
					// (C). 오른쪽 자식이 빨간색인 경우
					Sibling->Color = Successor->Parent->Color;
					Successor->Parent->Color = BLACK;
					Sibling->Right->Color = BLACK;
					RBT_RotateLeft(Root, Successor->Parent);
					Successor = (*Root);
				}
			}
		}
		else
		{
			// 이중 흑색 노드가 부모 노드의 오른쪽 자식인 경우: 오<->왼
			if (Sibling->Right->Color == BLACK &&
				Sibling->Left->Color == BLACK)
			{
				Sibling->Color = RED;
				Successor = Successor->Parent;
			}
			else
			{
				if (Sibling->Right->Color == RED)
				{
					Sibling->Right->Color = BLACK;
					Sibling->Color = RED;

					RBT_RotateLeft(Root, Sibling);
					Sibling = Successor->Parent->Left;
				}

				Sibling->Color = Successor->Parent->Color;
				Successor->Parent->Color = BLACK;
				Sibling->Left->Color = BLACK;
				RBT_RotateRight(Root, Successor->Parent);
				Successor = (*Root);
			}
		}
	}

	Successor->Color = BLACK;
}

void RBT_PrintTree(RBTNode* Node, int Depth, int BlackCount) 
{
	int   i = 0;
	char c = 'X';
	int  v = -1;
	char cnt[100];

	if (Node == NULL || Node == Nil)
		return;

	if (Node->Color == BLACK)
		BlackCount++;

	if (Node->Parent != NULL)
	{
		v = Node->Parent->Data;

		if (Node->Parent->Left == Node)
			c = 'L';
		else
			c = 'R';
	}

	if (Node->Left == Nil && Node->Right == Nil)
		sprintf(cnt, "--------- %d", BlackCount);
	else
		strncpy(cnt, "", sizeof(cnt));

	for (i = 0; i < Depth; i++)
		printf("  ");

	printf("%d %s [%c,%d] %s\n", Node->Data,
		(Node->Color == RED) ? "RED" : "BLACK", c, v, cnt);

	RBT_PrintTree(Node->Left, Depth + 1, BlackCount);
	RBT_PrintTree(Node->Right, Depth + 1, BlackCount);
}

void RBT_RotateLeft(RBTNode** Root, RBTNode* Parent)
{
	RBTNode* RightChild = Parent->Right;

	Parent->Right = RightChild->Left;

	if (RightChild->Left != Nil)
		RightChild->Left->Parent = Parent;

	RightChild->Parent = Parent->Parent;

	if (Parent->Parent == NULL)
		(*Root) = RightChild;
	else
	{
		if (Parent == Parent->Parent->Left)
			Parent->Parent->Left = RightChild;
		else
			Parent->Parent->Right = RightChild;
	}

	RightChild->Left = Parent;
	Parent->Parent = RightChild;
}

void RBT_RotateRight(RBTNode** Root, RBTNode* Parent)
{
	RBTNode* LeftChild = Parent->Left;
	Parent->Left = LeftChild->Right;

	if (LeftChild->Right != Nil) LeftChild->Right->Parent = Parent;

	LeftChild->Parent = Parent->Parent;

	if (Parent->Parent == NULL) (*Root) = LeftChild;
	else
	{
		if (Parent == Parent->Parent->Left) Parent->Parent->Left = LeftChild;
		else Parent->Parent->Left = LeftChild;
	}

	LeftChild->Right = Parent;
	Parent->Parent = LeftChild;
}