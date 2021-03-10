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
	root = NULL;  // 초기화

	while (1) {
		printf("1 : 삽입   2 : 삭제   3 : 출력   4 : 종료\n");
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
	//필요 포인터 변수 선언 및 초기화 
	struct tnode* previous = (struct tnode *)malloc(sizeof(struct tnode));
	struct tnode* parent = (struct tnode *)malloc(sizeof(struct tnode));
	struct tnode* move = (struct tnode *)malloc(sizeof(struct tnode));
	struct tnode* temp = (struct tnode *)malloc(sizeof(struct tnode));
	temp = *root;
	previous = 0;
	move = 0;
	parent = 0;
	if (*root == 0) {
		printf("노드가 비어있습니다.\n");
		return;
	}
	/*삭제할 노드 탐색*/
	while (temp->item != num) {

		if (temp->item == num) {		//삭제할 노드 찾음 (temp가 가지고 있음)
			break;
		}
		else if (temp->item < num) {		//이진 탐색	(키 값보다 큰경우)
			previous = temp;				//삭제 하려는 노드의 부모 노드 기억
			temp = temp->right;

		}
		else if (temp->item > num) {	//키 값보다 작은 경우
			previous = temp;				//삭제하려는 노드의 부모 노드 기억
			temp = temp->left;
		}
		/*삭제할 노드가 존재하지 않는 경우(단말노드에 들어왔는데 이 노드조차 삭제하려는 노드가 아닌경우)*/
		if (temp == 0) {
			printf("노드가 존재하지 않습니다.\n");
			return;
		}

	}

	/*노드 삭제*/
	//현재 temp는 삭제할 노드, previous 는 삭제할 노드의 부모 노드 
	if (temp->left == 0 && temp->right == 0) {	//단말 노드삭제	(루트 삭제 고려? )
		if (previous == 0) {					//루트노드 하나만 존재할 때
			*root = 0;
			return;
		}
		if (previous->left == temp) {	//부모의 왼쪽에 연결된 노드라면
			previous->left = 0;
		}
		else if (previous->right == temp) {
			previous->right = 0;
		}

		return;
	}
	else if (temp->left != 0) {		//왼쪽 노드 올리기
		//삭제 후 올려줄 노드 탐색 (왼쪽 서브트리 중 가장 큰 노드)
		parent = temp;
		move = temp->left;
		while (move->right != 0) {	//왼쪽 서브트리부터 시작해 오른쪽 노드끝까지 탐색
			parent = move;			//move의 부모 저장
			move = move->right;
		}

		//move를 삭제할 자리로 올리기
		if (parent == temp) {			//move의 부모가 삭제할 노드일 때
			if (temp->right != 0) {		//삭제할 노드의 오른쪽 자식이 있을 때
				move->right = temp->right;
			}

			//삭제할 노드의 부모에 move를 연결(올려채움)
			if (previous != 0) {
				if (previous->left == temp) {
					previous->left = move;
				}
				else if (previous->right == temp) {
					previous->right = move;

				}
			}
			else                   //삭제되는 노드가 루트라면
			{
				*root = move;
			}


		}
		else {							//아닐때
			parent->right = move->left;
			move->left = temp->left;

			if (temp->right != 0) {		//삭제할 노드의 오른쪽 자식이 있을 때
				move->right = temp->right;
			}

			//삭제할 노드의 부모에 move를 연결(올려채움)
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
	else if (temp->right != 0) {	//오른쪽 노드 올리기
		//삭제 후 올려줄 노드 탐색 (오른쪽 서브트리 중 가장 작은 노드)
		parent = temp;
		move = temp->right;
		while (move->left != 0) {	//오른쪽 서브트리부터 시작해 왼쪽 노드끝까지 탐색
			parent = move;			//move의 부모 저장
			move = move->left;
		}

		//move를 삭제할 자리로 올리기
		if (parent == temp) {			//move의 부모가 삭제할 노드일 때
			if (temp->left != 0) {		//삭제할 노드의 왼쪽 자식이 있을 때
				move->left = temp->left;
			}

			//삭제할 노드의 부모에 move를 연결(올려채움)
			if (previous != 0) {			//root 노드가 아니라면
				if (previous->left == temp) {
					previous->left = move;
				}
				else if (previous->right == temp) {
					previous->right = move;

				}
			}
			else                   //삭제되는 노드가 루트라면
			{
				*root = move;
			}


		}
		else {							//아닐때
			parent->left = move->right;
			move->right = temp->right;

			if (temp->left != 0) {		//삭제할 노드의 오른쪽 자식이 있을 때
				move->left = temp->left;
			}

			//삭제할 노드의 부모에 move를 연결(올려채움)
			if (previous != 0) {			//루트노드가 아닐경우
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
		printf("존재하는 숫자 입니다\n");
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
