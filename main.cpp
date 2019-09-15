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

PNode f[2][K][M]; 
int flen[2][K];

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
        //printf(">>%s %llu\n", s, tmpHash);
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

    for(int i = 1; i <= heapA.Size(); i ++)
        f[curLevel & 1][num][i - 1] = heapA.h[i];
    flen[curLevel & 1][num] = heapA.Size();

    curUrl.clear();
    vector<char *>().swap(curUrl);
    trieA.Delete();
    heapA.Clear();
    return;
}

void GetFileInit(){
    for(auto p: curFile)
        getFileInit(p);
    return;
}

void checkStage(int stage){
    printf(">>%d\n", stage);
    for(auto p: curFile){
        printf(">>>>%d %d:\n", p, flen[stage & 1][p]);
        for(int i = 0; i < flen[stage & 1][p]; i ++)
            printf("%s %lld\n", f[stage & 1][p][i].s, f[stage & 1][p][i].cnt);
    }
    printf("\n\n");
    return;
}

void merge(int stage, int x, int y, int tar){
    if(y == -1){
        for(int i = 0; i < flen[stage & 1][x]; i ++)
            f[!(stage & 1)][tar][i] = f[stage & 1][x][i];
        flen[!(stage & 1)][tar] = flen[stage & 1][x];
        return;
    }
    heapA.Clear();
    for(int i = 0; i < flen[stage & 1][x]; i ++) heapA.Insert(f[stage & 1][x][i]);
    for(int i = 0; i < flen[stage & 1][y]; i ++){
        if(heapA.Size() < M) heapA.Insert(f[stage & 1][y][i]);
        else if(heapA.Top() < f[stage & 1][y][i]) heapA.Pop(), heapA.Insert(f[stage & 1][y][i]);
    }
    
    for(int i = 1; i <= heapA.Size(); i ++)
        f[!(stage & 1)][tar][i - 1] = heapA.h[i];
    flen[!(stage & 1)][tar] = heapA.Size();
    existFlag[tar] = 1;
    return;
}

void MergePhase(){
    int n = curFile.size();
    while(n > 1){
        //checkStage(curLevel);
        curLevel ++;
        for(int i = 0; i < curFile.size(); i += 2){
            if(i + 1 < curFile.size()) merge(curLevel - 1, curFile[i], curFile[i + 1], (i >> 1));
            else merge(curLevel - 1, curFile[i], -1, (i >> 1));
        }
        SetCurFile();
        n = curFile.size();
    }
    return;
}

int main(int argc, char ** argv){
    if(argc > 1) inputFile = argv[1];
    else inputFile = new char[1024], scanf("%s", inputFile);
    if(argc > 2) outputFile = argv[2];
    else outputFile = new char[1024], scanf("%s", outputFile);

    GetInitFile(inputFile);
    GetFileInit();
    MergePhase();

    FILE * fp = fopen(outputFile, "w");
    sort(f[curLevel & 1][0], f[curLevel & 1][0] + flen[curLevel & 1][0]);

    for(int i = flen[curLevel & 1][0] - 1; i >= 0; i --)
        fprintf(fp, "%s %lld\n", f[curLevel & 1][0][i].s, f[curLevel & 1][0][i].cnt);
    fclose(fp);
    return 0;
}