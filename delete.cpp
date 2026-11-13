#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first
#define s second
// --- Master Debugger Block ---
// Debug Overloads
#ifdef SanG_05
#define debug(x) _print(x); cerr << endl;
#else
#define debug(x)
#endif
void _print(ll t) {cerr << t;}
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(bool t) {cerr <<t;}
template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class... Args> void _print(unordered_set <Args...> v);
template <class... Args> void _print(unordered_multiset <Args...> v);
template <class... Args> void _print(unordered_map <Args...> v);
template <class... Args> void _print(unordered_multimap <Args...> v);
template <class... Args> void _print(list <Args...> v);
template <class... Args> void _print(forward_list <Args...> v);
template <class... Args> void _print(stack <Args...> v);
template <class... Args> void _print(queue <Args...> v);
template <class... Args> void _print(priority_queue <Args...> v);

template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.f); cerr << ","; _print(p.s); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class... Args> void _print(unordered_set <Args...> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class... Args> void _print(unordered_multiset <Args...> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class... Args> void _print(unordered_map <Args...> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class... Args> void _print(unordered_multimap <Args...> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class... Args> void _print(list <Args...> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class... Args> void _print(forward_list <Args...> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class... Args> void _print(stack <Args...> v) {cerr << "[ "; while (!v.empty()) {_print(v.top()); cerr << " "; v.pop();} cerr << "]";}
template <class... Args> void _print(queue <Args...> v) {cerr << "[ "; while (!v.empty()) {_print(v.front()); cerr << " "; v.pop();} cerr << "]";}
template <class... Args> void _print(priority_queue <Args...> v) {cerr << "[ "; while (!v.empty()) {_print(v.top()); cerr << " "; v.pop();} cerr << "]";}

class Node{
    public:
    ll data;
    Node* left; 
    Node* right;
    ll height=1;
    Node(ll val, Node* left1, Node* right1):data(val),left(left1),right(right1){}
    Node(ll val):data(val),left(nullptr),right(nullptr){}
    Node():data(0),left(nullptr),right(nullptr){}
};
ll getheight(Node* curr){
    if(!curr){return 0;}
    return curr->height;
}
Node* rightr(Node* curr){
    Node* temp=curr; 
    if(!curr->left){return curr;}
    Node* temp1=curr->left;
    Node* temp2=curr->left->right;
    temp1->right=temp;
    temp->left=temp2;
    temp->height=1+max(getheight(temp->left),getheight(temp->right));
    temp1->height=1+max(getheight(temp1->left),getheight(temp1->right));
    return temp1;
}
Node* leftr(Node* curr){
    Node* temp=curr; 
    if(!curr->right){return curr;}
    Node* temp1=curr->right;
    Node* temp2=curr->right->left;
    temp1->left=temp;
    temp->right=temp2;
    temp->height=1+max(getheight(temp->left),getheight(temp->right));
    temp1->height=1+max(getheight(temp1->left),getheight(temp1->right));
    return temp1;
}
ll getbf(Node* curr){return getheight(curr->left)-getheight(curr->right);}
Node* balance(Node* curr){
    ll bf=getbf(curr);
    Node* temp=curr;
    if(bf>1){
        if(getbf(curr->left)>=0){temp=rightr(curr);}
        else{curr->left=leftr(curr->left); temp=rightr(curr);}
    }
    else if(bf<-1){
        if(getbf(curr->right)<=0){temp=leftr(curr);}
        else{curr->right=rightr(curr->right); temp=leftr(curr);}
    }
    curr->height=1+max(getheight(curr->left),getheight(curr->right));
    return temp;
}

Node* deleteNode(Node* curr, ll val){
    if(!curr){return nulltpr;}
    if(curr->data<val){curr->right=deleteNode(curr->right,val);}
    else if(curr->data>val){curr->left=deleteNode(curr->left,val);}
    else{
        if(!curr->left && !curr->right){
            delete curr;  curr=nullptr; return nullptr;
        }
        else if((curr->right && !curr->left)||(!curr->right && curr->left)){
            Node* temp;
            if(curr->right){temp=curr->right;}
            else{temp=curr->left;}
            delete curr; return temp;
        }
        else{
            Node* successor=curr->right;
            while(successor->left){
                successor=successor->left;
            }
            curr->data=successor->data;
            curr->right=deleteNode(curr->right,successor->data);
        }
    }
    return balance(curr);
}
int main(){
    Node* guy;
    root=insert(guy,root);

}
