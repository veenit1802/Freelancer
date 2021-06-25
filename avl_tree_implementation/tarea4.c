#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
struct TreeNode
{
    char name[200];
    float data;
    struct TreeNode *left, *right;
};


struct TreeNode *createNode(float data,char s[],int size)
{   
    struct TreeNode *newNode = (struct TreeNode *)(malloc(sizeof(struct TreeNode)));
    for(int i=0;i<size;i++)
    {
        newNode->name[i]=s[i];
        newNode->name[i+1]='\0';
    }
    newNode->data=data;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}


int height(struct TreeNode *node)
{
    if(node==NULL)
    {
        return -1;
    }

    int left = height(node->left)+1,right = height(node->right)+1;

    return (left>right?left:right);
    
}


int getBalanceFactor( struct TreeNode *n)
{
    if(n==NULL)
    {
        return -1;
    }
    else{
        return height(n->left) - height(n->right);
    }
}

struct TreeNode* rightRotation(struct TreeNode *node)
{
    struct TreeNode *x = node->left;
    struct TreeNode *T2 = x->right;


    x->right = node;
    node->left = T2;
    return x;
}

struct TreeNode* leftRotation(struct TreeNode *node)
{
    struct TreeNode *y = node->right;
    struct TreeNode *T2 = y->left;

    y->left = node;
    node->right = T2;

    return y;
}




struct TreeNode* insertIn(struct TreeNode* root,struct TreeNode *newNode)
{
    if(root==NULL)
    {
        root=newNode;
        return root;
    }
    else if( newNode->data < root->data  )
    {
        root->left = insertIn( root->left,newNode);
    }
    else if(newNode->data > root->data)
    {
        root->right = insertIn(root->right,newNode);
    }
    else{
        return root;
    }

    int bf = getBalanceFactor(root);
    if( bf>1 && newNode->data < root->left->data )
    {
        return rightRotation(root);
    }
    if(bf<-1 && newNode->data > root->right->data)
    {
        return leftRotation(root);
    }
    if(bf>1 && newNode->data > root->left->data)
    {
        root->left=leftRotation(root->left);
        return rightRotation(root);
    }
    else if(bf<-1 && newNode->data < root->right->data)
    {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }
    return root;
}


void display(struct TreeNode* root)
{
    if(root==NULL)
    {
        return ;
    }
    printf("%s %f\n",root->name,root->data);
    display(root->left);
    display(root->right);
}

float findMinNum(struct TreeNode *root)
{
    if(root==NULL)
        return 0;
    if(root->left==NULL)
    {
        return root->data;
    }
    return findMinNum(root->left);
}

float findMaxNum(struct TreeNode *root)
{
    if(root==NULL)
    {
        return 0;
    }
    if(root->right==NULL)
    {
        return root->data;
    }
    return findMinNum(root->right);
}


int main(int argc,char **argv)
{
    if(argc!=2)
    {
        printf("Insufficient parameters are given\n");
        return 0;
    }

    FILE *fin;
    
    if(!(fin = fopen(argv[1],"r")))
    {
        printf("File does not exists");
    }

    char s[8000];
    fgets(s,(int)sizeof(s),fin);
    struct TreeNode *root=NULL;
    int totalstudent=0;
    float overallSum=0.0;
    while(fgets(s,(int)sizeof(s),fin))
    {
        totalstudent++;
        int length = strlen(s);
        int strlength=0;
        for(int i=0;i<length && s[i]!=',';i++)
        {
            strlength++;
        }
        char newStr[strlength+1];
        for(int i=0;i<strlength;i++)
        {
            newStr[i] = s[i];
            newStr[i+1]='\0';
        }
        float num=0;
        int k=0,cnt=0;
        while ( !(s[length-1]>='0' && s[length-1]<='9'))
        {
            length--;
        }
        int totele=0;
        float avg=0.0;
        for(int i=strlength+1;i<length;i++)
        {
            if(s[i]==',')
            {
                k=0;
                num = num/ pow(10.0,cnt);
                cnt=0;
                totele++;
                avg+=num;
                num=0;
            }
            else if(s[i]!='.')
            {
                num = num*10 + (int)(s[i]-'0');
            }
            else if(s[i]=='.')
            {
                k=1;
            }
            if(k && s[i]!='.' && s[i]!=',')
            {
                cnt++;
            }
        }
        num/=pow(10.0,cnt);
        totele+=1;
        avg+=num;
        avg=avg/totele;
        overallSum+=avg;
        struct TreeNode *obj = createNode(avg,newStr,strlength);
        root = insertIn(root,obj);
    }
    overallSum/=totalstudent;
    FILE *fout = fopen("out.txt","w");
    fprintf(fout,"numero de alumnos: %d\n",3);
    fprintf(fout,"Promedio: %0.1f\n",overallSum);
    fprintf(fout,"minimo: %0.1f\n",findMinNum(root));
    fprintf(fout,"maximo: %0.1f\n",findMaxNum(root));


    return 0;
}