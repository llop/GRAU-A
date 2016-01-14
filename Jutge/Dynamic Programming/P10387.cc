#include <iostream>
using namespace std;

int n;              // word length
string s;           // word
int tbl[101][101];  // memo table

// min cost of having s[x] open and s[y] close a parenthesis of the same type
// characters       operations            cost
// ----------       ----------            ----
// () []            none                  0
// ]] )) (( [[      flip                  1
// )( ][            2 flips               2
// (] [)            transform             2
// ]) )] [( ([      flip + transform      3
// ]( )[            2 flips + transform   4
inline int cost(int x, int y) {
  if (s[x]==s[y]) return 1;
  if ((s[x]=='('&&s[y]==')')||(s[x]=='['&&s[y]==']')) return 0;
  if ((s[x]=='('&&s[y]==']')||(s[x]=='['&&s[y]==')')||
    (s[x]==')'&&s[y]=='(')||(s[x]==']'&&s[y]=='[')) return 2;
  if ((s[x]==']'&&s[y]=='(')||(s[x]==')'&&s[y]=='[')) return 4;
  return 3;
}

// precondition: x<y, (y-x+1)%2==0
// minimum cost of making s[x..y] a correct perenthesis expression
int dyn(int x, int y) {
  int &r=tbl[x][y];
  if (r==-1) {
    r=cost(x, y)+(x+1==y?0:dyn(x+1, y-1));                        // s[y] closes s[x]
    for (int i=x+1; i<y; i+=2) r=min(r, dyn(x, i)+dyn(i+1, y));   // s[x] opens a different parenthesis
  }                                                               // expression than s[y]
  return r;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  while (cin>>s) {                                                    // read input
    n=s.size();
    for (int i=0; i<n; ++i) for (int j=i+1; j<n; ++j) tbl[i][j]=-1;   // reset memo table
    cout<<dyn(0, n-1)<<endl;                                          // solve and print
  }
  return 0;
}