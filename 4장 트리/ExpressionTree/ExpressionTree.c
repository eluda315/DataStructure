#include "ExpressionTree.h"

ETNode* ET_CreateNode(ElementType NewData)
{
	ETNode* Node = (ETNode*)malloc(sizeof(ETNode));

	Node->Left = NULL;
	Node->Right = NULL;
	Node->Data = NewData;

	return Node;
}

void ET_DestroyNode(ETNode* Node)
{
	free(Node);
}

void ET_DestroyTree(ETNode* Root)
{
	if (Root == NULL) return;

	ET_DestroyTree(Root->Left);
	ET_DestroyTree(Root->Right);
	ET_DestroyNode(Root);
}

void ET_PreorderPrintTree(ETNode* Node)
{
	if (Node == NULL)
		return;

	printf(" %c", Node->Data);

	ET_PreorderPrintTree(Node->Left);
	ET_PreorderPrintTree(Node->Right);
}

void ET_InorderPrintTree(ETNode* Node)
{
	if (Node == NULL)
		return;

	printf("(");
	ET_InorderPrintTree(Node->Left);

	printf("%c", Node->Data);

	ET_InorderPrintTree(Node->Right);
	printf(")");
}

void ET_PostorderPrintTree(ETNode* Node)
{
	if (Node == NULL)
		return;

	ET_PostorderPrintTree(Node->Left);
	ET_PostorderPrintTree(Node->Right);
	printf(" %c", Node->Data);
}

void ET_BuildExpressionTree(char* PostfixExpression, ETNode** Node)
{
	int len = strlen(PostfixExpression);
	char token = PostfixExpression[len - 1];
	PostfixExpression[len - 1] = '\0';

	switch (token)
	{
		// �������� ���
		case '+': case '-': case '*': case '/':
			(*Node) = ET_CreateNode(token); // ��� ���� �� �ǿ����� �ޱ�.
			ET_BuildExpressionTree(PostfixExpression, &(*Node)->Right);
			ET_BuildExpressionTree(PostfixExpression, &(*Node)->Left);
			break;
		default: // �ǿ����ڶ�� ���� �ٳ���� ��.
			(*Node) = ET_CreateNode(token);
			break;
	}
}

double ET_Evaluate(ETNode* Tree)
{
	char Temp[2];  // ���ڸ� ���ڸ� ���� �� �ִٴ� �Ѱ谡 ����
	double Right = 0;
	double Left = 0;
	double Result = 0;

	if (Tree == NULL) return;

	switch (Tree->Data)
	{
	case '+': case '-': case '*': case '/':
		Left = ET_Evaluate(Tree->Left);
		Right = ET_Evaluate(Tree->Right);

		if (Tree->Data == '+') Result = Left + Right;
		else if (Tree->Data == '-') Result = Left - Right;
		else if (Tree->Data == '*') Result = Left * Right;
		else if (Tree->Data == '/') Result = Left / Right;
		break;

	default:
		memset(Temp, 0, sizeof(Temp)); // Temp 0���� �ʱ�ȭ
		Temp[0] = Tree->Data;
		Result = atof(Temp);  // Result = (double)(Tree->Data-'0');�� �� �������̸� ����
		break;
	}

	return Result;
}