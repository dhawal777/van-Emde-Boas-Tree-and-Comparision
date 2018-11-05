#include<bits/stdc++.h>
using namespace std;
int count1=0;
// int r,s;
struct node
{
    int data;
    struct node *left,*right;
    int h;
    vector<pair<int,int>> start;
    
    struct node *parent;
    int k;
    int c;
};
//struct node *root2;



///////////////////////////////////////////
////////////////TRAVERSE

////////////////////////////////////////////
bool traverse(struct node* root,int value)
{
    if(root->data==value)
        return true;
    else if(root->left==NULL&&root->right==NULL)
        return false;
    else if(root->left==NULL&&value<root->data)
        return false;
    else if(root->right==NULL&&value>root->data)
        return false;
    else if(value<root->data)
        return traverse(root->left,value);
    else
        return traverse(root->right,value);
}
//struct node* root=NULL;
int height(struct node *root)
{
    if(root==NULL)
    return 0;
    else
    return root->h;
}
int k_cal(struct node *root)
{
    if(root==NULL)
    return 0;
    else
    return root->k;
}
int balance_factor(struct node * root)
{
    int x,y;
    if(root->left!=NULL)
     x=root->left->h;
    else
      x=0;
    if(root->right!=NULL)
       y=root->right->h;
    else
        y=0;
    return x-y;
}

struct node* rotate_left(struct node *root)
{
        struct node *temp,*temp1;
        temp=root->right;
        temp1=root->right->left;
        temp->left=root;
        root->right=temp1;
      root->h = max(height(root->left),height(root->right))+1;
      root->k=k_cal(root->left)+k_cal(root->right)+1;
      temp->h = max(height(temp->left),height(temp->right))+1;
      //temp->k=height(temp->left)+height(temp->right);
      temp->k=k_cal(temp->left)+k_cal(temp->right)+1;
        return temp;
}
struct node* rotate_right(struct node *root)
{
        struct node *temp,*temp1;
        temp=root->left;
        temp1=root->left->right;
        temp->right=root;
        root->left=temp1;
       
      root->h = max(height(root->left),height(root->right))+1;
      root->k=k_cal(root->left)+k_cal(root->right)+1;
      temp->h = max(height(temp->left),height(temp->right))+1;
      temp->k=k_cal(temp->left)+k_cal(temp->right)+1;
      return temp;
}
struct node* insert(struct node *root,int x,int y,int value)
{

    if(root==NULL)
    {
        // cout<<"ddklld "<<x<<" ss'l'ls "<<y<<endl;
        struct node *temp;
    temp=(struct node*)malloc(sizeof(struct node));
    temp->data=value;
    temp->left=NULL;
    temp->right=NULL;
    temp->h=1;
    temp->k=1;
         temp->start.clear();
        temp->start.push_back(make_pair(x,y));
        // temp->end.push_back(y);
         temp->c=1;
        //root=temp;
        // cout<<"check insert "<<temp->start[0].first<<" "<<temp->start[0].second<<endl;
        return temp;
    }
    if(value==root->data)
    {
        // cout<<"together"<<endl;
        root->start.push_back(make_pair(x,y));
        root->c+=1;
    }
    else if(value<root->data)
           { 
               //cout<<"hello"<<endl;
               root->left=insert(root->left,x,y,value);
               root->left->parent=root;
               //cout<<"champ"<<endl;
           }
    else
        {
            root->right=insert(root->right,x,y,value);
            root->right->parent=root;
        }
    
    root->h=max(height(root->left),height(root->right))+1;
     //root->k=height(root->left)+height(root->right);
    root->k=k_cal(root->left)+k_cal(root->right)+1;
    int l=height(root->left);
    int r=height(root->right);
    //cout<<l<<" "<<r<<endl;
    if(l-r>1)
    {
       
       int l1=balance_factor(root->left);
       //cout<<l1<<endl;
       if(l1>=0)
       {
              return rotate_right(root);
       }
       else
       {
             root->left=rotate_left(root->left);
             root->left->parent=root;
             return rotate_right(root);
       }
    }
    if(r-l>1)
    {
       
       int l1=balance_factor(root->right);
       if(l1>=0)
       {
               root->right=rotate_right(root->right);
               root->right->parent=root;
             return rotate_left(root);
       }
       else
       {
           return rotate_left(root); 
       }
    }
    // cout<<"kflkdllflfl "<<root->start<<"scknk "<<root->end<<endl;
    return root;
   
 }
