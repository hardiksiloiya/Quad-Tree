#include<bits/stdc++.h>
using namespace std;


class quad_tree{
    int x1;
    int y1;
    int x2;
    int y2;
    int matrix_size;
    int val;
    quad_tree *topleft,*topright,*bottomleft,*bottomright;

    public:
    /*~quad_tree()
    {
        if(topleft)
        {
            topright->~quad_tree();
            topleft->~quad_tree();
            bottomright->~quad_tree();
            bottomleft->~quad_tree();
        }
    }*/
    void delfunc(quad_tree* t)
    {
        if(t==NULL)
        return;
        if(t->bottomleft)
        {
            delfunc(t->bottomleft);
            delfunc(t->bottomright);
            delfunc(t->topleft);
            delfunc(t->topright);
        }
        delete t;
    }
    quad_tree(int n,int value=0,int a=0,int b=0)
    {
        val=value;
        x1=a;
        y1=b;
        x2=a+pow(2,n)-1;
        y2=b+pow(2,n)-1;
        matrix_size=n;
        topleft=topright=bottomleft=bottomright=NULL;
    }

    int size() const{
        return matrix_size;
    }

    void func(quad_tree* t1,quad_tree* t2)
    {
        if(t2==NULL)
        return;
        t1->val=t2->val;
        t1->x1=t2->x1;
        t1->y1=t2->y1;
        t1->x2=t2->x2;
        t1->y2=t2->x2;
        t1->matrix_size=t2->matrix_size;
        if(t2->topright)
        {
            t1->topright=new quad_tree(0);
            t1->topleft=new quad_tree(0);
            t1->bottomleft=new quad_tree(0);
            t1->bottomright=new quad_tree(0);
            func(t1->bottomright,t2->bottomright);
            func(t1->bottomleft,t2->bottomleft);
            func(t1->topleft,t2->topleft);
            func(t1->topright,t2->topright);
        }
        
    }

    quad_tree(quad_tree const &Q)
    {
        val=Q.val;
        x1=Q.x1;
        x2=Q.x2;
        y1=Q.y1;
        y2=Q.y2;
        matrix_size=Q.matrix_size;
        if(Q.bottomright)
        {
            topright=new quad_tree(0);
            topleft=new quad_tree(0);
            bottomleft=new quad_tree(0);
            bottomright=new quad_tree(0);
            func(bottomright,Q.bottomright);
            func(bottomleft,Q.bottomleft);
            func(topleft,Q.topleft);
            func(topright,Q.topright);
            
        }
    }
    
    bool lies(int x1,int y1,int x2,int y2,int a,int b,int c,int d)
    {
    if(x1<=a&&c<=x2)
    if(y1<=b&&d<=y2)
    return true;

    return false;
    }

    bool partialies(int x1,int y1,int x2,int y2,int a,int b,int c,int d)
    {
    if(x1>c||a>x2)
    return false;
    if(d<y1||b>y2)
    return false;
    return true;
    }
    
    void set(int a,int b,int c,int d,int value)
    {
        //cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
        //cout<<a<<b<<c<<d<<endl;
       // cout<<int(lies(a,b,c,d,x1,y1,x2,y2))<<endl;
        
        
        if(lies(a,b,c,d,x1,y1,x2,y2))
        {
           // cout<<"inserted at "<<x1<<y1<<x2<<y2<<endl;
            val=value;
            if(topright)
            {
                delfunc(bottomleft);
                delfunc(bottomright);
                delfunc(topleft);
                delfunc(topright);
            }

            bottomleft=NULL;
            bottomright=NULL;
            topleft=NULL;
            topright=NULL;
            return;
        }
       // cout<<"noice";
        if(!partialies(x1,y1,x2,y2,a,b,c,d))
        {
           // cout<<"sed "<<a<<" "<<b<<" "<<c<<" "<<d<<endl;
            return;
        }

        int temp=pow(2,matrix_size-1)-1;

        if(!bottomleft)
        {
            bottomleft=new quad_tree(matrix_size-1,val,x1,y1+temp+1);
            bottomright=new quad_tree(matrix_size-1,val,x1+temp+1,y1+temp+1);
            topleft=new quad_tree(matrix_size-1,val,x1,y1);
            topright=new quad_tree(matrix_size-1,val,x1+temp+1,y1);
        }
        bottomleft->set(a,b,c,d,value);
        bottomright->set(a,b,c,d,value);
        topleft->set(a,b,c,d,value);
        topright->set(a,b,c,d,value);
        if(bottomleft)
        {
            if(bottomleft->bottomleft==NULL&&topleft->bottomleft==NULL&&topright->bottomleft==NULL&&bottomright->bottomright==NULL)
            {
                int temp=bottomright->val;
                if(bottomleft->val==temp&&topright->val==temp&&topleft->val==temp)
                {
                   // cout<<"deleting"<<x1<<y1<<x2<<y2<<"  val  "<<temp<<endl;

                    val=temp;
                    delfunc(bottomleft);
                    delfunc(bottomright);
                    delfunc(topleft);
                    delfunc(topright);

                    topright=NULL;
                    topleft=NULL;
                    bottomright=NULL;
                    bottomleft=NULL;
                }
            }
        }

    }

