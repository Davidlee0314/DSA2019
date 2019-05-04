//
// Created by 李得瑋 on 2019-04-11.
//
#include <iostream>
#include <stdio.h>
using namespace std;
#define REP(i, j, k) for(int i = j; i < k; i++)

struct Player{
    /*
     * Row: C, D, H, S
     * Col: A, 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K
     */
    int cards[4][13];
    int cardNum;
    Player(int n){
        this->cardNum = n;
    }
    void cinCards(int n){
        REP(i, 0, n){
            char temp[3];
            cin >> temp;
            int tempRow = 0, tempCol = 0;

            if(temp[0] == 'D'){
                tempRow = 1;
            }else if(temp[0] == 'H'){
                tempRow = 2;
            }else if(temp[0] == 'S'){
                tempRow = 3;
            }

            if(temp[1] == 'T'){
                tempCol = 9;
            }else if(temp[1] == 'J'){
                tempCol = 10;
            }else if(temp[1] == 'Q'){
                tempCol = 11;
            }else if(temp[1] == 'K'){
                tempCol = 12;
            }else if(temp[1] == 'A'){
                tempCol = 0;
            }else{
                tempCol = int(temp[1]) - 48;
            }
            this->cards[tempRow][tempCol] += 1;
        }
    }
    void print(){
        REP(i, 0, 4){
            REP(j, 0, 13){
                cout << this->cards[i][j] << " ";
            }
            cout << "\n";
        }
    }
};

int main(){
    int N = 0;
    Player* Alice = new Player(N);
    Player* Bob = new Player(N);
    cin >> N;
    Alice->cinCards(N);
    Bob->cinCards(N);
    Alice->print();
    Bob->print();
    return 0;
}