void inorder(struct node *head)
{
  if(head==NULL)
    return;
    
  inorder(head->left);
  printf("%d ",head->data);
  inorder(head->right);
}

struct node * inorder_succ(struct node* root)
{
    struct node* temp=root;
    while (temp->left != NULL)
        temp = temp->left;
 
    return temp;
}

struct node* delete1(struct node* root,int start1,int end1, int value)
{
 
    if (root == NULL)
    {
        // cout<<"cricko"<<endl;
        return root;
    }
    else if ( value < root->data )
        root->left = delete1(root->left,start1,end1,value);
    else if( value > root->data )
        root->right = delete1(root->right,start1,end1,value);
    // else if(value==root->data&&root->c>1)
    // {
    //     cout<<"here "<<root->start<<"here1 "<<root->end<<endl;
    //     root->right= delete1(root->right,start1,end1,value);
    // }
    else
    {
         //cout<<"DOing"<<endl;
    
        if( (root->left == NULL) || (root->right == NULL) )
        {
           struct node *temp;
          if(root->left==NULL&&root->right==NULL)
          temp=NULL;
          else if(root->left!=NULL)
          temp=root->left;
          else
          temp=root->right;
 
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else 
             *root = *temp; 
            free(temp);
        }
        else
        {
        //    cout<<"DO"<<endl;
            struct node* temp = inorder_succ(root->right);
            // int x1=root->start;
            // int y1=root->end;
            // cout<<"INORDER SUC "<<temp->data<<endl;
             root->data = temp->data;
             root->start.clear();
             for(int i=0;i<temp->c;i++)
             {
                 root->start.push_back(temp->start[i]);
             }
            //  root->end=temp->end;
            // start1=temp->start;

            // end1=temp->end;
            // cout<<"START1 "<<start1<<"END1 "<<end1<<endl;
            root->c=temp->c;
            root->right = delete1(root->right,start1,end1,temp->data);
        }
    }
 
    if (root == NULL)
      return root;
    
 
root->h=max(height(root->left),height(root->right))+1;
     //root->k=height(root->left)+height(root->right);
    root->k=k_cal(root->left)+k_cal(root->right)+1;
    int l=height(root->left);
    int r=height(root->right);
  //cout<<l<<" "<<r<<endl;
  if(l-r>1)
  {
       
       int l1=balance_factor(root->left);
       //cout<<l1<<endl;
       if(l1>=0)
       {
              return rotate_right(root);
       }
       else
       {
             root->left=rotate_left(root->left);
             root->left->parent=root;
             return rotate_right(root);
       }
  }
  if(r-l>1)
  {
       
       int l1=balance_factor(root->right);
       if(l1>=0)
       {
               root->right=rotate_right(root->right);
               root->right->parent=root;
             return rotate_left(root);
       }
       else
       {
           return rotate_left(root); 
       }
  }
  return root;
   
 }

