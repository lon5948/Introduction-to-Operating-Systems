# include <iostream>
# include <thread>
# include <unistd.h>
using namespace std;

# define MAX 500

int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX]; // Result of Addition
int matD[MAX][MAX]; // Result of Multiplication

void Addition(){
    // Addition -> matC
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++){
            matC[i][j] = matA[i][j] + matB[i][j];
        }   
    }
}
void Multiplication(){
    // Multiplication -> matD
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            matD[i][j] = 0;
            for (int k = 0; k < MAX; k++) {
                matD[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
}

int main()
{
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
    Addition();
    Multiplication();
    // calculate SUM of matC
    long long sum_C = 0;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            sum_C +=  matC[i][j];     
    }
    cout << sum_C << endl;

    // calculate SUM of matD
    long long sum_D = 0;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            sum_D += matD[i][j];
    }
    cout << sum_D << endl;

    return 0;
}