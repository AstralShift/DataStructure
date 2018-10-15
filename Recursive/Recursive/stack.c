#include"global.h"
#include "stack.h"

unsigned char initializeLS(struct Stack* stack)
{
	// �Լ� �����Ϳ� �� ��ɿ� �´� �Լ����� �������ش�.
	stack->push = pushLS;
	stack->top = topLS;
	stack->pop = popLS;
	stack->empty = emptyLS;
	stack->release = releaseLS;

	stack->_size = 0;
	// ���� ���ð� ����� ��尡 ������ NULL�� �ʱ�ȭ ���ش�.
	stack->_top = NULL;

	return TRUE;
}

void pushLS(struct Stack* stack, struct Vector2 pos)
{
	// �� ��� ������ ���� ����.
	struct Node* newNode = NULL;

	// �� ��� �����Ϳ� �޸� �� �Ҵ�.
	newNode = (struct Node*)malloc(sizeof(struct Node));

	// ������ ��ȿ�� üũ. (�޸� �Ҵ� �޾Ҵ���?)
	if (NULL == newNode)
	{
		printf("Stack - pushLS �޸� �Ҵ� ����\n");
		return;
	}
	// �� ��忡 ������ �ʱ�ȭ.
	newNode->pos = pos;

	// ���� ���� ������ ����ִ� ���.(�� _top�� NULL�ΰ��)
	if (NULL == stack->_top)
		newNode->pNext = NULL;
	// ���� ���� ������ ������� ���� ���.(�� ���� ���ÿ� �����Ͱ� �־ �� ��ĭ�� ����Ű�� ���)
	else
		newNode->pNext = stack->_top;

	// top�����͸� ���� ���� ���� �Ѵ�.
	stack->_top = newNode;

	// ���ÿ� ����� �޸� ���� ������ �÷��ش�.
	stack->_size++;
}

/**
* �ش� �Լ��� ������ ��������� ���� ���� ���״�.
* pop���� ��带 ����� ��ȯ�ϰԲ� �ص� ������ ���ʿ� �����Ҷ�
* top���� ���� ����Ű�� �κп� ���� �������� �Ͽ� ���� ���鿡�� Ȱ�뵵�� �� ����.(�ݺ������� ������ top���� ���ϰų� Ȯ���ϴ� ���)
*/
struct Vector2 topLS(struct Stack* stack)
{
	// a���� ������ ����ִ� ��� exception.
	if (TRUE == stack->empty(stack))
	{
		printf("����ִ� ���ÿ� top�� ȣ���Ͽ����ϴ�.");
		exit(1);
	}
	// ���� ������ _top�� ����Ű�� �ִ� ����� data���� �����Ѵ�.
	return stack->_top->pos;
}

void popLS(struct Stack* stack)
{
	// ���� ������ ����ִٸ� �ٷ� �����Ѵ�.
	// ���� TRUE��� ����ϰ� ���� ������ ������ ����.
	// �̷��� �Ѵٰ� ���ɿ� ������ ���� �̹��ϴ�.
	if (TRUE == stack->empty(stack))
		return;
	// ���� ��忡 ���� ��������.
	struct Node* deleteNode = NULL;

	// ���� ������ ����Ű�� �ִ� ��带 deleteNode�� ����Ų��.
	// �� �������� ������ ���ÿ��� ������ ������ ���� ����� ������ �Ѵ�.
	deleteNode = stack->_top;

	// ���� ������ ����Ű�� ��带 ���� ����� ���� ���� �Ѵ�.
	stack->_top = deleteNode->pNext;

	// ��带 �����Ѵ�.
	free(deleteNode);

	// �޸𸮺��� ������ �ٿ��ش�.
	stack->_size--;
}

unsigned char emptyLS(struct Stack* stack)
{
	// size�� 0�� �ƴ϶��,
	// ��, ������ ������� ������ FALSE�� ����.
	if (0 != stack->_size)
		return FALSE;

	return TRUE;
}

unsigned int sizeLS(struct Stack* stack)
{
	return stack->_size;
}

void releaseLS(struct Stack* stack)
{
	// ���� ������ ����ִٸ� �ٷ� �����Ѵ�.
	// ���� TRUE��� ����ϰ� ���� ������ ������ ����.
	// �̷��� �Ѵٰ� ���ɿ� ������ ���� �̹��ϴ�.
	if (TRUE == stack->empty(stack))
		return;


	while (FALSE == stack->empty(stack))
		stack->pop(stack);

	stack->_top = NULL;
	stack->_size = 0;
}

unsigned char createStack(struct Stack * stack)
{
	stack->initialize = initializeLS;

	return TRUE;
}
