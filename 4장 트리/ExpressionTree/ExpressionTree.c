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
		// 연산자인 경우
		case '+': case '-': case '*': case '/':
			(*Node) = ET_CreateNode(token); // 노드 생성 후 피연산자 받기.
			ET_BuildExpressionTree(PostfixExpression, &(*Node)->Right);
			ET_BuildExpressionTree(PostfixExpression, &(*Node)->Left);
			break;
		default: // 피연산자라는 것은 잎노드라는 것.
			(*Node) = ET_CreateNode(token);
			break;
	}
}

double ET_Evaluate(ETNode* Tree)
{
	char Temp[2];  // 한자리 숫자만 받을 수 있다는 한계가 있음
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
		memset(Temp, 0, sizeof(Temp)); // Temp 0으로 초기화
		Temp[0] = Tree->Data;
		Result = atof(Temp);  // Result = (double)(Tree->Data-'0');이 더 직관적이며 안정
		break;
	}

	return Result;
}