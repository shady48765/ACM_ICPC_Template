#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

const int SIGMA = 26;
const int TOTAL_LENS = 500000;
const int B = 50000;
const int N = 300000;

int alpha(char c) {return c-'a';}

struct node {
    node *suffix, *next[SIGMA];
    int maxDigit;
    std::size_t minLength;
    void evaluate(int a, std::queue<node*> &Q){
        if(next[a]){
            next[a]->suffix = suffix->next[a];
            if(next[a]->maxDigit < next[a]->suffix->maxDigit)
                next[a]->maxDigit = next[a]->suffix->maxDigit;
            if(next[a]->minLength > next[a]->suffix->minLength)
                next[a]->minLength = next[a]->suffix->minLength;
            Q.push(next[a]);
        } else {
            next[a] = suffix->next[a];
        }
    }
} buf[TOTAL_LENS + 1];
int bufc;

node *get_node(){
    for(int a = 0; a < SIGMA; a++) buf[bufc].next[a] = NULL;
    buf[bufc].maxDigit = -1;
    buf[bufc].minLength = TOTAL_LENS;
    return buf + bufc++;
}


void printNodes(){
    for(int i = 0; i < bufc; i++){
        printf("Node %d:\n", i);
        printf("\tsuffix: %d\n", (int) (buf[i].suffix - buf));
        printf("\tnexts:\n");
        for(int a = 0; a < SIGMA; a++)
            if(buf[i].next[a] != buf)
                printf("\t\t%c: %d\n", 'a' + a, (int)(buf[i].next[a] - buf));
        printf("\tmaxDigit: %d\n", buf[i].maxDigit);
        printf("\tminLength: %lu\n", buf[i].minLength);

    }
}


void add_str(node *root, const char *str, int d){
    for(std::size_t i = 0; str[i]; i++){
        int a = alpha(str[i]);
        if(!root->next[a]) root->next[a] = get_node();
        root = root->next[a];
    }
    root->maxDigit = std::max(root->maxDigit, d);
    root->minLength = std::min(root->minLength, strlen(str));
}

void evaluate(node *root){
    root->suffix = root;
    std::queue<node*> Q;
    for(int a = 0; a < SIGMA; a++)
        if(!root->next[a]) root->next[a] = root;
        else {
            root->next[a]->suffix = root;
            Q.push(root->next[a]);
        }
    while(!Q.empty()){
        node *cur = Q.front(); Q.pop();
        for(int a = 0; a < SIGMA; a++) cur->evaluate(a, Q);
    }
}

char digit[TOTAL_LENS + 1];
char message[N + 1];
int digitMatch[N + 1];
std::size_t digitLength[B];

int main(){
    int z;
    scanf("%d", &z);
    while(z--){
        int b;
        scanf("%d", &b);
        bufc = 0;
        node *root = get_node();
        for(int i = 0; i < b - 1; i++){
            scanf("%s", digit);
            digitLength[i] = strlen(digit);
            std::reverse(digit, digit + digitLength[i]);
            add_str(root, digit, i);
        }
        evaluate(root);
        scanf("%s", message);
        std::size_t len = strlen(message);
        std::reverse(message, message + len);
        digitMatch[0] = 0;
        node *cur = root;
        for(std::size_t i = 0; i < len; i++){
            cur = cur->next[alpha(message[i])];
            int j = i + 1 - cur->minLength;
            if(j >= 0 && digitMatch[j] + 1 > digitMatch[i])
                digitMatch[i + 1] = digitMatch[j] + 1;
            else
                digitMatch[i + 1] = digitMatch[i];
        }
        int end = len;
        if(digitMatch[len] == 0){
            printf("0\n");
            continue;
        }
        for(int i = digitMatch[len] - 1; i >= 0; i--){
            int start = end;
            while(start - 1 >= 0 && digitMatch[start - 1] >= i) start--;
            int curDigit = -1;
            int newend = -1;
            cur = root;
            for(int j = start; j < end; j++){
                cur = cur->next[alpha(message[j])];
                if(cur->maxDigit >= curDigit){
                    curDigit = cur->maxDigit;
                    newend = j + 1 - digitLength[cur->maxDigit];
                }
            }
            printf("%d ", curDigit + 1);
            end = newend;
        }
        printf("\n");
    }
}
