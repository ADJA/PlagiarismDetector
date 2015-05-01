#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <cassert>
#include <utility>
#include <iomanip>

using namespace std;

struct node {
    int x, y;
    node *l, *r;
    int sz;
    node(int new_x, int new_y) {
        x = new_x; y = new_y;
        l = NULL; r = NULL;
        sz = 1;
    }
};

typedef node * pnode;

int getsize(pnode t) {
    if (t == NULL)
        return 0;
    return t->sz;
}

void update(pnode t) {
    if (t == NULL) 
        return;
    t->sz = getsize(t->l) + 1 + getsize(t->r);
}               

void merge(pnode &t, pnode l, pnode r) {
    if (l == NULL) 
        t = r;
    else if (r == NULL) 
        t = l;
    else if (l->y > r->y) {
        merge(l->r, l->r, r); 
        t = l;
    }
    else {
        merge(r->l, l, r->l); 
        t = r;
    }
    update(t);
}

void split(pnode t, int x, pnode &l, pnode &r) {
    if (t == NULL) 
        l = r = NULL;
    else if (t->x > x) {
        split(t->l, x, l, t->l); 
        r = t;
    }
    else {
        split(t->r, x, t->r, r); 
        l = t;
    }
    update(t);
    update(r); update(l);
}

void add(pnode &t, pnode a) {
    if (t == NULL) 
        t = a;
    else if (a->y > t->y) {
        split(t, a->x, a->l, a->r); 
        t = a;
    }
    else {
        if (t->x < a->x) 
            add(t->r, a);
        else 
            add(t->l, a);
    }
    update(t);
}

void add(pnode &t, int x) {
    pnode num = new node(x, rand());
    add(t, num);
    //cout << "ADDED " << x << endl;
}

int numG(pnode &t, int x) {
    pnode l, r;
    split(t, x, l, r);
    int res = getsize(r);
    merge(t, l, r);
    return res;
}

int numL(pnode &t, int x) {
    pnode l, r;
    split(t, x, l, r);
    int res = getsize(l);
    merge(t, l, r);
    return res;
}

pnode root = NULL;

int n;
map < int, int > ind;
int t[15];
vector < pair <int, int> > v;
long long ans;

int main() {
    //assert(freopen("input.txt","r",stdin));
    //assert(freopen("output.txt","w",stdout));

    scanf("%d", &n);

    /*add(root, 1);
    add(root, 4);
    add(root, 5);
    add(root, 7);

    while (true) {
        int x;
        cin >> x;
        if (!x)
            break;
        cout << numG(root, x) << endl;
    }



    while (true) {
        int x;
        cin >> x;
        if (!x)
            break;
        cout << numL(root, x) << endl;
    }*/

    /*for (int i = 1; i < 15; i++)
        t[i] = i;   */

    for (int i = 1; i <= n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (ind.count(a) == 0)
            ind[a] = a;
        if (ind.count(b) == 0)
            ind[b] = b;
        swap(ind[a], ind[b]);
        //swap(t[a], t[b]);
    }

    /*int cc = 0;
    for (int i = 1; i < 15; i++)
        for (int j = i + 1; j < 15; j++)
            if (t[i] > t[j])
                cc++;

    cout << cc << endl;*/

    for (map <int, int> :: iterator it = ind.begin(); it != ind.end(); it++) {
        v.push_back(make_pair(it->first, it->second));
    }

    int prev = -1;
    for (int i = 0; i < (int) v.size(); i++) {
        int pos = v[i].first;
        int cur = v[i].second;

        if (prev != -1) {
            int from = prev + 1, to = pos - 1;
            if (to >= from) {
                //cout << "F " << from << " " << to << " " << numG(root, from) << endl;
                long long add = 1ll * numG(root, from) * (to - from + 1);
                //cout << add << endl;
                ans += add;
            }
        }

        ans += numG(root, cur);

        prev = pos;
        add(root, cur); 
    }

    root = NULL;

    prev = -1;
    for (int i = v.size() - 1; i >= 0; i--) {
        int pos = v[i].first;
        int cur = v[i].second;

        if (prev != -1) {
            int from = pos + 1, to = prev - 1;
            if (to >= from) {
                long long add = 1ll * numL(root, from) * (to - from + 1);
                //cout << add << endl;
                ans += add;
            }
        }

        prev = pos;
        add(root, cur); 
    }

    cout << ans << endl;
                                                      
    return 0;
}