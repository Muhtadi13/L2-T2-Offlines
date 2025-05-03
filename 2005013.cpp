#include <bits/stdc++.h>
#include "MyListLinked.cpp"

#define lli long long
#define plli pair<lli, lli>
#define MAX 5000006
lli MOD = 1000000007LL;

using namespace std;
vector<lli> smallestprimedivisor(MAX + 3);
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
int cou=0;

class HashTable
{
    vector<list<string>> headList;
    vector<string> container;
    const string empty = "$";
    const string deleted = "#";
    const string present = "@";
    double loadfactor;
    int tableSize;
    int count;
    int which;
    int method;
    int probcount;
    const int c1 = 53;
    const int c2 = 61;

public:
    int gettableSize()
    {
        return tableSize;
    }

    int getprobcount()
    {
        return probcount;
    }

    void setprobcount(int x)
    {
        probcount = x;
    }
    int Hash1(string s)
    {
        int h = 37;
        for (int i = 0; i < s.size(); i++)
        {
            h = (h * 54059) ^ (s[i] * 76963);
            h %= tableSize;
        }
        return h;
    }

    int Hash2(string s)
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
    int AuxHash(string val)
    {
        int p=2;
        for (int i = tableSize - 1; i > 1; i--)
        {
            if (smallestprimedivisor[i] == i)
            {
                p = i;
                break;
            }
        }
        int cur=11;
        for(int i=0;i<val.size();i++)
        {
            cur = (((cur << 5) + cur) + val[i])%p;
        }
      
        return p - cur % p;

       
    }

    // void rehash()
    // {
    //      vector<MyList_Linked<string> >old=headList;

    // }

    HashTable(int sz, int w, int met)
    {
        tableSize = sz;
        loadfactor = 0.5;
        count = 0;
        which = w;
        method = met;
        probcount = 0;
        sieve();
        for (int i = tableSize; i <= 2 * tableSize; i++)
        {
            if (smallestprimedivisor[i] == i)
            {
                tableSize = i;
                break;
            }
        }
        if (method == 1)
            headList.resize(tableSize);

        else
            container.resize(tableSize, empty);

        // cout << tableSize << "\n";
        // cout << headList.size() << "\n";
    }
    int Insert(string el)
    {
        if (method == 1)
        {
            int ind;
            if (which == 1)
                ind = Hash1(el);

            else
                ind = Hash2(el);

            int elind = Find(el);

            //cout<<elind<<"\n";

            int c = 0;
            

            if (elind==-1)
            {
                headList[ind].push_back(el);
                count++;
                if(headList[ind].size()>1)
                c=1;
                // cout << el << " "
                //      << "inserted\n";
            }
            return c;
        }
        else if (method == 2)
        {
            int pos;

            if (which == 1)
                pos = Hash1(el);
            else
                pos = Hash2(el);
            int distance = AuxHash(el);
            int i = distance;
            int c = 0;

            while (container[pos] != empty && container[pos] != el && container[pos] != deleted)
            {
                pos = (pos + distance) % tableSize;
                distance += i;
                c++;
                if (c > tableSize)
                    break;
                //cout<<pos<<"\n";
            }
            if (c <= tableSize && (container[pos] == empty || container[pos] == deleted))
            {
                //cou++;
                container[pos] = el;
                count++;
                return c;
                
            }
            return 0;
            
        }
        else
        {
            int pos;

            if (which == 1)
                pos = Hash1(el);
            else
                pos = Hash2(el);
            // cout<<pos<<"\n";
            int distance = AuxHash(el);
            int i = pos;
            int it = 1;

            while (container[i] != empty && container[i] != el && container[i] != deleted)
            {
                if (it > tableSize)
                    break;

                i = (pos + c1 * distance * it + c2 * it * it) % tableSize;
                it++;
                //cout<<i<<"\n";
            }

            if (it <= tableSize && (container[i] == empty || container[i] == deleted))
            {
                container[i] = el;
                count++;
                
                return it - 1;
            }
            return 0;

           
        }

        // if (1.0 * (tableSize * loadfactor) < count)
        // {
        //     rehash();
        // }
    }
    void Delete(string el)
    {
        if (method == 1)
        {
            int ind;
            if (which == 1)
                ind = Hash1(el);

            else
                ind = Hash2(el);
            auto elind = find(headList[ind].begin(), headList[ind].end(), el);

            if (elind != headList[ind].end())
            {
                headList[ind].erase(elind);
                count--;
            }
        }
        else
        {
            if (count == 0)
                return;

            int pos = Find(el);
            if (pos != -1)
            {
                container[pos] = deleted;
                count--;
            }
        }
    }

