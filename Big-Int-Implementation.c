#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum {
	MINUS,
	PLUS
}Sign;
typedef struct node_tag{
	int data;
	struct node_tag *next;
}Node;

typedef struct bigInt_tag{
	Node *rear;
	Node *front;
	Sign s;
}bigInt;

Node *makeNode(Node *num,int n);
void createInt(bigInt *x);
void printRecurse(Node *n);
void print(bigInt *x);
Sign Addition(bigInt *x,bigInt *y,bigInt *res);
Sign Subtraction(bigInt *x,bigInt *y,bigInt *res);
Sign Multiplication(bigInt *l1, bigInt *l2,bigInt *b);
int getLength(bigInt *x);

void main()
{
	int e=1;
	Sign s=PLUS;
	while(e==1)
	{
		int a,b,c;
			printf("Which operation you want to perform-\n1.Addition\n2.Subtraction\n3.Multiplication\n");
			scanf("%d",&c);
			switch(c)
			{
				case 1 :
					{
						bigInt a,b,sum;
						createInt(&a);
						/*print(&a);*/
						createInt(&b);
						/*print(&b);*/
						printf("Addition is:\n");
						s=Addition(&a,&b,&sum);
						printf("%d\n",getLength(&sum));
						if(getLength(&sum)>38)
						{
							printf("The BigInt limit is exceeded\n");	
						}
						else{
						
							if(s==PLUS){
								print(&sum);
							}
							else{
								printf("-");
								print(&sum);
							}
						}
					}	break;
				case 2 :
					{
						bigInt a,b,diff;
						createInt(&a);
						/*print(&a);*/
						createInt(&b);
						/*print(&b);*/
						printf("Subtraction is:\n");
						s=Subtraction(&a,&b,&diff);
						if(s==PLUS){
							print(&diff);
						}
						else{
							printf("-");
							print(&diff);
						}
					}	break;
				case 3 :
				{
					bigInt a,b,mul;
					createInt(&a);
					createInt(&b);
					printf("Multiplication  is:\n");
					s=Multiplication(&a,&b,&mul);
					if(getLength(&mul)>38)
						{
							printf("The BigInt limit is exceeded\n");	
						}
						else{
						
							if(s==PLUS){
								print(&mul);
							}
							else{
								printf("-");
								print(&mul);
							}
						}
				}	break;
				default  : 	
					printf("Enter correct option\n");
					break;	
			}
		printf("press 0 to exit\npress 1 to continue\n");
		scanf("%d",&e);
	}
}






Node * makeNode(Node *num,int n){
	num = (Node *)malloc(sizeof(Node));
	num->next=NULL;
	num->data = n;
	return num;
}

void createInt(bigInt *x)
{
	printf("Enter a number\n");
	char n[310] = "203956878356401977405765866929034577280193993314348263094772646453283062722701277632936616063144088173312372882677123879538709400158306567338328279154499698366071906766440037074217117805690872792848149112022286332144876183376326512083574821647933992961249917319836219304274280243803104015000563790123444444";
	Node *num;
	int sum = 0,steps=0,mul=1;
	x->front = x->rear = NULL;
	x->s = PLUS;
	scanf("%s",&n);
	int l = strlen(n)-1;
	if(n[0] == '-')
	{
		x->s = MINUS;
		n[0] = '0';
	}
	while(l>=0)
	{
		sum = 0;steps=0;mul=1;
		while(steps<=8 && l>=0)
		{
			sum += (n[l]-48)*mul;
			mul*=10;
			steps++;
			l--;
		}
		num=makeNode(num,sum);
		if(x->front==NULL){
			x->front=x->rear=num;
		}
		else{
			(x->rear)->next=num;
			x->rear=num;
		}
	}
}

void printRecurse(Node *n)
{
	Node * num = n;
	if(num!=NULL){
		printRecurse(num->next);
		printf("%d",num->data);
	}
}

void print(bigInt *x)
{
	printRecurse(x->front);
	printf("\n");
}


