#ifndef _UTILLITY_H_
#define _UTILLITY_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <crtdbg.h>


/**
 * ��ġ���� ǥ���� ���� ���� ����ü.
 * Vector�� ��︮�� �ʴ� ǥ���� unsigned char�� ����Ͽ���.
 * POSITION�̶�� ���̹��� �ϴ°� ��������
 * ���ǻ� �Ϲ������� ���� ���̴� Vector2�� �Ͽ���.
 */
struct Vector2
{
	unsigned char x, y;
};

/**
 * Linked Stack�� Ȱ���ϱ� ����
 * Node����ü�� �ڱ���������ü ������ �־� �������.
 * �̷ν� Node���� ���� ǥ���� �������� Linked ����� ���ν� Ȱ���� ����������.
 * ���翡�� ���뼺�� ���� ������(pos������ Vector2�� �Ǿ��ִ�.)�� �Ǿ��־�
 * ��带 Ȱ���ϴ� �ڷᱸ�� ���� ���뼺�� ��������.
 * ���� �̸� �����Ͽ� void* �� Ȱ���� �����̴�.
 */
struct Node
{
	// ��ġ ���� ���� ����.
	struct Vector2 pos;
	// �ڱ� ���� ����ü. �̸� Ȱ���Ͽ� ��尣�� ������ �����ϴ�.
	struct Node* pNext;
};

// const�� �̿��� Global���� �����ϰ� ��������� Ȱ��. #define ��� ����
extern const unsigned char const FALSE;
extern const unsigned char const TRUE;

#endif