    int Find(string el)
    {
        probcount = 0;
        if (method == 1)
        {

            int ind;
            if (which == 1)
                ind = Hash1(el);
            else
                ind = Hash2(el);
            auto elind=headList[ind].end();
            int c=0;

           for(auto it=headList[ind].begin();it!=headList[ind].end();it++)
           {
             c++;
                if((*it)==el)
                {
                    elind=it;
                    break;

                }
               
           }
            // auto it
            if (elind == headList[ind].end())
                return -1;
            
            probcount=c;
            return 1;
        }
        else if(method==2)
        {
            int pos;

            if (which == 1)
                pos = Hash1(el);
            else
                pos = Hash2(el);

            int distance = AuxHash(el);
            int i = distance;
            int c = 0;
            //probcount=0;

            while (container[pos] != empty && container[pos] != el)
            {
                pos = (pos + distance) % tableSize;
                distance += i;
                c++;

                if (c > tableSize)
                    break;
            }

            if (c > tableSize || container[pos] == empty)
                return -1;

            probcount = c;
            probcount++;
            return pos;
        }
        else
        {
             int pos;

            if (which == 1)
                pos = Hash1(el);
            else
                pos = Hash2(el);
            // cout<<pos<<"\n";
            int distance = AuxHash(el);
            int i = pos;
            int it = 1;

            while (container[i] != empty && container[i] != el)
            {
                if (it > tableSize)
                    break;

                i = (pos + c1 * distance * it + c2 * it * it) % tableSize;
                it++;
                //cout<<i<<"\n";
            }

            if (it > tableSize || container[i] == empty )
            return -1;
            
            probcount = it;
            probcount++;
            return 0;

        }
    }
};
int main()
{
    int t = 1;
    while (t--)
    {
        int sz = 5000;
        HashTable hsc1(sz, 1, 1);
        HashTable hsc2(sz, 2, 1);
        HashTable hdh1(sz, 1, 2);
        HashTable hdh2(sz, 2, 2);
        HashTable hcp1(sz, 1, 3);
        HashTable hcp2(sz, 2, 3);

        // vector<string> testhsc1;
        // vector<string> testhsc2;
        // vector<string> testhdh1;
        // vector<string> testhdh2;
        // vector<string> testhcp1;
        // vector<string> testhcp2;

        vector<string> test;

        srand(1);

        int cnt = 300000;
        int j = 0;
        int col1 = 0;
        int col2 = 0;
        int col3 = 0;
        int col4 = 0;
        int col5 = 0;
        int col6 = 0;

        for (int i = 0; i < min(sz,10000); i++)
        {
            // if (j == min(sz,10000))
            //     break;

            int len = (rand() % 6) + 5;
            string s;
            for (int j = 0; j < len; j++)
            {
                char ch = 'a' + (rand() % 26);
                s.push_back(ch);
            }
            //cout<<s<<"\n";
            if (hcp1.Find(s) == -1)
            {
                test.push_back(s);
                col1 += hsc1.Insert(s);
               
                col2 += hsc2.Insert(s);
                col3 += hdh1.Insert(s);
                col4 += hdh2.Insert(s);
                col5 += hcp1.Insert(s);
                col6 += hcp2.Insert(s);
                //cout<<col1<<col2<<col3<<col4<<"\n";
                //j++;
            }
            // test.push_back(s);
        }
        //cout<<test.size()<<"\n";
        hsc1.setprobcount(0);
        hsc2.setprobcount(0);
        hdh1.setprobcount(0);
        hdh2.setprobcount(0);
        hcp1.setprobcount(0);
        hcp2.setprobcount(0);

        //cout<<cou<<"\n";

        int p1=0, p2=0, p3=0, p4=0, p5=0, p6=0;

        for (int i = 0; i < 1000; i++)
        {
            int ind = (rand() % test.size());
            hsc1.Find(test[ind]);
            p1 += hsc1.getprobcount();

            hsc2.Find(test[ind]);
            p2 += hsc2.getprobcount();

            hdh1.Find(test[ind]);
            p3 += hdh1.getprobcount();

            hdh2.Find(test[ind]);
            p4 += hdh2.getprobcount();

            hcp1.Find(test[ind]);
            p5 += hcp1.getprobcount();

            hcp2.Find(test[ind]);
            p6 += hcp2.getprobcount();
        }

        cout <<"Table size "<< hsc1.gettableSize() << "\n";
        cout <<"chaining hash1 collision "<< col1 << " avg probe " << 1.0 * p1 / 1000 << "\n";
        cout <<"chaining hash2 collision "<< col2 << " avg probe " << 1.0 * p2 / 1000 << "\n";
        cout << "Double Hashing hash1 collision "<<col3 << " avg probe " << 1.0 * p3 / 1000 << "\n";
        cout <<"Double Hashing hash2 collision "<< col4 << " avg probe " << 1.0 * p4 / 1000 << "\n";
        cout << "custom probing hash1 collision "<<col5 << " avg probe " << 1.0 * p5 / 1000 << "\n";
        cout <<"custom probing hash2 collision "<<col6 << " avg probe " << 1.0 * p6 / 1000 << "\n";

        // for(int i=0;i<test.size();i++)
        // {
        //     cout<<test[i]<<"\n";
        // }

        // for (int i = 0; i < test.size(); i++)
        // {
        //     h.Insert(test[i]);
        // }
        // for (int i = 0; i < test.size(); i++)
        // {
        //     cout << test[i] << " " << h.Hash1(test[i]) << "\n"; //<< h.AuxHash(test[i]) << "\n";
        //     cout << h.Find(test[i]) << "\n";
        // }
        // h.Delete(test[0]);
        // cout << test[0] << " " << h.Find(test[0]) << "ghfgh\n";
    }
}
