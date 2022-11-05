# include <iostream>
# include <thread>
# include <unistd.h>
using namespace std;

# define MAX 500

int matA[MAX][MAX];
int matB[MAX][MAX];
static const int threadNum = 20;

typedef struct {
    int start;
    int end;
    long long addans;
    long long mulans;
} Range;

void* func(void* inp){
    Range* data = (Range*) inp;
    long long add = 0;
    long long mul = 0;
    for (int i = data->start; i < data->end; i++) {
        for (int j = 0; j < MAX; j++){
            add += matA[i][j] + matB[i][j];
            for (int k = 0; k < MAX; k++) {
                mul += matA[i][k] * matB[k][j];
            }
        }   
    }
    data->addans = add;
    data->mulans = mul;
    pthread_exit(NULL); 
}

Range * createRangeParam(int start, int end) {
    Range* num = (Range*) malloc(sizeof(Range));
    num->start = start;
    num->end = end;
    num->addans = 0;
    num->mulans = 0;
    return num;
}

int main(void){
    cin.sync_with_stdio(0);
    cin.tie(0);

    //get input
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cin >> matA[i][j];
        }
    }
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cin >> matB[i][j];
        }
    }

    Range* numList[threadNum];
    int range = MAX / threadNum;
    int start = 0;
    int end = range;
    for (int i = 0; i < threadNum; i++) {
        numList[i] = createRangeParam(start,end);
        start += range;
        if (end + range > 500) end = 500;
        else end += range;
    }

    pthread_t t[threadNum];
    void *ans;
    long long mulTotal = 0;
    long long addTotal = 0;
    
    for (int i = 0; i < threadNum; i++) {
        pthread_create(&t[i],NULL,func,(void*) numList[i]);
    }   
    for (int i = 0; i < threadNum; i++) {
        pthread_join(t[i], NULL);
    }
    for (int i = 0; i < threadNum; i++) {
        addTotal += numList[i]->addans;
        mulTotal += numList[i]->mulans;
    }
    
    cout << addTotal << endl << mulTotal << endl;

    return 0;
}