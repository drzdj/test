#pragma once
#include <bits/stdc++.h>

typedef long long ll;
struct TrieNode{
    ll cnt;
    TrieNode* ch[128];
    TrieNode(){
        cnt = 0;
        for(int i = 0; i < 128; i ++) 
            ch[i] = NULL;
    }
};

struct Trie{
    TrieNode * root;
    Trie(){
        root = NULL;
    }
    void Insert(char * s){
        TrieNode * cur = root;
        if(root == NULL) root = new TrieNode();
        for(int i = 0; s[i]; i ++){
            if(cur -> ch[s[i]] == NULL) cur->ch[s[i]] = new TrieNode();
            cur = cur->ch[s[i]];
        }
        cur->cnt ++;
        return;
    }
    ll Count(char * s){
        if(root == NULL) root = new TrieNode();
        TrieNode * cur = root;
        for(int i = 0; s[i]; i ++){
            if(cur == NULL) return 0ll;
            cur = cur->ch[s[i]];
        }
        return cur->cnt;
    }
    void NodeDelete(TrieNode * o){
        for(int i = 0; i < 128; i ++)
            if(o->ch[i] != NULL) NodeDelete(o->ch[i]);
        delete o;
    }
    void Delete(){
        if(root) NodeDelete(root);
        root = NULL;
    }
};