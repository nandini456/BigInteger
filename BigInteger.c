
#include "BigInteger.h" // Include the header file

struct BigInteger add(struct BigInteger a, struct BigInteger b) {
    struct BigInteger r;
    r.l = NULL;

    if(a.sign!=b.sign)
    {
        if(compare(a.l,b.l)>0)r.sign=a.sign;
        else
        r.sign=b.sign;
        b.sign=-1*b.sign;
        r=sub(a,b);
        return r;
    }
    if(compare(a.l,b.l)>0)r.sign=a.sign;
        else
        r.sign=b.sign;

    struct node* p1 = a.l;
    struct node* p2 = b.l;
    int carry = 0;
    struct node* result = NULL;
    struct node* itr = NULL;
    
    while (p1 || p2 || carry) {
        int sum = (p1 ? p1->data : 0) + (p2 ? p2->data : 0) + carry;
        if (result == NULL) {
            result = newnode(sum % 10);
            itr = result;
        } else {
            itr->next = newnode(sum % 10);
            itr = itr->next;
        }
        carry = sum / 10;

        if (p1)
        p1 = p1->next;
        if (p2) 
        p2 = p2->next;
    }
    r.l = rev(result);
    r.length = length(result); 
    return r;
}
struct BigInteger sub(struct BigInteger a, struct BigInteger b)
{
    struct BigInteger r;
    r.l = NULL;
    if(a.sign!=b.sign)
    {
       
        if(compare(a.l,b.l)>0)r.sign=a.sign;
        else
        r.sign=b.sign;
        b.sign=-1*b.sign;
        r=add(a,b);
        
        return r;
    }
    if(compare(a.l,b.l)>0)r.sign=a.sign;
    else r.sign=-1*b.sign;

    int borrow = 0;
    struct node* result = NULL;
    struct node* itr = NULL;
    
    struct node* p1 = a.l;
    struct node* p2 = b.l;
    if(compare(p1,p2)<=0)
    {
        struct node*t=p1;
        p1=p2;
        p2=t;
    }
    while (p1 != NULL || p2 != NULL) {
        int x = p1 ? p1->data : 0;
        int y = p2 ? p2->data : 0;

        int diff = x - y - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        addatfront(&result, diff);

        if (p1) p1 = p1->next;
        if (p2) p2 = p2->next;
    }
    r.l=result;
    r=truncate(r);
    return r;
}
struct BigInteger mul(struct BigInteger a, struct BigInteger b)
{
   
    struct BigInteger r;
    r.l = NULL;
    r.sign=a.sign*b.sign ;
    struct node*p1=a.l;
    struct node*p2=b.l;
    int carry=0;
    struct node* sum;
    struct node*result=NULL,*itr1=NULL,*multi,*temp=NULL;
    while(p2)
    {
        struct node*res1=NULL;
        struct node *itr=p1;
       
        carry=0;
        while(itr)
        {
            int mul=itr->data*(p2!= NULL ? p2->data : 0)+carry;
            if(res1==NULL)
            {
                res1=newnode(mul%10);
                itr1=res1;
            }
            else
            {
                itr1->next=newnode(mul%10);
                itr1=itr1->next;
            }
            carry=mul/10;
            itr=itr->next;
        }
        for (int i = 0; i < carry; i++) {
            itr1->next=newnode(carry);
            itr1=itr1->next;
            carry = carry / 10;
        }
    
        if(result==NULL)
        {
            result=res1;
            multi=res1;
        }
      
        if(temp!=NULL)
        {
            addAtEnd(&temp,0);
            temp=temp->next;
            sum=addition(res1,temp);
            multi->next=sum;
            multi=multi->next;
            temp=multi;
            
        }
        else
        {
        temp=res1;
        }
        p2=p2->next;
    }
    r.l=rev(result);
    r=truncate(r);
    return r;
    
}
struct BigInteger div1(struct BigInteger a,struct BigInteger b)
{
    struct BigInteger dl;
    dl.l=NULL;
    dl.sign=a.sign*b.sign;
    struct node*d=NULL,*val=NULL;
    int c=1;
    struct node*res=b.l,*res2=b.l;
    struct node* permanent=a.l;

    if(b.length==1 && b.l->data==0)
    {
        printf("Invalid input\n");
        return b;
    }
    if(compare(a.l,b.l)<0)//h1 is smaller than h2
    {
        dl.l=newnode(0);
        dl.length=1;
        return truncate(dl);
    }
    while(compare(permanent,res2)>0)
    {
        val=addition(res2,res);
        res2=val;
        c++;
    }
    if(compare(permanent,res2)!=0)
    c-=1;
    while(c!=0)
    {
        addAtEnd(&d,c%10);
        c=c/10;
    }
    dl.l=rev(d);
    dl.length=length(d);
    dl=truncate(dl);
    return dl;
}

