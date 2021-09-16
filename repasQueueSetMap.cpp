#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <map>

class meu_ordre {
public:
  // Retorna cert si p2 te mes prioritat a la cua
  bool operator () (const pair<int,int>& p1, const pair<int,int>& p2 ) {
    // if (p1.first + p1.second < p2.first + p2.second) return true;
    // else return false;
    return p1.first + p1.second > p2.first + p2.second;
  }
};

using namespace std;

int main() {
   
   // PAIRS
  pair<int,string> a = {10,"hola"};
  //cout << a.first << " " << a.second << endl;

  // PRIORITY QUEUE
  priority_queue<  pair<int,int>,  vector<pair<int,int>>, meu_ordre > Q;
  Q.push({8,2});
  Q.push({1,7});
  Q.push({3,1});
  Q.push({6,3});

  while (not Q.empty()) {
    pair<int,int> x = Q.top();
    Q.pop();
    cout << x.first << " " << x.second << endl;
  }

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
           
 }
                  
                  
                  
                
