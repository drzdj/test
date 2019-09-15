#include <bits/stdc++.h>
#include "trie.h"
#include "heap.h"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int K = 400;
const int M = 100;
const int bas = 131;
const int inc = 27;

Trie trieA;
Heap heapA;
char s[1024], ts[128];
int curLevel = 1;
bool existFlag[K];
vector<int> curFile;
vector<char *> curUrl;
char *inputFile, *outputFile;

ull Hash(char * s){
    ull ret = 0;
    for(int i = 0; s[i]; i ++)
        ret = ret * bas + inc;
    return ret;
}

char * GetFileName(char flag, int level, int num){
    sprintf(ts, "%c_%d_%d", flag, level, num);
    return ts;
}

void SetCurFile(){
    curFile.clear();
    for(int i = 0; i < K; i ++)
        if(existFlag[i]) curFile.push_back(i);
    memset(existFlag, 0, sizeof(existFlag));
    return;
}

void GetInitFile(char * src){
    FILE * fp = fopen(src, "r");
    FILE * fpt;
    ull tmpHash;
    while(~fscanf(fp, "%s", s)){
        tmpHash = Hash(s) % K;
        fpt = fopen(GetFileName('f', 0, tmpHash), "a");
        fprintf(fpt, "%s ", s);
        existFlag[tmpHash] = 1;
        fclose(fpt);
    }
    fclose(fp);
    SetCurFile();
    return;
}

void getFileInit(int num){
    FILE * fp = fopen(GetFileName('f', 0, num), "r");
    while(~fscanf(fp, "%s", s)){
        if(!trieA.Count(s)) {
            char * st = new char [strlen(s) + 1];
            strcpy(st, s);
            curUrl.push_back(st);
        }
        trieA.Insert(s);
    }
    fclose(fp);

    PNode tmpNode;
    for(auto p: curUrl){
        tmpNode = PNode(p, trieA.Count(p));
        if(heapA.Size() < M) heapA.Insert(tmpNode);
        else if(heapA.Top() < tmpNode) heapA.Pop(), heapA.Insert(tmpNode);
    }


    curUrl.clear();
    vector<char *>().swap(curUrl);
    trieA.Delete();
    return;
}

void GetFileInit(){
    for(auto p: curFile)
        getFileInit(p);
    return;
}

int main(int argc, char ** argv){
    if(argc > 1) inputFile = argv[1];
    else inputFile = new char[1024], scanf("%s", inputFile);
    if(argc > 2) outputFile = argv[2];
    else outputFile = new char[1024], scanf("%s", outputFile);

    GetInitFile(inputFile);
    GetFileInit();

    FILE * fp = fopen(outputFile, "w");
    sort(heapA.h + 1, heapA.h + heapA.Size() + 1);

    for(int i = heapA.Size(); i >= 1; i --)
        fprintf(fp, "%s %lld\n", heapA.h[i].s, heapA.h[i].cnt);
    fclose(fp);

    return 0;
}