    void boolor(quad_tree* t1,quad_tree* t2)
    {
        if(t2==NULL)
        return;
        if(t2->bottomleft==NULL&&t2->val!=0)
        {
            
            if(t1->bottomleft==NULL&&t1->val==1)
            {
            }
            else if(t1->x1==t2->x1&&t1->x2==t2->x2&&t1->y1==t2->y1&&t1->y2==t2->y2)
            {
                t1->val=1;
                if(t1->bottomleft)
                {
                    delfunc(t1->bottomleft);
                    delfunc(t1->bottomright);
                    delfunc(t1->topleft);
                    delfunc(t1->topright);
                }
                t1->bottomright=NULL;
                t1->bottomleft=NULL;
                t1->topright=NULL;
                t1->topleft=NULL;
              //  cout<<t1->x1<<t1->y1<<t1->x2<<t1->y2<<"noice"<<endl;
                
            }
            else if(lies(t1->x1,t1->y1,t1->x2,t1->y2,t2->x1,t2->y1,t2->x2,t2->y2))
            {
                if(t1->topright==NULL)
                {
                    int temp=pow(2,t1->matrix_size-1)-1;

                    t1->bottomleft=new quad_tree(t1->matrix_size-1,t1->val,t1->x1,t1->y1+temp+1);
                    t1->bottomright=new quad_tree(t1->matrix_size-1,t1->val,t1->x1+temp+1,t1->y1+temp+1);
                    t1->topleft=new quad_tree(t1->matrix_size-1,t1->val,t1->x1,t1->y1);
                    t1->topright=new quad_tree(t1->matrix_size-1,t1->val,t1->x1+temp+1,t1->y1);
                }
                boolor(t1->bottomright,t2);
                boolor(t1->bottomleft,t2);
                boolor(t1->topright,t2);
                boolor(t1->topleft,t2);
            }
            else
            {
              //  cout<<"sad"<<endl;
                
            }

        }
        else
        {
            boolor(t1,t2->bottomleft);
            boolor(t1,t2->bottomright);
            boolor(t1,t2->topleft);
            boolor(t1,t2->topright);
        }

        if(t1->bottomleft)
        {
            if(t1->bottomleft->bottomleft==NULL&&t1->topleft->bottomleft==NULL&&t1->topright->bottomleft==NULL&&t1->bottomright->bottomright==NULL)
            {
                int temp=t1->bottomright->val;
                if(t1->bottomleft->val==temp&&t1->topright->val==temp&&t1->topleft->val==temp)
                {
                    //cout<<"deleting"<<t1->x1<<t1->y1<<t1->x2<<t1->y2<<"  val  "<<temp<<endl;

                    t1->val=temp;
                    delfunc(t1->bottomleft);
                    delfunc(t1->bottomright);
                    delfunc(t1->topleft);
                    delfunc(t1->topright);

                    t1->topright=NULL;
                    t1->topleft=NULL;
                    t1->bottomright=NULL;
                    t1->bottomleft=NULL;
                }
            }
        }
        
    }

    void overlap(quad_tree &Q)
    {

        boolor(this,&Q);
    }

