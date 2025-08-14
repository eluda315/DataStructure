#include "BinarySearchTree.h"

BSTNode* BST_CreateNode(ElementType NewData)
{
	BSTNode* NewNode = (BSTNode*)malloc(sizeof(BSTNode));

	NewNode->Data = NewData;
	NewNode->Left = NULL;
	NewNode->Right = NULL;

	return NewNode;
}

void BST_DestroyNode(BSTNode* Node)
{
	free(Node);
}

void BST_DestroyTree(BSTNode* Tree)
{
	if (Tree->Right != NULL) BST_DestroyTree(Tree->Right);
	if (Tree->Left != NULL) BST_DestroyTree(Tree->Left);

	Tree->Left = NULL;
	Tree->Right = NULL;	
	
	BST_DestroyNode(Tree);
}

BSTNode* BST_SearchNode(BSTNode* Tree, ElementType Target)
{
	if (Tree == NULL) return NULL;

	if (Tree->Data == Target) return Tree;
	else if ((Tree->Data) > Target) BST_SearchNode(Tree->Left, Target);
	else BST_SearchNode(Tree->Right, Target);
}

BSTNode* BST_SearchMinNode(BSTNode* Tree)
{
	if (Tree == NULL) return NULL;

	// ���� ������ NULL�̸� �߾ӳ�尡 ���� ����(������ ������ ������ �ڱ⺸�� ũ�ϱ�)
	if (Tree->Left == NULL) return Tree;
	else return BST_SearchMinNode(Tree->Left);
}

void BST_InsertNode(BSTNode* Tree, BSTNode* Child)
{
	if (Tree == NULL) return NULL;

	if (Tree->Data > Child->Data)
	{
		if (Tree->Left == NULL) Tree->Left = Child;
		else BST_InsertNode(Tree->Left, Child);
	}
	else if (Tree->Data < Child->Data)
	{
		if (Tree->Right == NULL) Tree->Right = Child;
		else BST_InsertNode(Tree->Right, Child);
	}
}

BSTNode* BST_RemoveNode(BSTNode* Tree, BSTNode* Parent, ElementType Target)
{
	BSTNode* Removed = NULL;
	if (Tree == NULL) return NULL;

	if (Tree->Data > Target) Removed = BST_RemoveNode(Tree->Left, Tree, Target);
	else if (Tree->Data < Target) Removed = BST_RemoveNode(Tree->Right, Tree, Target);
	else // removed�� ã�� ���
	{
		Removed = Tree;
		
		// 1. �ٳ����
		if (Tree->Left == NULL && Tree->Right == NULL)
		{
			// �θ� ����� ����� �ڽ� ��忴���� Ȯ���ϰ� NULLó��
			if (Parent->Left == Tree) Parent->Left = NULL;
			else Parent->Right = NULL;
		}
		else // 2. �������ٸ�
		{
			// 2-1. �ڽ��� ���� �� �ִ� ���
			if (Tree->Left != NULL && Tree->Right != NULL)
			{
				BSTNode* Min = BST_SearchMinNode(Tree->Right);
				// �ּڰ� ���� �ڽ��� �־ ������ �ϳ��� �����Ƿ� ó���� ����
				Min = BST_RemoveNode(Tree, NULL, Min->Data);
				Tree->Data = Min->Data;
			}
			else // 2-2. �ڽ��� �ϳ��� �ִ� ���
			{
				BSTNode* Child = NULL;
				if (Tree->Left != NULL) // ���� �ڽĸ� �ִ� ���
					Child = Tree->Left;
				else // ������ �ڽĸ� �ִ� ���
					Child = Tree->Right;

				if (Parent->Left == Tree) // ������ ��尡 �θ��� ���� �ڽ��̸�
					Parent->Left = Child;
				else // ������ ��尡 �θ��� ������ �ڽ��̸�
					Parent->Right = Child;
			}
		}
	}

	return Removed;
}

void BST_InorderPrintTree(BSTNode* Node)
{
	if (Node == NULL) return NULL;

	BST_InorderPrintTree(Node->Left);
	printf("%d ", Node->Data);
	BST_InorderPrintTree(Node->Right);
}