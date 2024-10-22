#include<bits/stdc++.h>

using namespace std;

struct rt{
    int i;
    vector<int> weights;
    int sum_weights;
    vector<vector<int>> bracket;
    vector<int> SLword;
};
int compare_roots(int n, vector<int>& root1, vector<int>& root2)
{
    if(root1[n+1]!=root2[n+1])
        return root1[n+1]<root2[n+1];
    int i=0;
    while(i<= n && root1[i]== root2[i] )
        i++;
    if(i==n+1)
        return 2;
    return root1[i]<root2[i];
}
int equality_roots(int n, vector<int>& root1, vector<int>& root2)
{
    for(int i =0;i<=n+1; i++)
        if(root1[i]!= root2[i])
            return 0;
    return 1;
}
int compare_letter(int i, int j)
{
    if(i==0)
        return 0;
    return i<j;
}   
int compare_word( vector<int>& a, vector<int>& b) 
{
    int n = a.size();
    int m = b.size();
    for(int i=0;i<min(n,m); i++)
    {
        if(a[i]!= b[i])
            return compare_letter(a[i],b[i]);
    }
    return n<m;
}
void subtract_root(int n, vector<int>& root1,vector<int>& root2, vector<int>& result)
{
    int flag = 0;
    for(int i=0; i<=n+1;i++)
    {
        result[i] = root1[i]-root2[i];
        if (result[i]<0)
            flag = 1;
    }
    if(flag)
    {
        result[n+1]--;
        result[0]++;
        result[1]++;
        for(int i=2;i<=n;i++)
            result[i]+=2;
    }
}
int check_finite_root(int n, vector<int>& root)
{
    if(root[1]<0|| root[1]>1 || root[0]!=0)
        return 0;
    for(int i=2;i<=n;i++)
        if(root[i]<0||root[i]>2)
            return 0;
    if(root[n]>0)
    {
        for(int i=1;i<n;i++)
            if(root[i]>root[i+1] || root[i+1]>root[i]+1)
                return 0;
        return 1;
    }
    int j=n;
    while(root[j]==0 && j>0)
        j--;
    if(root[j]==2)
    {
        return 0;
    }
    for(int i=1;i<j;i++)
        if(root[i]>root[i+1])
            return 0;
    return 1;
}
int check_root(int n, vector<int>& root)
{
    if(root[n+1]<0 || root[0]<0 || root[0]>1)
        return 0;
    if(root[0]==1 && root[2]==2)
        return 0;
    int flag = 1;
    for(int i=0;i<=n+1;i++)
        if(root[i]!=0)
            flag = 0;
    if(flag)
        return 0;
    if(root[0] == 0)
        return check_finite_root(n,root);
    vector<int> delta(n+2,0);
    vector<int> check(n+2, 0);
    delta[n+1] = root[n+1]+1;
    subtract_root( n, delta, root, check );
    return check_finite_root(n,check);
}
void conjugation_part(vector<vector<int>>& bracket1, vector<vector<int>>& bracket2, vector<int>& basis)
{
    int p = bracket1.size();
    basis.push_back(0);
    basis.push_back(bracket2[0][1]);
    basis.push_back(bracket2[0][2]);
    for(int i=0;i<p;i++)
        if(bracket1[i][2]==bracket2[0][1])
            basis[0]+= bracket1[i][0];
        else if(bracket1[i][1]==bracket2[0][2])
            basis[0]-= bracket1[i][0];
}
void conjugation(vector<vector<int>>& bracket1, vector<vector<int>>& bracket2, vector<vector<int>>& res, int n){
    if(bracket1[0][1]==bracket1[0][2] && bracket2[0][1]==bracket2[0][2])
        return;
    vector<int> basis(3,0);
    if(bracket1[0][1]==bracket1[0][2])
    {
        conjugation_part(bracket1, bracket2, basis);
        if(basis[0]!=0)
            res.push_back(basis);
    }
    else if(bracket2[0][1] == bracket2[0][2])
    {
        conjugation_part(bracket2,bracket1,basis);
        if(basis[0]!=0)
        {
            basis[0]= -basis[0];
            res.push_back(basis);
        }
    }
    else
    {
        if(bracket1[0][2]== bracket2[0][1] && bracket1[0][1]==bracket2[0][2])
        {
            basis[0] = bracket1[0][0] * bracket2[0][0];
            basis[1] = bracket1[0][1];
            basis[2] = bracket2[0][2];
            if(basis[1]+basis[2]>= 2*n+2)
            {
                int dummy = 2*n+2 - basis[1];
                basis[1] = 2*n+2-basis[2];
                basis[2] = dummy;
                basis[0]=-basis[0];
            }
            res.push_back(basis);
            vector<int> basis1(3,0);
            basis1[0]= -bracket1[0][0] * bracket2[0][0];
            basis1[1] = bracket2[0][1];
            basis1[2] = bracket1[0][2];
            if(basis1[1]+basis1[2]>= 2*n+2)
            {
                int dummy = 2*n+2 - basis1[1];
                basis1[1] = 2*n+2-basis1[2];
                basis1[2] = dummy;
                basis[0]=-basis[0];
            }
            res.push_back(basis1);
        }
        else if(bracket1[0][2]== bracket2[0][1])
        {
            basis[0] = bracket1[0][0] * bracket2[0][0];
            basis[1] = bracket1[0][1];
            basis[2] = bracket2[0][2];
            if(basis[1]+basis[2]>= 2*n+2)
            {
                int dummy = 2*n+2 - basis[1];
                basis[1] = 2*n+2-basis[2];
                basis[2] = dummy;
                basis[0]=-basis[0];
            }
            res.push_back(basis);
        }
        else if(bracket1[0][1]==bracket2[0][2])
        {
            basis[0] = -bracket1[0][0] * bracket2[0][0];
            basis[1] = bracket2[0][1];
            basis[2] = bracket1[0][2];
            if(basis[1]+basis[2]>= 2*n+2)
            {
                int dummy = 2*n+2 - basis[1];
                basis[1] = 2*n+2-basis[2];
                basis[2] = dummy;
                basis[0]=-basis[0];
            }
            res.push_back(basis);
        }
        else if(bracket1[0][1]+ bracket2[0][1]== 2*n+2)
        {
            basis[0] = bracket1[0][0] * bracket2[0][0];
            basis[1] = 2*n+2-bracket2[0][2];
            basis[2] = bracket1[0][2];
            if(basis[1]+basis[2]>= 2*n+2)
            {
                int dummy = 2*n+2 - basis[1];
                basis[1] = 2*n+2-basis[2];
                basis[2] = dummy;
                basis[0]=-basis[0];
            }
            res.push_back(basis);
        }
        else if(bracket1[0][2]+ bracket2[0][2]== 2*n+2)
        {
            basis[0] = -bracket1[0][0] * bracket2[0][0];
            basis[1] = bracket1[0][1];
            basis[2] = bracket1[0][2];
            if(basis[1]+basis[2]>= 2*n+2)
            {
                int dummy = 2*n+2 - basis[1];
                basis[1] = 2*n+2-basis[2];
                basis[2] = dummy;
                basis[0]=-basis[0];
            }
            res.push_back(basis);
        }
    }
}
void add_list_real(vector<struct rt>& list, vector<int>& root, int n)
{
    int m= list.size();
    int sum_of_weights = (2*n)*root[n+1];
    struct rt input;
    int flag=1;
    for(int i=0;i<=n;i++)
    {
        sum_of_weights += root[i];
        input.weights.push_back(root[i]);
    }
    input.weights.push_back(root[n+1]);
    input.i = -1;
    input.sum_weights = sum_of_weights;
    if(sum_of_weights == 1)
    {
        int k = 0;
        while(root[k]==0)
            k++;
        input.SLword.push_back(k);
        if(k!=0)
        {
            vector<int> vec{1,k,k+1};
            input.bracket.push_back(vec);
        }
        else
        {
            vector<int> vec{1,1,2*n};
            input.bracket.push_back(vec);
        }
        list.push_back(input);
        return;
    }
    for(int i=0;i<m-1;i++)
    {
        vector<int> dec1(n+2,0);
        subtract_root(n,root,list[i].weights, dec1);
        if(check_root(n, dec1) == 0)
            continue;
        else if(compare_roots(n,dec1, list[i].weights))
            i=m-1;
        else
        {
            int a = i;
            int b = m-1;
            if(equality_roots(n,dec1,list[b].weights))
                a=b;
            while(a<b)
            {
                int c = (a+b)/2;
                if(equality_roots(n,dec1,list[c].weights))
                {
                    a=c;
                    b=c;
                }
                else if(compare_roots(n,dec1, list[c].weights))
                    b=c;
                else
                    a=c;
            }
            if(list[a].i>0)
            {
                a=a+1-list[a].i;
                for(int i=0;i<n;i++)
                {
                    vector<vector<int>> new_bracket;
                    conjugation(list[i].bracket, list[a].bracket, new_bracket, n);
                    if(new_bracket.size()>0)
                    {
                        vector<int> new_SL;
                        if(compare_word(list[i].SLword, list[a].SLword))
                        {
                            for(int j =0; j< list[i].SLword.size();j++)
                            {
                                int dum = list[i].SLword[j];
                                new_SL.push_back(dum);
                            }
                            for(int j =0; j< list[a].SLword.size();j++)
                            {
                                int dum = list[a].SLword[j];
                                new_SL.push_back(dum);
                            }
                        }
                        else
                        {
                            for(int j =0; j< list[a].SLword.size();j++)
                            {
                                int dum = list[a].SLword[j];
                                new_SL.push_back(dum);
                            }
                            for(int j =0; j< list[i].SLword.size();j++)
                            {
                                int dum = list[i].SLword[j];
                                new_SL.push_back(dum);
                            }
                        }
                        if(flag)
                        {
                            flag = 0;
                            for(int k=0;k<new_SL.size();k++)
                            {
                                int dum = new_SL[k];
                                input.SLword.push_back(dum);
                            }
                            for(int k=0;k<new_bracket.size();k++)
                            {
                                vector<int> vec(3,0);
                                vec[0] = new_bracket[k][0];
                                vec[1] = new_bracket[k][1];
                                vec[2] = new_bracket[k][2];
                                input.bracket.push_back(vec);
                            }
                            list.push_back(input);
                        }
                        else if(compare_word( list[list.size()-1].SLword, new_SL))
                        {   
                            list[list.size()-1].bracket.clear();
                            for(int k=0;k<new_bracket.size();k++)
                                list[list.size()-1].bracket.push_back(new_bracket[k]);
                            for(int k=0;k<new_SL.size();k++)
                                list[list.size()-1].SLword[k]= new_SL[k];
                        }
                    }
                }
            }
            else
            {
                vector<vector<int>> new_bracket;
                conjugation(list[i].bracket, list[a].bracket, new_bracket,n);
                if(new_bracket.size()>0)
                {
                    vector<int> new_SL;
                    if(compare_word(list[i].SLword, list[a].SLword))
                    {
                        for(int j =0; j< list[i].SLword.size();j++)
                            new_SL.push_back(list[i].SLword[j]);
                        for(int j =0; j< list[a].SLword.size();j++)
                            new_SL.push_back(list[a].SLword[j]);
                    }
                    else
                    {
                        for(int j =0; j< list[a].SLword.size();j++)
                            new_SL.push_back(list[a].SLword[j]);
                        for(int j =0; j< list[i].SLword.size();j++)
                            new_SL.push_back(list[i].SLword[j]);
                    }
                    if(flag)
                    {
                        flag = 0;
                        for(int k=0;k<new_SL.size();k++)
                            input.SLword.push_back(new_SL[k]);
                        for(int k=0;k<new_bracket.size();k++)
                        {
                            vector<int> vec(3,0);
                            vec[0] = new_bracket[k][0];
                            vec[1] = new_bracket[k][1];
                            vec[2] = new_bracket[k][2];
                            input.bracket.push_back(vec);
                        }
                        list.push_back(input);
                    }
                    else if(compare_word( list[list.size()-1].SLword, new_SL))
                    {   
                        list[list.size()-1].bracket.clear();
                        for(int k=0;k<new_bracket.size();k++)
                            list[list.size()-1].bracket.push_back(new_bracket[k]);
                        for(int k=0;k<new_SL.size();k++)
                            list[list.size()-1].SLword[k]= new_SL[k];
                    }
                }
            }
        }
    }
}
void fill_list(vector<struct rt>& list, vector<int>& root, int i, int n){
    if(i==1)
    {
        root[i] = 0;
        fill_list(list, root, i+1,n);
        root[i] = 1;
        add_list_real(list, root, n);
        fill_list(list, root, i+1,n);
    }
    else if(i<n)
    {
        if(root[i-1]==0)
        {
            root[i] = 0;
            fill_list(list, root, i+1,n);
            root[i]=1;
            add_list_real(list, root, n);
            fill_list(list, root, i+1,n);
        }
        else if(root[i-1]==1)
        {
            root[i] = 1;
            add_list_real(list, root, n);
            fill_list(list, root, i+1,n);
            root[i] = 2;
            fill_list(list, root, i+1,n);
        }
        else if(root[i-1]==2)
        {
            root[i] = 2;
            fill_list(list, root, i+1,n);
        }
    }
    else
    {
        if(root[i-1] == 0)
        {
            root[i] = 1;
            add_list_real(list, root, n);
        }
        else if(root[i-1]==1)
        {
            root[i] = 1;
            add_list_real(list, root, n);
            root[i] = 2;
            add_list_real(list, root, n);
        }
        else
        {
            root[i] =2;
            add_list_real(list,root,n);
        }
    }
    root[i]=0;
}

int main()
{
    int n = 5;
    vector<struct rt> list;
    vector<int> root(n+2,0);
    fill_list(list,root,1,n);
    cout<<"Fin";
    cout<<list.size()<<"\n";
    for(int i=0;i<list.size();i++)
    {
        for(int j=0;j<=n+1;j++)
            cout<<list[i].weights[j];
        cout<<" ";
        for(int j=0;j<list[i].SLword.size();j++)
            cout<<list[i].SLword[j];
        cout<<" Height="<<list[i].sum_weights<<"\n";
    }
    return 0;
}