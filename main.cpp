#include <iostream>
#include <vector>
#include <cstring>

using namespace std;


struct edge {
    char transition;
    int node, code;
};

class MealyMachine {
    vector<vector<edge>> edges;
    int n, m, start, *final;
public:
    MealyMachine(int n=0, int m=0) {
        this->n=n;
        this->m=m;
        final= new int [n];
        start = 0;
        for(int i=0;i<n;i++)
            final[i]=0;
        edges.resize(n);

    }

    void addEdge(int node1, int node2, char transition, int code) {
        edges[node1].push_back({transition, node2, code});
    }

    void addFinalState(int node) {
        final[node] = 1;
    }

    void setStart(int node) {
        start = node;
    }

    void checkRec(char *);

    void check(char *);

    void dfs(int, char *, vector<int> &, vector<int> &);

};

void MealyMachine::check(char *c) {
    vector<int> route, encoding;
    int node=start;
    route.push_back(start);
    int l = strlen(c), i;
    for(i=0;i<l;i++){
        int gasit = 0;
        for (edge e: edges[node])
            if (e.transition == c[i]) {
                route.push_back(e.node);
                encoding.push_back(e.code);
                node=e.node;
                gasit=1;
                continue;
            }
        if(!gasit)
            break;
    }
    if(i==l && final[route[i]]){
        cout << "DA\n";
        for (int x: encoding) {
            cout << x;
        }
        cout << "\nTraseu: ";
        for (int x: route) {
            cout << x << " ";
        }
        cout << "\n";
        return;
    }
    cout<<"NU\n";
}

void MealyMachine::checkRec(char *c) {
    vector<int> route, encoding;
    route.push_back(start);
    dfs(start, c, route, encoding);
    if (route.size() - 1 == strlen(c) && final[route.back()]) {
        cout << "DA\n";
        for (int x: encoding) {
            cout << x;
        }
        cout << "\nTraseu: ";
        for (int x: route) {
            cout << x << " ";
        }
        cout << "\n";
        return;
    }
    cout << "NU\n";
}

void MealyMachine::dfs(int node, char *c, vector<int> &route, vector<int> &encoding) {
    for (edge e: edges[node])
        if (e.transition == c[0]) {
            route.push_back(e.node);
            encoding.push_back(e.code);
            dfs(e.node, c + 1, route, encoding);
        }
}

int main() {
    int n, m, node1, node2, code, start, nbFinals, final, nbStrings;
    char c[1000][1000];
    char transition;
    cin >> n >> m;
    MealyMachine mm(n,m);
    for (int i = 0; i < m; i++) {
        cin >> node1 >> node2 >> transition >> code;
        mm.addEdge(node1, node2, transition, code);
    }
    cin >> start;
    mm.setStart(start);
    cin >> nbFinals;
    for (int i = 0; i < nbFinals; i++) {
        cin >> final;
        mm.addFinalState(final);
    }
    cin>>nbStrings;
    for(int i=0;i<nbStrings;i++){
        cin>>c[i];
        mm.check(c[i]);
    }
    return 0;
}
