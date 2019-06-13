#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 10
#define EMPTY -1

struct node
{
	char kind;
	char op;
	int number;
	struct node *left,*right;
};

struct stack
{
	struct node *data[MAX];
	int top;
};

int isempty(struct stack *s)
{
	return (s->top == EMPTY) ? 1 : 0;
}

void emptystack(struct stack* s)
{
	s->top=EMPTY;
}

void push(struct stack* s, struct node *item)
{
	if(s->top == (MAX-1))
	{
		printf("\nSTACK FULL");
	}
	else
	{
		++s->top;
		s->data[s->top]=item;

	}
}

struct node* pop(struct stack* s)
{
	struct node *ret=NULL;
	if(!isempty(s))
	{
		ret= s->data[s->top];
		--s->top;
	}
	return ret;
}

void postfix2exptree(char* postfix, struct node **root)
{
	struct stack X;
	struct node *newnode,*op1,*op2;
	char numberextract[5];
	char *p;

	emptystack(&X);
	p = &postfix[0];
	strcpy(numberextract,"");
	while(*p)
	{

		while(*p == ' ' || *p == '\t')
		{
			p++;
		}

		if(isdigit(*p))
		{
			while(isdigit(*p))
			{
				strcat(numberextract,p);
				p++;
			}

			newnode = malloc(sizeof(struct node));
			newnode->kind = 'N';
			newnode->number = atoi(numberextract);
			newnode->left = NULL;
			newnode->right = NULL;
			push(&X,newnode);
			strcpy(numberextract,"");
		}
		else
		{
			op1 = pop(&X);
			op2 = pop(&X);
			newnode = malloc(sizeof(struct node));
			newnode->kind = 'O';
			newnode->op = *p;
			newnode->left = op2;
			newnode->right = op1;
			push(&X,newnode);
		}
		p++;
	}
	*root = pop(&X);
}

int evaluatetree(struct node *x)
{
   if( x->kind == 'O' )
	{
	  int op1 = evaluatetree( x->left );
	  int op2 = evaluatetree( x->right );
	  switch ( x->op )
		{
		 case '+':  return op1 + op2;
		 case '-':  return op1 - op2;
		 case '*':  return op1 * op2;
		 case '/':  return op1 / op2;
		 default:   return 0;
	  }
   }
	else
	   return (x->number);
}

void inorder(struct node *x)
{
	if(x != NULL)
	{
		inorder(x->left);

		if(x->kind == 'O')
			printf("%c ",x->op);
		else
			printf("%d ",x->number);

		inorder(x->right);
	}
}

void preorder(struct node *x)
{
	if(x != NULL)
	{
		if(x->kind == 'O')
			printf("%c ",x->op);
		else
			printf("%d ",x->number);

		preorder(x->left);
		preorder(x->right);
	}
}

void postorder(struct node *x)
{
	if(x != NULL)
	{
		postorder(x->left);
		postorder(x->right);

		if(x->kind == 'O')
			printf("%c ",x->op);
		else
			printf("%d ",x->number);
	}
}

int main()
{
	struct node *r;
	postfix2exptree("100 50 - 2 /",&r);
	printf("\nResult = %d\n",evaluatetree(r));
	return 0;
}
/* OUTPUT:
Inorder = 100 - 50 / 2
Preorder = / - 100 50 2
Postprder = 100 50 - 2 /
Result = 25

u*/
