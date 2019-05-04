#include <iostream>
#include <vector>
using namespace std;

void maxHeap(int*& arr, int*& arrPos, int**& arrStatic, int len, int window);
void maxHeapify(int*& arr, int*& arrPos, int**& arrStatic, int root, int len);

//pass array kth + 1 element and use it to index others
void minHeap(int* arr, int* arrPos, int**& arrStatic, int len);
void minHeapify(int* arr, int* arrPos, int**& arrStatic, int root, int len);

void findKth(int*& arr, int*& arrPos, int**& arrStatic, int loop, int window, int kth);
void swap(int* a, int* b, int** c, int** d, int* e, int* f);
void debugPrint(int*& arr, int*& arrPos, int**& arrStatic, int window, int kth, int index);
void debug(int*& arr, int window, int kth);


int main() {
    int n = 0, window = 0, kth = 0;
    cin >> n >> window >> kth;
    int* arr = new int[window + 1];
    int* arrPos = new int[window + 1];
    int** arrStatic = new int*[window + 1];
    for(int i = 0; i <= window; i++){
        if(i == 0){
            arr[i] = 0;
            arrPos[i] = 0;
            arrStatic[i] = arr;
        }else{
            int temp = 0;
            cin >> temp;
            arr[i] = temp;
            arrStatic[i] = arr + i;
            arrPos[i] = i;
        }
    }

//    debugPrint(arr, arrStatic, window, kth, 0);
     // build maxHeap for k number, minHeap for window - kth number
    maxHeap(arr, arrPos, arrStatic, kth, window);
    if(window != kth){
        minHeap(&arr[kth], &arrPos[kth], arrStatic, window - kth);
    }
    findKth(arr, arrPos, arrStatic, n - window, window, kth);
    return 0;
}

void findKth(int*& arr, int*& arrPos, int**& arrStatic, int loop, int window, int kth){
//    debugPrint(arr, arrPos, arrStatic, window, kth, 0);
//    cout << endl;
    cout << arr[1];
    
    for(int i = 1; i <= loop; i++){
        int index = (i % window == 0) ? (window) : (i % window),
            pos = (int)(arrStatic[index] - arrStatic[0]),
            temp = 0;
        cin >> temp;
        *arrStatic[index] = temp;
//        cout << endl << "pos:" << pos << endl;
//        cout << endl << temp << ": (kth)" << arr[1] << ": (kth + 1)" << arr[kth + 1] << endl;
        if(pos > kth + 1){
            if(temp >= arr[kth + 1]){
                int tempPos = pos;
                minHeapify(&arr[kth], &arrPos[kth], arrStatic, pos - kth, window - kth);
                tempPos = (tempPos - kth) / 2;
                if(arr[pos] < arr[kth + (pos - kth)/2]){
                    while(tempPos > 1){
                        minHeapify(&arr[kth], &arrPos[kth], arrStatic, tempPos, window - kth);
                        tempPos = tempPos / 2;
                    }
                }
            }else if(temp < arr[kth + 1] && temp >= arr[1]){
                swap(arr + pos, arr + kth + 1, arrStatic + arrPos[pos],
                        arrStatic + arrPos[kth + 1], arrPos + pos, arrPos + kth + 1);
                int tempPos = (pos - kth) / 2;
                if(arr[pos] < arr[kth + (pos - kth)/2]){
                    while(tempPos > 1){
                        minHeapify(&arr[kth], &arrPos[kth], arrStatic, tempPos, window - kth);
                        tempPos = tempPos / 2;
                    }
                }
            }else if(temp < arr[1]){
                swap(arr + pos, arr + 1, arrStatic + arrPos[pos],
                        arrStatic + arrPos[1], arrPos + pos, arrPos + 1);
                swap(arr + pos, arr + kth + 1, arrStatic + arrPos[pos],
                        arrStatic + arrPos[kth + 1], arrPos + pos, arrPos + kth + 1);
                maxHeapify(arr, arrPos, arrStatic, 1, kth);
                int tempPos = (pos - kth) / 2;
//                cout << "here";
//                cout << endl << arr[pos]  << ": " << arr[(pos - kth)/2];
                if(arr[pos] < arr[kth + (pos - kth)/2]){
                    while(tempPos > 1){
                        minHeapify(&arr[kth], &arrPos[kth], arrStatic, tempPos, window - kth);
                        tempPos = tempPos / 2;
                    }
                }
            }
        }else if(pos == kth + 1){
            if(temp < arr[1]){
                swap(arr + pos, arr + 1, arrStatic + arrPos[pos],
                     arrStatic + arrPos[1], arrPos + pos, arrPos + 1);
                maxHeapify(arr, arrPos, arrStatic, 1, kth);
            }else{
                minHeapify(&arr[kth], &arrPos[kth], arrStatic, 1, window - kth);
            }
        }else if(pos == 1){
            if(temp > arr[kth + 1] && window != kth){
                swap(arr + pos, arr + kth + 1, arrStatic + arrPos[pos],
                     arrStatic + arrPos[kth + 1], arrPos + pos, arrPos + kth + 1);
                minHeapify(&arr[kth], &arrPos[kth], arrStatic, 1, window - kth);
            }else{
                maxHeapify(arr, arrPos, arrStatic, 1, kth);
            }
        }else{
            if(temp <= arr[1]){
                int tempPos = pos;
                maxHeapify(arr, arrPos, arrStatic, pos, kth);
                tempPos = tempPos / 2;
                if(arr[pos] > arr[pos / 2]){
                    while(tempPos > 1){
                        maxHeapify(arr, arrPos, arrStatic, tempPos, kth);
                        tempPos = tempPos / 2;
                    }
                }
            }else if(temp > arr[1] && (window == kth || temp <= arr[kth + 1])){
                swap(arr + pos, arr + 1 , arrStatic + arrPos[pos],
                     arrStatic + arrPos[1], arrPos + pos, arrPos + 1);
                int tempPos = pos / 2;
                if(arr[pos] > arr[pos / 2]){
                    while(tempPos > 1){
                        maxHeapify(arr, arrPos, arrStatic, tempPos, kth);
                        tempPos = tempPos / 2;
                    }
                }
            }else if(temp > arr[kth + 1]){
                swap(arr + pos, arr + kth + 1, arrStatic + arrPos[pos],
                     arrStatic + arrPos[kth + 1], arrPos + pos, arrPos + kth + 1);
                swap(arr + pos, arr + 1, arrStatic + arrPos[pos],
                     arrStatic + arrPos[1], arrPos + pos, arrPos + 1);
                minHeapify(&arr[kth], &arrPos[kth], arrStatic, 1, window - kth);
                int tempPos = pos / 2;
                if(arr[pos] > arr[pos / 2]){
                    while(tempPos > 1){
                        maxHeapify(arr, arrPos, arrStatic, tempPos, kth);
                        tempPos = tempPos / 2;
                    }
                }
            }
        }
//        debug(arr, window, kth);
//        debugPrint(arr, arrPos, arrStatic, window, kth, index);
        cout << endl << arr[1];
    }
}

