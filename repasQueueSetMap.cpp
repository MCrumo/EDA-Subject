#include <iostream>
#include <queue>
#include <set>

using namespace std;

// PRIORITY QUEUE
priority_queue < pair<int,int>, vector<pair<int,int>>, meu_ordre > Q;
Q.push({8,2});
Q.push({1,5});
Q.push({8,1});
Q.push({4,1});
Q.push({2,8});


// SET
set<int> S;
S.insert(2);
S.insert(6);
S.insert(-2);
auto p = S.insert(9);
auto q = S.insert(9);
cout << p.second << endl;
cout << q.second << endl;

/* RECORDATORI VECTORS
vector<int> v = {1,3,-1,4,5};
for (auto x : v) cout << x << " ";
cout << endl; */

for (int x : S) cout << x << " ";
cout << endl;

auto it = S.begin(); // PRIMER element
cout << *it << endl;
it = S..end();
--it;               // ULTIM element
cout << *it << endl;


// MAP
map<string, int> M;
M.insert({"pau",5});
M.insert({"laura",1});
M.insert({"marta",2});
M.insert({"albert",7});

cout << M.size() << endl;
for (auto&p : M)
   cout << p.first << "-->" << p..second << endl;

auto it2 = M.find("laura);
cout << it2->first << endl;
cout << it2->second << endl;
it2->second++;
                  
cout << M["laura"] << endl;
M.erase("laura);
cout << M.size() << endl;

for (auto& p : M)
    cout << p.first << "-->" << p.second << endl;
                  
                  
                  
                
