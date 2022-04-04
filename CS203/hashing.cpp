#include <bits/stdc++.h>

#define ll long long
#define pb push_back
#define mp make_pair
#define be begin()
#define en end()
#define all(v) v.be, v.en
#define le length()
#define fi first
#define se second
#define lb lower_bound()
#define ub upper_bound()
#define endl "\n"
#define inf LLONG_MAX

#define forz(i, n) for (ll i = 0; i < n; i++)
#define fora(i, m, n) for (ll i = m; i < n; i++)
#define rforz(i, n) for (ll i = n - 1; i >= 0; i--)
#define rfora(i, m, n) for (ll i = n; i >= m; i--)

#define vll vector<ll>
#define vpll vector<pair<ll, ll>>
#define mll map<ll, ll>
#define pll pair<ll, ll>

#define P0(a) cout << a << " "
#define P1(a) cout << a << endl
#define PYES cout << "YES\n"
#define PNO cout << "NO\n"

#define rev(v) reverse(v.be, v.en)
#define srt(v) sort(all(v));

#define collect(v, n)          \
    for (ll i = 0; i < n; i++) \
    {                          \
        cin >> v[i];           \
    }

// sort(a.rbegin(), a.rend());
////////////////////////////////////////////////////////////////////////////////////////////////////
/////////=======================FUNCIONS======================================================////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;
ll M = 1000000007;

void fast()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

ll pow(ll a, ll b, ll m)
{
    ll ans = 1;
    while (b)
    {
        if (b & 1)
            ans = (ans * a) % m;
        b /= 2;
        a = (a * a) % m;
    }
    return ans;
}

ll power(ll a, ll b)
{
    ll s = 1;
    for (int x = 0; x < b; x++)
    {
        s *= a;
    }
    return s;
}

ll count_digits(ll n)
{
    string num = to_string(n);
    return num.size();
}
unsigned int nextPowerOf2(unsigned int n)
{
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;

    return log2(n);
}

ll factorial(ll n)
{
    ll factorial = 1;
    for (ll i = 2; i <= n; i++)
        factorial = factorial * i;
    return factorial;
}

ll nCr(ll n, ll r)
{
    return factorial(n) / (factorial(r) * factorial(n - r));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////CODE////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Bucket {
        int depth,size;
        std::vector<int>values;
    public:
        Bucket(int depth, int size);
        int insert(int key);
        int remove(int key);
        bool search(int key);
        int isFull(void);
        int isEmpty(void);
        int getDepth(void);
        int increaseDepth(void);
        std::vector<int> copy(void);
        void clear(void);
        int display(void);
        void dis();
};


class Directory {
        int global_depth, bucket_size;
        vector<Bucket*> buckets;
        vector<ll>s1;
        set<int>s3;
        int hash(int n);
        int pairIndex(int bucket_no, int depth);
        void grow(void);
         void split(int bucket_no);
        string bucket_id(int n);
    public:
        Directory(int depth, int bucket_size);
        void insert(int key);
        void remove(int key);
        void search(int key);
        void display();
        void dis();
};

int main()
{
    int initial_global_depth, bucket_size;
    cin>>initial_global_depth>>bucket_size;
    Directory d(initial_global_depth,bucket_size);
    int a;
    while(true)
    {
        cin>>a;
        ll b;
        if(a==2)
        {
            cin>>b;
            d.insert(b);
        }
        if(a==3)
        {
            cin>>b;
            d.search(b);

        }
        if(a==4)
        {
            cin>>b;
            d.remove(b);
        }
        if(a==5)
        {
    
            d.display();
        }
        if(a==6)
        {

            break;
        }

    }




}


Directory::Directory(int depth, int bucket_size)
{
    this->global_depth = depth;
    this->bucket_size = bucket_size;
    for(int i = 0 ; i < 1<<depth ; i++ )
    {
        buckets.push_back(new Bucket(depth,bucket_size));
        s1.pb(i);
    }
}

void Directory::grow(void)
{
    for(int i = 0 ; i < 1<<global_depth ; i++ )
        buckets.push_back(buckets[i]);
    global_depth++;
}