struct BigInteger mod(struct BigInteger a, struct BigInteger b)
{
    
    struct node*val=NULL;
    struct node*res=b.l,*res2=b.l,*temp=NULL;
    struct BigInteger mod;
    struct BigInteger t;
    if(a.l->data==0 && a.length==1)
        {
            mod.l=newnode(0);
            return mod;
        }
    if(b.length==1 && b.l->data==0)
    {
        printf("Invalid input\n");b.l=NULL;
        return b;
    }
    if(compare(a.l,b.l)<0)//h1 is smaller than h2
    {
        if(a.sign==b.sign)
        {
            mod.l=rev(addition(a.l,newnode(0)));mod.sign=b.sign;
        }
        else
        {
        t.l=b.l;
        t.sign=a.sign;
        mod=sub(a,t);mod.sign=b.sign;
        }
        return truncate(mod);
    }
    
    while(compare(a.l,res2)>=0)
    {
        temp=res2;
        val=addition(res2,res);
        res2=val;
    }
    if(a.sign==b.sign)
        t.l=temp;
    else
    t.l=res2;
    t.sign=a.sign;
    
    mod=sub(a,t);
    mod.sign=b.sign;
    mod=truncate(mod);
    return mod;
}
struct BigInteger truncate(struct BigInteger n)
{
    while(n.l!=NULL)
    {
        if(n.l->data==0)
        n.l=n.l->next;
        else
        break;
    }
    if(!n.l)
    {
    n.l=newnode(0);
    n.length=1;
    n.sign=1;
    }
    return n;
}
void addAtEnd(struct node** head,int data)
{
    struct node* temp=(struct node*)malloc(sizeof(struct node));
    if(!temp)
    {
        printf("Memory allocation failed\n");
        return;
    }
    temp->data=data;
    temp->next=NULL;
    if(!*head)
    {
        *head=temp;
        return;
    }
    struct node *itr=*head;
    while(itr->next)
    {
        itr=itr->next;
    }
    itr->next=temp;
}
void display(struct BigInteger n1) {

    if (!n1.l) {
        printf("Empty");
        return;
    }
    if(n1.sign==-1)
    printf("-");

    while (n1.l) {
        printf("%d", n1.l->data);
        n1.l = n1.l->next;
    }
    printf("\n");
}
void addatfront(struct node** n1, int data)
 {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    if (!temp) {
        printf("Memory allocation failed\n");
        return;
    }
    temp->data = data;
    temp->next = *n1;
    *n1 = temp;
}
 struct node* newnode(int data)
{
     struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}
struct BigInteger initialize(char* s) {
    struct BigInteger n1;
    n1.l = NULL;
    n1.length = 0;
    n1.sign = 1;  // Set the appropriate sign (1 for positive, -1 for negative)

    for (int i = 0; i < strlen(s); i++) 
    {
        if (s[i] >= '0' && s[i] <= '9') 
        {
            addatfront(&(n1.l), (s[i] - '0'));
            n1.length++;
        } 
        else if (s[i] == '-')
        {
            n1.sign = -1; // Handle negative sign
        }
    }
    return n1;
}
int length(struct node* head)
{
    int count = 0;
    while (head)
    {
        count++;
        head = head->next;
    }
    return count;
}
struct node*rev(struct node*head)
{
     struct node*temp1=NULL;
    struct node*temp2=NULL;
    while( head!=NULL)
    {
        temp2=(head)->next;
        (head)->next=temp1;
        temp1= head;
        (head)=temp2;
    }
    head=temp1;
    return head;
}
int compare(struct node *h1, struct node *h2)
{
    int flag=0;
    if(length(h1)!=length(h2))
        return (length(h1)<length(h2)?-1:1);
    else{
       
        struct node *itr1=rev(h1), *itr2=rev(h2);
        struct node*cur1=itr1,*cur2=itr2;
        while(itr1!=NULL){
            if(itr1->data < itr2->data)
            {
                flag=-1;
                break;
            }
            if(itr1->data > itr2->data)
            {
                flag=1;
                break;
            }
            itr1=itr1->next;
            itr2=itr2->next;
        }
        h1=rev(cur1);
        h2=rev(cur2);
        return flag;    
    }
    
}
struct node* addition(struct node* p1, struct node* p2) {
   int carry = 0;
    struct node* result = NULL;

    while (p1 != NULL || p2 != NULL || carry) {
        int sum = carry + (p1 ? p1->data : 0) + (p2 ? p2->data : 0);
        carry = sum / 10;
        sum %= 10;

        addAtEnd(&result, sum);

        if (p1) p1 = p1->next;
        if (p2) p2 = p2->next;
    }
    return result;
}
