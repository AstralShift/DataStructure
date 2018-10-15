#ifndef _STACK_H_
#define _STACK_H_
#include "global.h"

/**
 * Stack�� �⺻���� ��ɵ鿡 ���� �����س��Ҵ�.
 * Array������δ� �޸� ������ ���� ���ට����(�Ҵ緮 ��ŭ�� ����Ѵٵ簡 Ȥ�� ���Ҵ��ϰ� copy structure�Ѵٵ簡 ��)
 * �׷������� ���᰹���� ���࿡�� ���� �����ο� Linked ����� Ȱ���� Stack�� �����Ͽ���.
 */
struct Stack
{
	// ���� ������ �ֻ�� �޸� ���� ����Ű�� ������.
	struct Node* _top;
	// ���� ���ÿ� ���� ũ��.(�Ҵ�� �޸� ���� ����)
	unsigned int _size;

	/* initialize()
	 *
	 * initialize������ ����ü �������� �ʱ�ȭ �ϰ� ������ �Լ������Ϳ� �´� �Լ��� �������ش�.
	 *
	 * Parameters:
	 *     struct Stack* : ����� �� ���ñ���ü ������ ���ڷ� �����´�.(�� ���� �����ã�� ���� �Ѱ�)
	 * Returns : unsigned char
	 *     initialize�� �����ϸ� FALSE(0)�� �����ϰ� �����ϸ� TRUE(1)�� �����Ѵ�.
	 */
	unsigned char(*initialize)(struct Stack* stack);
	
	/* push()
	 *
	 * push������ ���ڷ� ���޵� struct Vector2�� ���� ���� �� ��带 ���� ���ÿ� �������ش�.
	 *
	 * Parameters:
	 *     struct Stack*  : intialize�� ���� struct Stack*�� ����. �ش� �κ� ����.
	 *     struct Vector2 : ��ġ���� ��Ÿ���� ����ü ����.
	 * Returns : void
	 */
	void(*push)(struct Stack* stack, struct Vector2 data);

	/* top()
	 *
	 * top������ ���� ������ ����Ű�� �ִ� �ֻ�� �޸𸮺��� ���� �������ش�.
	 *
	 * Parameters:
	 *     struct Stack*  : intialize�� ���� struct Stack*�� ����. �ش� �κ� ����.
	 * Returns : struct Vector2
	 *     ��ġ���� ��Ÿ�� ����ü ���� �ϳ��� �����Ѵ�.
	 */
	struct Vector2(*top)(struct Stack* stack);

	/* pop()
	 *
	 * ���� ������ ����Ű�� �ִ� �ֻ�� �޸� ������ ������ ���� �� �޸� ���� �����Ѵ�.
	 *
	 * Parameters:
	 *     struct Stack*  : intialize�� ���� struct Stack*�� ����. �ش� �κ� ����.
	 * Returns : void
	 */
	void(*pop)(struct Stack* stack);

	/* empty()
	*
	* ���� ������ ����ִ��� Ȯ���ϴ� ���.
	*
	* Parameters:
	*     struct Stack*  : intialize�� ���� struct Stack*�� ����. �ش� �κ� ����.
	* Returns : unsigned char
	*     initialize�� �����ϸ� FALSE(0)�� �����ϰ� �����ϸ� TRUE(1)�� �����Ѵ�.
	*/
	unsigned char(*empty)(struct Stack* stack);

	/* size()
	*
	* ���� ���ÿ� ����� �޸� ���� ������ �������ִ� ���.
	*
	* Parameters:
	*     struct Stack*  : intialize�� ���� struct Stack*�� ����. �ش� �κ� ����.
	* Returns : unsigned int
	*     ���ð� ����� �޸� �������� ����.
	*/
	unsigned int (*size)(struct Stack* stack);

	/* release()
	*
	* ���ð� ����� �ֻ�� �޸𸮺��� ���ʷ� ���ð��� ������ �����鼭 �޸𸮺��� �����Ѵ�.
	*
	* Parameters:
	*     struct Stack*  : intialize�� ���� struct Stack*�� ����. �ش� �κ� ����.
	* Returns : void
	*/
	void(*release)(struct Stack* stack);
};

/*
 * �Ʒ� region���� ���� StackFunctions��
 * ���� ������ ������ �Լ������� ������� ����� ������ �Լ����̴�.
 * �ּ����� ���� Stack����ü�� �Լ������Ϳ� �� ������
 * �ܺ��������̽��μ��� ������ �ϴ� ���� ���� ������ Stack ����ü�̹Ƿ�
 * ���������� �ܺο��� ��� �� �� �ش� �Լ��� �ּ� ����(���콺 on�� �ؼ��� ���� ��������� �ϴ�)��
 * ���� ������ Stack����ü�� �ϱ� �����̴�.
 * ���� ������Ʈ������ �ǹ̰� �������� ��⺰�� ������??
 * �ܺ��������̽��� �ּ��ٴ� ���� �ǹ̰� ũ�� �����ߴ�.
 */
#pragma region StackFunctions
unsigned char initializeLS(struct Stack* stack);
void pushLS(struct Stack* stack, struct Vector2 pos);
struct Vector2 topLS(struct Stack* stack);
void popLS(struct Stack* stack);
unsigned char emptyLS(struct Stack* stack);
unsigned int sizeLS(struct Stack* stack);
void releaseLS(struct Stack* stack);
unsigned char createStack(struct Stack * stack);
#pragma endregion
#endif