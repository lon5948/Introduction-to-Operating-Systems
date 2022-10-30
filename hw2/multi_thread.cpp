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
    long long ans;
} Range;

void* Addition(void* inp){
    Range* data = (Range*) inp;
    long long ret = 0;
    for (int i = data->start; i < data->end; i++) {
        for (int j = 0; j < MAX; j++){
            ret += matA[i][j] + matB[i][j];
        }   
    }
    data->ans= ret;
    pthread_exit(NULL); 
}

void* Multiplication(void* inp){
    Range* data = (Range*) inp;
    long long ret = 0;
    for (int i = data->start; i < data->end; i++) {
        for (int j = 0; j < MAX; j++) {
            for (int k = 0; k < MAX; k++) {
                ret += matA[i][k] * matB[k][j];
            }
        }
    }
    data->ans= ret;
    pthread_exit(NULL);
}

Range * createRangeParam(int start, int end) {
    Range* num = (Range*) malloc(sizeof(Range));
    num->start = start;
    num->end = end;
    num->ans = 0;
    return num;
}

int main(void){
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
    int range;
    if (MAX % threadNum == 0) range = MAX / threadNum;
    else range = MAX / threadNum + 1;
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
    long long mul = 0;
    long long add = 0;
    
    // add
    for (int i = 0; i < threadNum; i++) {
        pthread_create(&t[i],NULL,Addition,(void*) numList[i]);
    }   
    for (int i = 0; i < threadNum; i++) {
        pthread_join(t[i], NULL);
    }
    for (int i = 0; i < threadNum; i++) {
        add += numList[i]->ans;
    }

    // multiple
    for (int i = 0; i < threadNum; i++) {
        pthread_create(&t[i],NULL,Multiplication,(void*) numList[i]);
    }   
    for (int i = 0; i < threadNum; i++) {
        pthread_join(t[i], NULL);
    }
    for (int i = 0; i < threadNum; i++) {
        mul += numList[i]->ans;
    }
    
    cout << add << endl << mul << endl;
    return 0;
}