    void booland(quad_tree* t1,quad_tree* t2)
    {
       // cout<<"done intersect";
        if(t2==NULL)
        return;
        if(t2->bottomleft==NULL&&t2->val!=1)
        {
            if(t1->bottomleft==NULL&&t1->val==0)
            {
                
            }
            else if(t1->x1==t2->x1&&t1->x2==t2->x2&&t1->y1==t2->y1&&t1->y2==t2->y2)
            {
                t1->val=0;
                if(t1->bottomleft)
                {
                    delfunc(t1->bottomleft);
                    delfunc(t1->bottomright);
                    delfunc(t1->topleft);
                    delfunc(t1->topright);
                }
                t1->bottomright=NULL;
                t1->bottomleft=NULL;
                t1->topright=NULL;
                t1->topleft=NULL;
              //  cout<<t1->x1<<t1->y1<<t1->x2<<t1->y2<<"noice"<<endl;
                return;
            }
            else if(lies(t1->x1,t1->y1,t1->x2,t1->y2,t2->x1,t2->y1,t2->x2,t2->y2))
            {
                if(t1->topright==NULL)
                {
                    int temp=pow(2,t1->matrix_size-1)-1;

                    t1->bottomleft=new quad_tree(t1->matrix_size-1,t1->val,t1->x1,t1->y1+temp+1);
                    t1->bottomright=new quad_tree(t1->matrix_size-1,t1->val,t1->x1+temp+1,t1->y1+temp+1);
                    t1->topleft=new quad_tree(t1->matrix_size-1,t1->val,t1->x1,t1->y1);
                    t1->topright=new quad_tree(t1->matrix_size-1,t1->val,t1->x1+temp+1,t1->y1);
                }
                booland(t1->bottomright,t2);
                booland(t1->bottomleft,t2);
                booland(t1->topright,t2);
                booland(t1->topleft,t2);
            }
            else
            {
              //  cout<<"sad"<<endl;
                return;
            }

        }
        else
        {
            booland(t1,t2->bottomleft);
            booland(t1,t2->bottomright);
            booland(t1,t2->topleft);
            booland(t1,t2->topright);
        }

        if(t1->bottomleft)
        {
            if(t1->bottomleft->bottomleft==NULL&&t1->topleft->bottomleft==NULL&&t1->topright->bottomleft==NULL&&t1->bottomright->bottomright==NULL)
            {
                int temp=t1->bottomright->val;
                if(t1->bottomleft->val==temp&&t1->topright->val==temp&&t1->topleft->val==temp)
                {
                    //cout<<"deleting"<<t1->x1<<t1->y1<<t1->x2<<t1->y2<<"  val  "<<temp<<endl;

                    t1->val=temp;
                    delfunc(t1->bottomleft);
                    delfunc(t1->bottomright);
                    delfunc(t1->topleft);
                    delfunc(t1->topright);

                    t1->topright=NULL;
                    t1->topleft=NULL;
                    t1->bottomright=NULL;
                    t1->bottomleft=NULL;
                }
            }
        }
        
    }

    void intersect(quad_tree &Q)
    {
       // cout<<"noice"<<endl;
        booland(this,&Q);
    }

    void complement()
    {
        val^=1;
        if(bottomleft)
        bottomleft->complement();
        if(bottomright)
        bottomright->complement();
        if(topleft)
        topleft->complement();
        if(topright)
        topright->complement();
    }

    int get(int a,int b)
    {
        if(a<x1||b>y2||b<y1||a>x2)
        return -1;
        if(bottomleft)
        {
            if(a>=bottomleft->x1&&a<=bottomleft->x2&&b>=bottomleft->y1&&b<=bottomleft->y2)
            return bottomleft->get(a,b);
            else if(a>=bottomright->x1&&a<=bottomright->x2&&b>=bottomright->y1&&b<=bottomright->y2)
            return bottomright->get(a,b);
            else if(a>=topleft->x1&&a<=topleft->x2&&b>=topleft->y1&&b<=topleft->y2)
            return topleft->get(a,b);
            else if(a>=topright->x1&&a<=topright->x2&&b>=topright->y1&&b<=topright->y2)
            return topright->get(a,b);
        }
        return val;
    }

