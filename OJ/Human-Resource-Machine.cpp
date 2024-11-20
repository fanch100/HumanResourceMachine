#include<iostream>
#include<map>
#include<vector>
using namespace std;
const int N = 110;
const int INF = 0x3f3f3f3f;
int level;
int n;
map<string,int> ma;
struct operation{
    int op;
    int x;
}a[N];
struct Level{
    bool is_useful[9];
    int block[30];
    int available_space;
    int cur_block=INF;
    vector<int> std_input,std_output;
    int nxt_input=-1;
    vector<int> user_output;
    int inbox(int cur_step){
        ++nxt_input;
//        printf("nxt_input=%d std.size=%d\n",nxt_input,std_input.size());
        if (nxt_input>=std_input.size()) return n+1;
        cur_block=std_input[nxt_input];
        return cur_step+1;
    }
    int outbox(int cur_step){
        if (cur_block==INF) return -1;
        user_output.push_back(cur_block);
        cur_block=INF;
        return cur_step+1;
    }
    int copyfrom(int cur_step,int x){
        if (x>available_space || block[x]==INF) return -1;
        cur_block = block[x];
        return cur_step+1;
    }
    int copyto(int cur_step,int x){
        if (x>available_space || cur_block==INF) return -1;
        block[x] = cur_block;
        return cur_step+1;
    }
    int add(int cur_step,int x){
        if (x>available_space || cur_block==INF || block[x]==INF) return -1;
        cur_block += block[x];
        return cur_step+1;
    }
    int sub(int cur_step,int x){
        if (x>available_space || cur_block==INF || block[x]==INF) return -1;
        cur_block -= block[x];
        return cur_step+1;
    }
    int jump(int x){
        if (x>n) return -1;
        return x;
    }
    int jumpifzero(int cur_step,int x){
        if (x>n || cur_block==INF) return -1;
        return (!cur_block)?x:cur_step+1;
    }
    int getnxt(int cur_step){
        int op=a[cur_step].op, x=a[cur_step].x;
        if (!is_useful[op]) return -1;
        if (op==1) return inbox(cur_step);
        else if (op==2) return outbox(cur_step);
        else if (op==3) return copyfrom(cur_step,x);
        else if (op==4) return copyto(cur_step,x);
        else if (op==5) return add(cur_step,x);
        else if (op==6) return sub(cur_step,x);
        else if (op==7) return jump(x);
        else if (op==8) return jumpifzero(cur_step,x);
        return -1;
    }
    bool chk(){
        if (user_output.size()!=std_output.size()) return 0;
        else {
            for (int i=0;i<user_output.size();++i){
                if (user_output[i]!=std_output[i]) return 0;
            }
        }
        return 1;
    }
    void solve(){
        int cur_step = 1;
        while(cur_step<=n){
//            printf("cur_step=%d\n",cur_step);
            int nxt_step=getnxt(cur_step);
//            printf("nxt_step=%d\n",nxt_step);
            if (nxt_step==-1){
                printf("Error on instruction %d\n",cur_step);
                return;
            }
            cur_step=nxt_step;
        }
//        for (int i=0;i<std_output.size();++i) printf("i=%d out=%d\n",i,std_output[i]);
//        for (int i=0;i<user_output.size();++i) printf("i=%d out=%d\n",i,user_output[i]);
        if (chk()) puts("Success");
        else puts("Fail");
    }
}L[4];
void init();
int main(){
    init();
//    for (auto x : L[2].std_input) printf("%d ",x); puts("");
//    for (auto x : L[2].std_output) printf("%d ",x); puts("");
    cin >> level >> n;
    for (int i=1; i<=n; ++i) {
        string s; cin>>s;
        int op=ma[s];
        a[i].op=op;
        if (s!="inbox" && s!="outbox") cin>>a[i].x;
    }
    L[level].solve();
    return 0;
}
int L1[]={
2,
1,2,
2,
1,2,
0,
1,1,0,0,0,0,0,0};
int L2[]={
8,
3,9,5,1,-2,-2,9,-9,
8,
-6,6,4,-4,0,0,18,-18,
3,
1,1,1,1,1,1,1,1};
int L3[]={
8,
6,2,7,7,-9,3,-3,-3,
2,
7,-3,
3,
1,1,1,1,1,1,1,1};
void init_level(Level &L, int* a){
    int cur=0, x=a[0];
    for (cur=1; cur<=x; ++cur) L.std_input.push_back(a[cur]);
    x=cur+a[cur]; cur++;
    for (; cur<=x; ++cur) L.std_output.push_back(a[cur]);
    L.available_space=a[cur];
    for (int i=1; i<=L.available_space; ++i) L.block[i] = INF;
    cur++;
    for (int i=1; i<=8; ++i,++cur) L.is_useful[i] = a[cur];

}
void init(){
    ma["inbox"]=1;
    ma["outbox"]=2;
    ma["copyfrom"]=3;
    ma["copyto"]=4;
    ma["add"]=5;
    ma["sub"]=6;
    ma["jump"]=7;
    ma["jumpifzero"]=8;
    init_level(L[1],L1);
    init_level(L[2],L2);
    init_level(L[3],L3);
}
