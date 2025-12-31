#include<bits/stdc++.h>

using namespace std;

#define lli long long int

#define mod 998244353

#define INF 1000000009

//dp[200005][2]={0};
// lli p[18];
// lli hash_val[20][200005];

// void generate_pow(int n)
// {
//     lli A=3;
//     for(int j=1;j<=n;j++)
//     {
//         p[j]=(p[j-1]*A)%mod;
//     }

// }
// lli generate_hash(char *ch1,char *ch2)
// {


// }





lli ans=1;


string binsearchtree(int ind,string &s,int n)
{
   
    if(ind*2+1>n)
    {  //cout<<ind<<"\n";      
       string ss=""+s[ind-1];
       return ss;
       

    }
    else
    {
        string n1=binsearchtree(ind*2,s,n);
        string n2=binsearchtree(ind*2+1,s,n);

        // lli num1=p[order]*p[order]*s[ind]+n1*p[order]+n2;
        // lli num2= p[order]*p[order]*s[ind]+n2*p[order]+n1;

        //hash_val[order][ind]=num1;

        if(n1!=n2)
        (ans*=2)%=mod;

        if(n1>n2)
        {
            swap(n1,n2);

        }
        return ""+s[ind-1]+n1+n2;
    }




}

int main()
{
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    int t=1;
    //cin>>t;
    while(t--)
    {
        int n;
        string s;
        cin>>n;
        cin>>s;
        ans=1;
        int len=s.size();
        string ss= binsearchtree(1,s,len);

        //generate_pow(n);

        //generate_hash();

        //dfs(0,s);
        // for(int j=(1<<(n-1));j< 1<<n;j++)
        // {

        // }
        cout<<ans<<"\n";

        
    }
}