    /*int onecount(quad_tree* t)
    {
        if(t->bottomleft==NULL)
        {
            if(t->val==1)
            return 1;
            else
            return 0;
        }
        return onecount(t->bottomleft)+onecount(t->bottomright)+onecount(t->topleft)+onecount(t->topright);
    }

    int zerocount(quad_tree* t)
    {
        if(t->bottomleft==NULL)
        {
            if(t->val==0)
            return 1;
            else
            return 0;
        }
        return zerocount(t->bottomleft)+zerocount(t->bottomright)+zerocount(t->topleft)+zerocount(t->topright);
    }

    void compress(quad_tree* t,int m)
    {
        if(m==t->matrix_size)
        {
            if(onecount(t)>zerocount(t))
            t->val=1;
            else
            {
                t->val=0;
            }
            matrix_size=1;
            if(t->bottomleft)
            {
                delfunc(t->bottomleft);
                delfunc(t->bottomright);
                delfunc(t->topleft);
                delfunc(t->topright);
                t->topright=NULL;
                t->topleft=NULL;
                t->bottomright=NULL;
                t->bottomleft=NULL;

            }
            return;            
        }
        else
        {
            if(t->bottomleft==NULL)
            {
                int temp=pow(2,t->matrix_size-1)-1;

                t->bottomleft=new quad_tree(t->matrix_size-1,t->val,t->x1,t->y1+temp+1);
                t->bottomright=new quad_tree(t->matrix_size-1,t->val,t->x1+temp+1,t->y1+temp+1);
                t->topleft=new quad_tree(t->matrix_size-1,t->val,t->x1,t->y1);
                t->topright=new quad_tree(t->matrix_size-1,t->val,t->x1+temp+1,t->y1);

            }
            compress(t->bottomleft,m);
            compress(t->bottomright,m);
            compress(t->topleft,m);
            compress(t->topright,m);
        }

        t->matrix_size=2*min(t->bottomright->matrix_size,min(t->bottomleft->matrix_size,min(t->topright->matrix_size,t->topleft->matrix_size)));

        if(t->bottomleft->bottomleft==NULL&&t->topleft->bottomleft==NULL&&t->topright->bottomleft==NULL&&t->bottomright->bottomright==NULL)
        {
            int temp=t->bottomright->val;
            if(t->bottomleft->val==temp&&t->topright->val==temp&&t->topleft->val==temp)
            {
                    //cout<<"deleting"<<t1->x1<<t1->y1<<t1->x2<<t1->y2<<"  val  "<<temp<<endl;

                delfunc(t->bottomleft);
                delfunc(t->bottomright);
                delfunc(t->topleft);
                delfunc(t->topright);
                t->topright=NULL;
                t->topleft=NULL;
                t->bottomright=NULL;
                t->bottomleft=NULL;
            }
        }

        
    }


    void resize(int m)
    {
        if(m<matrix_size)
        compress(this,m);
    }*/
};
/*
int main()
{
    int a,b,c,d,n,x,t,value;
    cout<<"enter size of tree - ";
    cin>>n;
    vector<quad_tree> v (2,quad_tree(n));
    cin>>t;
    while(t--)
    {
        int k;
        cout<<"enter the tree to perform operations on - ";
        cin>>k;
        cout<<"Performing on tree "<<k<<endl;

        
        cout<<"enter set(0) or get(1) or overlap(2) or size(3) or intersect(4) or complement(5) : ";
        cin>>x;
        if(x==0)
        {
            cin>>a>>b>>c>>d>>value;
            v[k].set(a,b,c,d,value);
            
        }
        else if(x==1)
        {
            cin>>a>>b;
            cout<<v[k].get(a,b)<<endl;
        }
        else if(x==3)
        {
            cout<<v[k].size();
        }
        else if(x==4)
        {
            v[0].intersect(v[1]);
            cout<<"done"<<endl;

        }
        else if(x==5)
        {
            v[k].complement();
        }
        
        else
        {
            v[0].overlap(v[1]);
            cout<<"done"<<endl;
        }
        
        
    }
    quad_tree temp(v[0]);
    cout<<temp.size()<<endl;
    return 0;
}*/