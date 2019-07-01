#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define LOOP(i, j, k) for(int i = j; i < k; i++)

struct Node{
    int num = 0;
    vector<int> u;
    Node(int a){
        u.push_back(a);
        num = a;
    }
    void uni(Node* v, vector<Node*>& node){
        unsigned long len = this->u.size() + v->u.size();
        vector<int>temp(len);
        vector<int>::iterator it;
        it = set_union(this->u.begin(), this->u.end(), v->u.begin(), v->u.end(), temp.begin());
        temp.resize(it-temp.begin());
//        cout << temp.size() << "\n";
        LOOP(i, 0, temp.size()){
            node[temp[i] - 1]->u.clear();
            node[temp[i] - 1]->u = temp;
        }
        temp.clear();
//        cout << "end\n";
    }
    bool findLoop(Node* v){
        vector<int>::iterator it;
        it = find(this->u.begin(), this->u.end(), v->num);
        if(it == this->u.end()){
            return false;
        }else{
            return true;
        }
    }
};

struct Edge{
    int c = 0;
    int fir = 0;
    int sec = 0;
    Edge(int a, int b, int len){
        fir = a;
        sec = b;
        c = len;
    }
};

int kruskal(vector<Edge*>& arr, vector<Node*>& node, int n, int m){
    int res = 0;
    bool findMST = false;
    LOOP(i, 0, m){
        int a = arr[i]->fir - 1, b = arr[i]->sec - 1;
        if(!node[a]->findLoop(node[b])){
//            cout << arr[i]->fir << " " << arr[i]->sec << " "<< arr[i]->c << "\n";
            res += arr[i]->c;
            node[a]->uni(node[b], node);
            if(node[a]->u.size() == n){
                findMST = true;
                break;
            }
        }
    }
    if(findMST){
        return res;
    }else{
        return -1;
    }
}
vector<Edge*> arr(1000000);
int main(){
    int n = -1, m = -1, ind = 0;

    while(n != 0 && m != 0){
        cin >> n >> m;
        if(n != 0){
            vector<Node*> node;
            LOOP(i, 0, n){
                Node* nd = new Node(i + 1);
                node.push_back(nd);
            }

            LOOP(i, 0, m){
                int a = 0, b = 0, c = 0;
                cin >> a >> b >> c;
                Edge* e = new Edge(a, b, c);
                arr[i] = e;
            }

            sort(arr.begin(), arr.begin() + m,
                 [](const Edge* a, const Edge* b){
                     return a->c < b->c;
                 });
            if(ind == 0){
                cout << kruskal(arr, node, n, m);
            }else{
                cout << "\n" << kruskal(arr, node, n, m);
            }
            ind++;
            arr.clear();
        }
    }
    return 0;
}