struct node* kthmin(struct node *root,int y)
{
    //cout<<"hello"<<endl;
    int t=k_cal(root->left);
   if(t==y-1)
   return root;
   else if(t>y-1)
   {
      // cout<<"leftk "<<root->left->k<<" "<<root->endl;
       //cout<<"y "<<y<<endl;
   return kthmin(root->left,y);
   }
   else
   {
      // cout<<"leftr "<<root->data<<endl;
   return kthmin(root->right,y-(t)-1);
   }
   
   
}
/*struct node* inorder1(struct node *root,int y)
{
    //struct node *temp;
    if(root==NULL)
    return root;
    struct node *temp;
    
    

   
    temp=inorder1(root->left,y);
    if(temp!=NULL)
    return temp;                 //preordeer
    count1=count1+1;
   // cout<<root->data<<" "<<count1<<" ";
   // cout<<"mmnb"<<endl;
    if(count1==y)
        return root; 
    temp=inorder1(root->right,y);
       //return temp;
}
*/
int main()
{
    int n,m,x;
    cin>>n>>m;
    vector<vector<pair<int,int>>> v(100005);
    int visited[100005]={0};
    int w,y,i;
    for(i=0;i<m;i++)
    {
        cin>>x>>y>>w;
        v[x].push_back(make_pair(y,w));
        v[y].push_back(make_pair(x,w));
    }
    
    int count1=1;
//   //  insert()
     struct node *root1=NULL;
     root1=insert(root1,0,0,0);
    //  cout<<root1->c<<" "<<root1->end<<endl;
    // cout<<"champ2 "<<root1->c<<endl;
    //  root1=insert(root1,0,1,3);
    // //  cout<<root1->start<<" "<<root1->end<<endl;
    //  root1=insert(root1,0,2,3);
    // //  cout<<root1->start<<" "<<root1->end<<endl;
    //  root1=insert(root1,1,2,3);
    //  cout<<"champ "<<root1->right->c<<endl;
    //  cout<<root1->start<<" "<<root1->end<<endl;
    //   cout<<root1->right->start<<" "<<root1->right->end<<endl;
    // cout<<root1->right->right->start<<" "<<root1->right->right->end<<endl;
    // cout<<root1->right->right->right->start<<" "<<root1->right->right->right->end<<endl;
    int sum=0;
    while(count1!=n+1)
    {
      
        //   cout<<"root1 data "<<root1->start<<"ssllsl "<<root1->end<<"k "<<root1->k<<endl;
           struct node *temp=kthmin(root1,1);
        // cout<<"temp->data "<<temp->data<<endl;
           int r=temp->start[0].first;
           int s=temp->start[0].second;
           
        // cout<<"r "<<r<<"s "<<s<<endl;
           bool flag=false;
           if(visited[r]==0)
           {
               int n1=v[r].size();
               for(i=0;i<n1;i++)
               {
                 if(visited[v[r][i].first]==0)
                 {
                     //cout<<"champ"<<endl;
                     //cout<<v[r][i].first<<endl;
                    // cout<<"champ1"<<endl;
                    //  if(root1!=NULL)
                    //    {
                    //    bool f=traverse(root1,v[r][i].second);
                    //    if(f==1)
                    //    continue;
                    //    }
                    // cout<<"first "<<r<<"second "<<v[r][i].first<<endl;
                     root1=insert(root1,r,v[r][i].first,v[r][i].second);
                 }
               }
               visited[r]=1;
              // count1++;
               flag=true;
               
           }
           if(visited[s]==0)
           {
               int n1=v[s].size();
               for(i=0;i<n1;i++)
               {
                 if(visited[v[s][i].first]==0)
                 {
                    //   if(root1!=NULL)
                    //    {
                    //    bool f=traverse(root1,v[s][i].second);
                    //    if(f==1)
                    //    continue;
                    //    }
                    // cout<<"first1 "<<s<<"second1 "<<v[s][i].first<<endl;
                     root1=insert(root1,s,v[s][i].first,v[s][i].second);
                 }
               }
               visited[s]=1;
               //count1++;
               flag=true;
               
           }
           if(flag==true)
               {
                   sum=sum+temp->data;
                   count1++;
               }
        //    cout<<"sum "<<sum<<endl;
           if(temp->c>1)
           {
               temp->c--;
               temp->start.erase(temp->start.begin());
           }
           else
           {
           root1=delete1(root1,r,s,temp->data);
           }
            // root1->parent=NULL;
      //  cout<<"ciunt1 "<<count1<<endl;
    }
    cout<<sum<<endl;

}

