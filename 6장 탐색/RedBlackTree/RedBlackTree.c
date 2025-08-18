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
	RBT_InsertNodeHelper(Tree, NewNode);  // ���� Ž�� Ʈ���� ��� ������ ����

	// �� ���� ���������� ĥ�ϰ� Nil�� ���� �ڽ����� ����
	NewNode->Color = RED;
	NewNode->Left = Nil;
	NewNode->Right = Nil;

	RBT_RebuildAfterInsert(Tree, NewNode); // ������ ���� �� Ʈ�� ��Ģ �ٷ����
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
	RBTNode* Removed = NULL; // ���������� ������ ������ ���
	RBTNode* Successor = NULL; // ������ �ڸ��� ��ü�� ���
	RBTNode* Target = RBT_SearchNode((*Root), Data); // ������ ���

	if (Target == NULL) return NULL;

	// �ڽ��� ���ų� �� ���� ��� ���� ����
	if (Target->Left == Nil || Target->Right == Nil) Removed = Target;
	else // ���� �ڽ��� �� �ִ� ���
	{
		Removed = RBT_SearchMinNode(Target->Right);
		Target->Data = Removed->Data;
	}
	// �� ���� �� Removed�� �ڽ��� ������ 1�� ���ϰ� ��.

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
	// 4�� ��Ģ�� �����ϴ� ���� ��� �ݺ�
	// ���� ����: NewNode�� �Ѹ��� �ƴϸ鼭 �θ� �������� ���
	while (NewNode != (*Tree) && NewNode->Parent->Color == RED)
	{
		// �θ� ��尡 �Ҿƹ��� ����� ���� �ڽ��� ���
		if (NewNode->Parent == NewNode->Parent->Parent->Left)
		{
			RBTNode* Uncle = NewNode->Parent->Parent->Right;

			// 1. ���̵� �������� ���
			if (Uncle->Color == RED)
			{
				// �θ�, ����: ��, �Ҿƹ���: ������ �� ����
				NewNode->Parent->Color = BLACK;
				Uncle->Color = BLACK;
				NewNode->Parent->Parent->Color = RED;

				NewNode = NewNode->Parent->Parent; // �Ҿƹ��� �������� ��� 4�� ��Ģ ���� ��ó�� �ݺ�
			}
			else
			{
				// 2. ������ �������̸鼭 ���� ������ ��尡 �θ��� ������ �ڽ��� ���
				if (NewNode == NewNode->Parent->Right)
				{
					// �θ� ���� ��ȸ���ؼ� 3�� ���� �ٲٱ�
					RBT_RotateLeft(Tree, NewNode->Parent);
				}
				// 3. ������ �������̸鼭 ���� ������ ��尡 �θ��� ���� �ڽ��� ���
				// �θ�: ��, �Ҿƹ���: �������� ���� ���� �� �Ҿƹ��� ���� ��ȸ��
				NewNode->Parent->Color = BLACK;
				NewNode->Parent->Parent->Color = RED;
				RBT_RotateRight(Tree, NewNode->Parent->Parent);
			}
		}
		else // �θ� ��尡 �Ҿƹ��� ����� ������ �ڽ��� ���: ��<->��
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

	// ���������� �Ѹ� ��� ������ ó��
	(*Tree)->Color = BLACK;
}

void RBT_RebuildAfterRemove(RBTNode** Root, RBTNode* Successor)
{
	RBTNode* Sibling = NULL;

	// �Ѹ� ����̰ų� ������ ���� �������� �Ѿ�� ���� ����
	while (Successor->Parent != NULL && Successor->Color == BLACK)
	{
		if (Successor == Successor->Parent->Left)
		{
			// ���� ��� ��尡 �θ� ����� ���� �ڽ��� ���
			Sibling = Successor->Parent->Right;

			if (Sibling->Color == RED) // 1. ������ �������� ���
			{
				Sibling->Color = BLACK;
				Successor->Parent->Color = RED;
				RBT_RotateLeft(Root, Successor->Parent);
			}
			else // 2. ������ �������̰�
			{
				// (A). ���� �ڽ��� ��� �������� ���
				if (Sibling->Left->Color == BLACK && Sibling->Right->Color == BLACK)
				{
					Sibling->Color = RED;
					Successor = Successor->Parent;
				}
				else
				{
					// (B). ���� �ڽ��� �������� ���
					if (Sibling->Left->Color == RED)
					{
						Sibling->Left->Color = BLACK;
						Sibling->Color = RED;

						RBT_RotateRight(Root, Sibling);
						Sibling = Successor->Parent->Right;
					}
					// (C). ������ �ڽ��� �������� ���
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
			// ���� ��� ��尡 �θ� ����� ������ �ڽ��� ���: ��<->��
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