void maxHeap(int*& arr, int*& arrPos, int**& arrStatic, int len, int window){
    for(int i = len / 2; i > 0; i--){
//        cout << "run" << endl;
        maxHeapify(arr, arrPos, arrStatic, i, len);
    }
    for(int i = 1; i <= window - len; i++){
        if(arr[1] > arr[len + i]){
            swap(arr + 1, arr + len + i, arrStatic + arrPos[1], arrStatic + arrPos[len + i], arrPos + 1, arrPos + len + i);
            maxHeapify(arr, arrPos, arrStatic, 1, len);
        }
    }
}

void minHeap(int* arr, int* arrPos, int**& arrStatic, int len){
    for(int i = len / 2; i > 0; i--){
        minHeapify(arr, arrPos, arrStatic, i, len);
    }
}

void maxHeapify(int*& arr, int*& arrPos, int**& arrStatic, int root, int len){
    int left = 2 * root,
        right = 2 * root + 1,
        large = root;
    if (left <= len && arr[left] > arr[root]) {
        large = left;
    }
    if (right <= len && arr[right] > arr[large]) {
        large = right;
    }
    if (large != root) {
        swap(arr + root, arr + large, arrStatic + arrPos[root], arrStatic + arrPos[large], arrPos + root, arrPos + large);
        maxHeapify(arr, arrPos, arrStatic, large, len);
    }
}

void minHeapify(int* arr, int* arrPos, int**& arrStatic, int root, int len){
    int left = 2 * root,
            right = 2 * root + 1,
            large = root;

    if (left <= len && *(arr + left) < *(arr + root)) {
        large = left;
    }
    if (right <= len && *(arr + right) < *(arr + large)) {
        large = right;
    }
    if (large != root) {
        swap(arr + root, arr + large, arrStatic + arrPos[root], arrStatic + arrPos[large], arrPos + root, arrPos + large);
        minHeapify(arr, arrPos, arrStatic, large, len);
    }
}

void swap(int* a, int* b, int** c, int** d, int* e, int* f){
    int temp = *a;
    *a = *b;
    *b = temp;
    *c = b;
    *d = a;
    temp = *e;
    *e = *f;
    *f = temp;
}

void debugPrint(int*& arr, int*& arrPos, int**& arrStatic, int window, int kth, int index){
    cout << endl << endl << "========= Original =======" << endl;
    for(int i = 1; i <= window; i++){
        if(i == index){
            cout << "[" << *arrStatic[i] << "] ";
        }else{
            cout << *arrStatic[i] << " ";
        }
    }
    cout << endl << "========= Heap ========" << endl;
    for(int i = 1; i <= window; i++){
        if(i == kth + 1 || i == 1){
            cout << "[" << arr[i] << "] ";
        }else{
            cout << arr[i] << " ";
        }
    }
    cout << endl << "========= Pos ========" << endl;
    for(int i = 1; i <= window; i++){
        cout << arrPos[i] << " ";
    }
    cout << endl;
}

void debug(int*& arr, int window, int kth){
    for(int i = 2; i <= kth; i++){
        if(arr[i] > arr[i / 2]){
//            cout << arr[i] << " " << arr[i / 2] << endl;
            cout << endl << "max error " << i << endl;
        }
    }
    for(int i = 2; i <= window - kth; i++){
        if(arr[kth + i] < arr[kth + i / 2]){
//            cout << arr[kth + i] << " " << arr[kth + i / 2] << endl;
            cout << endl << "min error " << i << endl;
        }
    }
}