Sign Addition(bigInt *x,bigInt *y,bigInt *res)
{
	Sign s = PLUS;
	if(x->s == y->s){
		res->front=res->rear=NULL;
		Node *num,*xptr,*yptr;
		
		xptr = x->front;
		yptr = y->front;
		int sum=0,carry = 0;
		while(xptr!=NULL && yptr!=NULL)
		{
			sum = xptr->data + yptr->data + carry;
			sum%=1000000000;
			carry/=1000000000;
			num = makeNode(num,sum);
			if(res->front == NULL)
				res->front = res->rear = num;
			else
			{
				(res->rear)->next = num;
				res->rear = num;
			}
			xptr=xptr->next;
			yptr=yptr->next;
		}
		while(xptr!=NULL)
		{
			sum = xptr->data + carry;
			sum%=1000000000;
			carry/=1000000000;
			num = makeNode(num,sum);
			if(res->front == NULL)
				res->front = res->rear = num;
			else
			{
				(res->rear)->next = num;
				res->rear = num;
			}
			xptr=xptr->next;
		}
		while(yptr!=NULL)
		{
			sum = yptr->data + carry;
			sum%=1000000000;
			carry/=1000000000;
			num = makeNode(num,sum);
			if(res->front == NULL)
				res->front = res->rear = num;
			else
			{
				(res->rear)->next = num;
				res->rear = num;
			}
			yptr=yptr->next;
		}
		
		if(carry!=0)
		{
			num = makeNode(num,carry);
			(res->rear)->next = num;
			res->rear = num;
		}
		return x->s;
	}
	else{
		if(x->s == MINUS){
			x->s = PLUS;
			return Subtraction(y,x,res);
		}
		else{
			y->s = PLUS;
			return Subtraction(x,y,res);}
	}
}

Sign Subtraction(bigInt *x,bigInt *y,bigInt *res)
{
	if(x->s == y->s){
		res->front=res->rear = NULL;
		Sign sig = PLUS;
		int diff = 0,borrow = 0;
		Node *num,*xptr,*yptr;
		xptr=x->front;
		yptr=y->front;
		while(xptr!=NULL && yptr!=NULL)
		{
			diff = xptr->data - yptr->data -borrow;
			borrow = (diff<0)?1:0;
			diff = (borrow==1)?(1000000000+diff):diff;
			num = makeNode(num,diff);
			if(res->front == NULL)
				res->front = res->rear = num;
			else
			{
				(res->rear)->next = num;
				res->rear = num;
			}
			xptr = xptr->next;
			yptr = yptr->next;
		}
		while(xptr!=NULL)
		{
			diff = xptr->data-borrow;
			borrow = (diff<0)?1:0;
			diff = (borrow==1)?(1000000000+diff):diff;
			num = makeNode(num,diff);
			if(res->front == NULL)
				res->front = res->rear = num;
			else
			{
				(res->rear)->next = num;
				res->rear = num;
			}
			xptr = xptr->next;
		}
		
		if(borrow == 1 || yptr!=NULL)
		{
			sig = MINUS;
			Subtraction(y,x,res);
		}
		
		if(x->s == sig)
			return PLUS;
		else
			return MINUS;
	}
	else
	{
		if(x->s == MINUS){
			y->s = MINUS;
			return Addition(x,y,res);
		}
		else
		{
			y->s = PLUS;
			return Addition(x,y,res);
		}
	}
}

Sign Multiplication(bigInt *l1, bigInt *l2,bigInt *b)
{	
	b->front=b->rear = NULL;
	long int m,carry=0,d;
	Node *num,*p1,*p2,*p,*t;
	p1=l1->front;
	p=b->rear;
	while(p1!=NULL)
	{
		d=p1->data;
		p2=l2->front;
		carry=0;
		while(p2!=NULL)
		{
			if(p==NULL){
				num=makeNode(num,0);
				if(b->front==NULL){
					t=p=b->front=b->rear=num;
				}
				else{
					(b->rear)->next=num;
					p=b->rear=num;
					if(t==NULL)
					{
						t=p;
					}
				}
			}
			m=d*(p2->data)+carry+p->data;
			carry=m/1000000000;
			m=m%1000000000;
			p->data=m;
			p=p->next;
			p2=p2->next;
		}
		if(carry!=0)
		{
				num=makeNode(num,carry);
				if(b->front==NULL){
					p=b->front=b->rear=num;
				}
				else{
					(b->rear)->next=num;
					p=b->rear=num;
				}
		}
		p1=p1->next;
		p=t=t->next;
	}
	if(l1->s == l2->s)
		return PLUS;
	else
		return MINUS;
}

int getLength(bigInt *x){
    int length =0;
    Node *num = x->front;
    while(num != NULL){
        num = num->next;
        length++;
    }
    return length;
}




















