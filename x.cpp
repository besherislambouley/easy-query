/*
 * we can solve this problem using segment tree , I'll explaing how to find the max y 
 * let's keep the following values in each node , mxans =  the max y , mx = max element , mxb = the max value of t & p , mxo = the max value of t & k 
mxpair = the max value of k & p 
 * now look at the comments in the merge function to learn how to merge two nodes 
*/ 
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <bits/stdc++.h>
using namespace std;
#define sqr 547
#define mid (l+r)/2
#define pb push_back
#define ppb pop_back
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define ins insert
#define era erase
#define C continue
#define mem(dp,i) memset(dp,i,sizeof(dp))
#define mset multiset
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef short int si;
typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pi> vpi;
typedef vector<pll> vpll;
const ll inf=1e18;
const ll mod=1e9+7;
const ld pai=acos(-1);
ll n , q ;
ll a [100009] ;
struct NODE {
	ll mxans , mnans , mx , mn , mxb , mxo , mnb , mno , mxpair , mnpair ;
} tree[400009] ;
NODE merge ( NODE x , NODE y ) {
	NODE ret ;
	ret .mx = max ( x.mx , y.mx ) ; // finding mx 
	ret .mn = min ( x.mn , y.mn ) ; 
	ret .mxb= max ( max ( x.mxb , y.mxb ) , x.mx + y.mx ) ; // finding the best t & p is , t&p from the first node , t&p from the second node , t from the first node & p from the second node 
	ret .mnb= min ( min ( x.mnb , y.mnb ) , x.mn + y.mn ) ;
	ret .mxo= max ( max ( x.mxo , y.mxo ) , x.mx - y.mn ) ; // finding the best t & k is , t&k from the first node , t&k from the second node , t from the first node & k from the second node 
	ret .mno= min ( min ( x.mno , y.mno ) , x.mn - y.mx ) ;
	ret .mxpair = ret .mx - ret.mn ; // the best p&k is always the max element - min one 
	ret .mnpair = ret .mn - ret.mx ; 
	ll Mx = max ( x.mxans , y.mxans ) ; // mxans is one of the following : mxans in the first node , mxans in the second node 
	Mx = max ( Mx , max ( x.mxb - y.mn , x.mxo + y.mx ) ) ; // t&p from the first & k from the second , t&k from the first & p from the second 
	Mx = max ( Mx , x.mx + y.mxpair ) ; // t from the first node , k&p from the second 
	ret .mxans = Mx ;
	ll Mn = min ( x.mnans , y.mnans ) ;
	Mn = min ( Mn , min ( x.mnb - y.mx , x.mno + y.mn ) ) ;
	Mn = min ( Mn , x.mn + y.mnpair ) ;
	ret .mnans = Mn ;
	return ret ;
}
void build ( int node , int l , int r ) {
	if ( l == r ) {
		tree [node] = { a[l] , a[l] , a[l] , a[l] , 2*a[l] , 0 , 2*a[l] , 0 , 0 , 0 } ;
		return ;
	}
	build ( node*2,l,mid ) ;
	build ( node*2+1,mid+1,r ) ;
	tree[node] = merge ( tree[node*2] , tree[node*2+1] ) ;
}
NODE query ( int node , int l , int r , int s , int e ) {
	if ( s <= l && e >= r ) return tree[node] ;
	if ( s <= mid && e >= mid +1 ) return merge ( query ( node*2 , l , mid , s , e ) , query ( node*2+1 , mid +1 , r , s , e ) ) ;
	else if ( s <= mid ) return query ( node*2 , l , mid , s , e ) ;
	else return query ( node*2+1 , mid +1 , r , s , e ) ;
}
int main () {
	freopen("eq.in", "r", stdin);
	freopen("eq.out", "w", stdout);
	scanf("%lld%lld",&n,&q);
	for ( int i = 0 ; i < n ; i ++ ) scanf("%lld",&a[i]) ;
	build ( 1 , 0 , n-1 );
	while ( q -- ) {
		int l , r ;
		scanf("%d%d",&l,&r);
		l -- , r -- ;
		NODE Ans = query ( 1 , 0 , n-1 , l , r ) ;
		printf("%lld\n",Ans .mxans + Ans .mnans); 
	}
}
