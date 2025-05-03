#include <bits/stdc++.h>
#include "compiler.cpp"
#include "MyLinkedList.cpp"

#define lli long long
#define plli pair<lli, lli>
#define MAX 5000006
lli MOD = 1000000007LL;
vector<lli> smallestprimedivisor(MAX+3);

using namespace std;

class HashTable
{
    MyLinkedList *headList;
    int tableSize;
    int count;
    const int c1 = 53;
    const int c2 = 61;

public:
    int getTableSize()
    {
        return tableSize;
    }
    
    void sieve()
    {
        for (lli i = 0; i < MAX; i++)
            smallestprimedivisor[i] = i;

        for (lli i = 2; i * i < MAX; i++)
        {
            if (smallestprimedivisor[i] == i)
            {
                for (lli j = i * i; j < MAX; j += i)
                {
                    if (smallestprimedivisor[j] == j)
                        smallestprimedivisor[j] = i;
                }
            }
        }
    }
    int hash(SymbolInfo& s){
        int h1= hash1(s.getName());
        int h2=0;//hash2(s.getType());

        return (h1+h2)%tableSize; 
    }

    int hash1(string s)
    {
        int h = 37;
        int seed1=54059;
        int seed2=76963;
        for (int i = 0; i < s.size(); i++)
        {
            h = (h * seed1) ^ (s[i] * seed2);
            h %= tableSize;
        }
        return h;
    }
    int hash2(string s)
    {
        int key=7;
        int seed = 31;
        for (int i = 0; i < s.size(); i++)
        {
            key = (key * seed) + (s[i]-'a');
            key %= tableSize;
        }
        //cout<<key<<"\n";
        return key;
    }
    HashTable(int sz, int w, int met)
    {
        tableSize = sz;
        count=0;
        for (int i = tableSize; i <= 2 * tableSize; i++)
        {
            if (smallestprimedivisor[i] == i)
            {
                tableSize = i;
                break;
            }
        }
        headList=new MyLinkedList[tableSize];
    }
    bool Insert(SymbolInfo& el)
    {

            int ind;
            ind = hash(el);
            int elind = Find(el);
            // cout<<elind<<"\n";
            int c = 0;

            if (elind == -1)
            {

                headList[ind].pushBack(el);
                count++;
                return true;

            }
            return false;
        
        
    }
    void Delete(SymbolInfo& el)
    {
 
            int ind;
            ind = hash(el);
            int elind = headList[ind].find(el);
            headList[ind].setToPos(elind);
            SymbolInfo s=headList[ind].erase();
            if(s.getName()!="")
                count--;
            
    }

    SymbolInfo* Find(SymbolInfo el)
    {
            int ind;
            ind = hash(el);
            return headList[ind].find(el);
        
    }
};
