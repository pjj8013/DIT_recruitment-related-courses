#include <stdio.h>
#include <stdlib.h>

struct tnode {
	int item;		/* number */
	struct tnode *left;	/* left child */
	struct tnode *right;	/* right child */
};

struct tnode *addtree(struct tnode *, int);
void deletetree(struct tnode **, int);
void treeprint(struct tnode *);

main()
{
	struct tnode *root;
	int cond, num;
	root = NULL;  // �ʱ�ȭ

	while (1) {
		printf("1 : ����   2 : ����   3 : ���   4 : ����\n");
		scanf("%d", &cond);
		if (cond == 1) {
			printf("Add Number\n");
			scanf("%d", &num);
			root = addtree(root, num);
		}
		else if (cond == 2) {
			printf("Delete Number\n");
			scanf("%d", &num);
			deletetree(&root, num);
		}
		else  if (cond == 3)
			treeprint(root);
		else  if (cond == 4)
			break;
		else {
			printf("Wrong Input\n");
			exit(1);
		}
	}
	return 0;
}

void deletetree(struct tnode **root, int num) {
	//�ʿ� ������ ���� ���� �� �ʱ�ȭ 
	struct tnode* previous = (struct tnode *)malloc(sizeof(struct tnode));
	struct tnode* parent = (struct tnode *)malloc(sizeof(struct tnode));
	struct tnode* move = (struct tnode *)malloc(sizeof(struct tnode));
	struct tnode* temp = (struct tnode *)malloc(sizeof(struct tnode));
	temp = *root;
	previous = 0;
	move = 0;
	parent = 0;
	if (*root == 0) {
		printf("��尡 ����ֽ��ϴ�.\n");
		return;
	}
	/*������ ��� Ž��*/
	while (temp->item != num) {

		if (temp->item == num) {		//������ ��� ã�� (temp�� ������ ����)
			break;
		}
		else if (temp->item < num) {		//���� Ž��	(Ű ������ ū���)
			previous = temp;				//���� �Ϸ��� ����� �θ� ��� ���
			temp = temp->right;

		}
		else if (temp->item > num) {	//Ű ������ ���� ���
			previous = temp;				//�����Ϸ��� ����� �θ� ��� ���
			temp = temp->left;
		}
		/*������ ��尡 �������� �ʴ� ���(�ܸ���忡 ���Դµ� �� ������� �����Ϸ��� ��尡 �ƴѰ��)*/
		if (temp == 0) {
			printf("��尡 �������� �ʽ��ϴ�.\n");
			return;
		}

	}

	/*��� ����*/
	//���� temp�� ������ ���, previous �� ������ ����� �θ� ��� 
	if (temp->left == 0 && temp->right == 0) {	//�ܸ� ������	(��Ʈ ���� ���? )
		if (previous == 0) {					//��Ʈ��� �ϳ��� ������ ��
			*root = 0;
			return;
		}
		if (previous->left == temp) {	//�θ��� ���ʿ� ����� �����
			previous->left = 0;
		}
		else if (previous->right == temp) {
			previous->right = 0;
		}

		return;
	}
	else if (temp->left != 0) {		//���� ��� �ø���
		//���� �� �÷��� ��� Ž�� (���� ����Ʈ�� �� ���� ū ���)
		parent = temp;
		move = temp->left;
		while (move->right != 0) {	//���� ����Ʈ������ ������ ������ ��峡���� Ž��
			parent = move;			//move�� �θ� ����
			move = move->right;
		}

		//move�� ������ �ڸ��� �ø���
		if (parent == temp) {			//move�� �θ� ������ ����� ��
			if (temp->right != 0) {		//������ ����� ������ �ڽ��� ���� ��
				move->right = temp->right;
			}

			//������ ����� �θ� move�� ����(�÷�ä��)
			if (previous != 0) {
				if (previous->left == temp) {
					previous->left = move;
				}
				else if (previous->right == temp) {
					previous->right = move;

				}
			}
			else                   //�����Ǵ� ��尡 ��Ʈ���
			{
				*root = move;
			}


		}
		else {							//�ƴҶ�
			parent->right = move->left;
			move->left = temp->left;

			if (temp->right != 0) {		//������ ����� ������ �ڽ��� ���� ��
				move->right = temp->right;
			}

			//������ ����� �θ� move�� ����(�÷�ä��)
			if (previous != 0) {
				if (previous->left == temp) {
					previous->left = move;
				}
				else if (previous->right == temp) {
					previous->right = move;

				}
			}
			else {
				*root = move;
			}

		}

	}
	else if (temp->right != 0) {	//������ ��� �ø���
		//���� �� �÷��� ��� Ž�� (������ ����Ʈ�� �� ���� ���� ���)
		parent = temp;
		move = temp->right;
		while (move->left != 0) {	//������ ����Ʈ������ ������ ���� ��峡���� Ž��
			parent = move;			//move�� �θ� ����
			move = move->left;
		}

		//move�� ������ �ڸ��� �ø���
		if (parent == temp) {			//move�� �θ� ������ ����� ��
			if (temp->left != 0) {		//������ ����� ���� �ڽ��� ���� ��
				move->left = temp->left;
			}

			//������ ����� �θ� move�� ����(�÷�ä��)
			if (previous != 0) {			//root ��尡 �ƴ϶��
				if (previous->left == temp) {
					previous->left = move;
				}
				else if (previous->right == temp) {
					previous->right = move;

				}
			}
			else                   //�����Ǵ� ��尡 ��Ʈ���
			{
				*root = move;
			}


		}
		else {							//�ƴҶ�
			parent->left = move->right;
			move->right = temp->right;

			if (temp->left != 0) {		//������ ����� ������ �ڽ��� ���� ��
				move->left = temp->left;
			}

			//������ ����� �θ� move�� ����(�÷�ä��)
			if (previous != 0) {			//��Ʈ��尡 �ƴҰ��
				if (previous->left == temp) {
					previous->left = move;
				}
				else if (previous->right == temp) {
					previous->right = move;

				}
			}
			else
			{
				*root = move;
			}
		}



	}




}

struct tnode *addtree(struct tnode *p, int num)
{
	if (p == NULL) {
		p = (struct tnode *)malloc(sizeof(struct tnode));
		p->item = num;
		p->left = p->right = NULL;
	}
	else if (num == p->item)
		printf("�����ϴ� ���� �Դϴ�\n");
	else if (num < p->item)
		p->left = addtree(p->left, num);
	else
		p->right = addtree(p->right, num);
	return p;
}


void treeprint(struct tnode *p)
{
	if (p != NULL) {
		treeprint(p->left);
		printf("%d\n", p->item);
		treeprint(p->right);
	}
}