void Directory::insert(int key)
{
    int bucket_no = hash(key);
    int ld = buckets[bucket_no]->getDepth();
    bucket_no = bucket_no&(ll)(pow(2, ld)-1);
    int status = buckets[bucket_no]->insert(key);
    if(status==0)
    {
        split(bucket_no);
        insert(key);
    }
    else
    {
     
    }

}



void Directory::split(int bucket_no)
{

    int local_depth,pair_index,index_diff,dir_size,i;
    vector<int>temp;
    vector<int>::iterator it;

    local_depth = buckets[bucket_no]->increaseDepth();
    if(local_depth>global_depth)
        grow();
    pair_index = pairIndex(bucket_no,local_depth);
    
    buckets[pair_index] = new Bucket(local_depth,bucket_size);

    s1.pb(pair_index);
    temp = buckets[bucket_no]->copy();
        buckets[bucket_no]->clear();
    index_diff = 1<<local_depth;
    dir_size = 1<<global_depth;
    for( i=pair_index-index_diff ; i>=0 ; i-=index_diff )
        buckets[i] = buckets[pair_index];
    for( i=pair_index+index_diff ; i<dir_size ; i+=index_diff )
        buckets[i] = buckets[pair_index];

    for(it=temp.begin();it!=temp.end();it++)
        insert(*it);
}

void Directory:: dis(void)
{
    // set<Bucket *>s;
    // ll i;

    // for(auto it = s1.begin(); it!= s1.end(); it++){
    //     cout<<"it"<<*it<<endl;
    //     buckets[*it]->dis();
    //     }

    for(ll i = 0; i<s1.size(); i++)
    {
        cout<<s1[i]<<"  ";
    }
}
    // }



void Bucket::dis(void)
{
    for(auto it = values.begin(); it!= values.end(); it++)
    {
        cout<<*it<<" ";
    }
    cout<<endl;
}

void Bucket::clear(void)
{
    values.clear();
}

vector<int> Bucket::copy(void)
{
    vector<int> temp(values.begin(),values.end());
    return temp;
}

int Bucket::increaseDepth(void)
{
    depth++;
    return depth;
}
int Directory::pairIndex(int bucket_no, int depth)
{
    return bucket_no^(1<<(depth-1));
}


int Directory::hash(int n)
{

    return n&((1<<global_depth)-1);
}


Bucket::Bucket(int depth, int size)
{
    this->depth = depth;
    this->size = size;
}


int Bucket::insert(int key)
{
    if(isFull())
        return 0;
    values.pb(key);
    return 1;
}


int Bucket::isFull(void)
{
    if(values.size()==size)
        return 1;
    else
        return 0;
}




void Directory::display()
{
    int i,j,d;
    string s;
    std::set<Bucket *> shown;
    std::vector<pair<int, int>>show;
   cout <<global_depth<<endl;
   ll p;
    for(j=0;j<s1.size(); j++)
    {
        i = s1[j];
         p = shown.size();
        d = buckets[i]->getDepth();

        shown.insert(buckets[i]);
        if((ll)(shown.size())>p)
        {
            show.push_back(mp(buckets[i]->display(), buckets[i]->getDepth()));

        }
    }
    cout<<shown.size()<<endl;
    for(int l = 0; l<show.size(); l++)
    {

        cout<<show[l].first<<" "<<show[l].second<<endl;
    }

}

int Bucket::isEmpty(void)
{
    if(values.size()==0)
        return 1;
    else
        return 0;
}
int Bucket::display()
{
    return values.size();

}

void Directory::remove(int key)
{
    int bucket_no = hash(key);
    if(buckets[bucket_no]->remove(key))
        {

        }
}

int Bucket::remove(int key)
{
    std::vector<int>::iterator it;
    it = find(values.begin(),values.end(),key);
    if(it!=values.end())
    {
        values.erase(it);
        return 1;
    }
    else
    {

        return 0;
    }
}



void Directory::search(int key)
{
    int bucket_no = hash(key);
    if(buckets[bucket_no]->search(key))
    {
        
    }
    else
    {
        
    }
}



bool Bucket::search(int key)
{

    for(auto it = values.begin(); it!= values.end(); it++)
    {
        if(*it == key)
        {
            return true;
        }
    }
    return false;

}
int Bucket::getDepth(void)
{
    return depth;
}
