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

	// 왼쪽 하위가 NULL이면 중앙노드가 제일 작음(오른쪽 하위는 언제나 자기보다 크니까)
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
	else // removed를 찾은 경우
	{
		Removed = Tree;
		
		// 1. 잎노드라면
		if (Tree->Left == NULL && Tree->Right == NULL)
		{
			// 부모 노드의 어느쪽 자식 노드였는지 확인하고 NULL처리
			if (Parent->Left == Tree) Parent->Left = NULL;
			else Parent->Right = NULL;
		}
		else // 2. 가지였다면
		{
			// 2-1. 자식이 양쪽 다 있는 경우
			if (Tree->Left != NULL && Tree->Right != NULL)
			{
				BSTNode* Min = BST_SearchMinNode(Tree->Right);
				// 최솟값 노드는 자식이 있어도 무조건 하나만 있으므로 처리가 쉬움
				Min = BST_RemoveNode(Tree, NULL, Min->Data);
				Tree->Data = Min->Data;
			}
			else // 2-2. 자식이 하나만 있는 경우
			{
				BSTNode* Child = NULL;
				if (Tree->Left != NULL) // 왼쪽 자식만 있는 경우
					Child = Tree->Left;
				else // 오른쪽 자식만 있는 경우
					Child = Tree->Right;

				if (Parent->Left == Tree) // 삭제할 노드가 부모의 왼쪽 자식이면
					Parent->Left = Child;
				else // 삭제할 노드가 부모의 오른쪽 자식이면
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