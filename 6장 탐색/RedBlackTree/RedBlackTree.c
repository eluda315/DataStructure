#include "RedBlackTree.h"

void RBT_DestroyTree(RBTNode* Tree)
{

}

RBTNode* RBT_CreateNode(ElementType NewData)
{

}

void RBT_DestroyNode(RBTNode* Node)
{

}

RBTNode* RBT_SearchNode(RBTNode* Tree, ElementType Target)
{

}

RBTNode* RBT_SearchMinNode(RBTNode* Tree)
{

}

void RBT_InsertNode(RBTNode** Tree, RBTNode* NewNode)
{

}

void RBT_InsertNodeHelper(RBTNode** Tree, RBTNode* NewNode)
{

}

RBTNode* RBT_RemoveNode(RBTNode** Root, ElementType Target)
{

}

void RBT_RebuildAfterInsert(RBTNode** Tree, RBTNode* NewNode)
{

}

void RBT_RebuildAfterRemove(RBTNode** Root, RBTNode* X)
{

}

void RBT_PrintTree(RBTNode* Node, int Depth, int BlackCount) 
{

}

void RBT_RotateLeft(RBTNode** Root, RBTNode* Parent)
{

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