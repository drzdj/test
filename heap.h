#pragma once
#include<bits/stdc++.h>
using namespace std;
const int HSIZE = 400;
typedef long long ll;


struct PNode{
    char * s;
    ll cnt;
    PNode(){s = NULL, cnt = 0ll;}
    PNode(char * _, int __) : s(_), cnt(__){}
    bool operator < (const PNode & a) const{
        return cnt < a.cnt;
    }
};

struct Heap{
    PNode h[HSIZE];
    int len;
    Heap(){len = 0;}
    void Clear(){len = 0;}
    int Size(){return len;}
    PNode Top(){
       if(!len) return PNode{NULL, 0};
       else return h[1];
    }
    void Insert(PNode t){
        h[++ len] = t;
        if(len == 1) return;
        int cur = len, tar;
        while(cur){
            tar = (cur >> 1);
            if(!tar) break;
            if(h[cur] < h[tar]) swap(h[tar], h[cur]);
            else break;
            cur = tar;
        }
        return;
    }
    void Pop(){ 
        swap(h[1], h[len]);
        len --;
        int cur = 1, tar;
        while(cur <= len){
            tar = (cur << 1);
            if(tar > len) break;
            if(tar + 1 <= len && h[tar + 1] < h[tar]) tar ++;
            if(h[tar] < h[cur]) swap(h[tar], h[cur]);
            else break;
            cur = tar;
        }
        return;
    }
};