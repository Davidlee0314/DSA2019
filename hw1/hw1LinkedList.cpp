//
// Created by 李得瑋 on 2019-03-08.
//

#include <iostream>
using namespace std;

class LinkedList;

/*  LinkedNode  */

class LinkedNode{
public:
    int data;
    LinkedNode* next;
    LinkedNode* prev;
    explicit LinkedNode(int);
    ~LinkedNode();
};

LinkedNode::LinkedNode(int a) {
    this->data = a;
    this->next = nullptr;
    this->prev = nullptr;
}
LinkedNode::~LinkedNode() {
    delete next;
}

/*  LinkedList  */

class LinkedList{
public:
    LinkedNode* first;
    LinkedList();

    //only add from back
    void printList();
    void changePos(LinkedNode* , LinkedNode*);
    void insert(LinkedNode* , LinkedNode*);
    void sort();
};

LinkedList::LinkedList() {
    this->first = nullptr;
}

void LinkedList::printList(){
    LinkedNode* current = this->first;
    while(current->next != nullptr){
        cout << current->data << " ";
        current = current->next;
    }
    cout << current->data;
}

void LinkedList::changePos(LinkedNode* a, LinkedNode* b){
    LinkedNode* tempNext = nullptr;
    LinkedNode* tempPrev = nullptr;
    tempNext = b->next;
    tempPrev = b->prev;
    b->next = a->next;
    b->prev = a->prev;
    a->next = tempNext;
    a->prev = tempPrev;
}

//a put in the back of b
void LinkedList::insert(LinkedNode * a, LinkedNode * b) {
    //change a prev and next nodes data
    if(a->prev){
        a->prev->next = a->next;
    }else{
        this->first = a->next;
        a->next->prev = nullptr;
    }
    if(a->next){
        a->next->prev = a->prev;
    }

    //four chains need update
    a->next = b->next;
    if(b->next){
        b->next->prev = a;
    }
    a->prev = b;
    b->next = a;
}

void LinkedList::sort(){
    LinkedNode* bar = this->first->next;
    while(bar != nullptr){
        LinkedNode* now = this->first;
        LinkedNode* next = bar->next;
        while(now != bar){
//            cout << bar->data << ": " << now->data << endl;
            if(now->prev != nullptr){
                if(bar->data < now->data && bar->data >= now->prev->data){
                    this->insert(bar, now->prev);
                    break;
                }
            }else{
                if(bar->data < now->data){
                    this->first = bar;
                    bar->prev->next = bar->next;
                    bar->next->prev = bar->prev;

                    bar->next = now;
                    bar->prev = nullptr;
                    now->prev = bar;
                    break;
                }
            }
            now = now->next;
        }
//        cout << "move bar " << endl;
        bar = next;
    }
}
/* function */

void createList(LinkedNode** listOrigin, LinkedList* list, int n){
    LinkedNode* current = nullptr;
    for(int i = 0; i < n; i++){
        int temp = 0;
        cin >> temp;
        LinkedNode* a = new LinkedNode(temp);
        listOrigin[i] = a;
        if(list->first == nullptr){
            list->first = a;
            current = a;
        }else{
            current->next = a;
            a->prev = current;
            current = a;
        }
    }
}

void findKth(LinkedNode** listOrigin, LinkedList* list, int kth, int window, int loop){
    //find first kth data
    LinkedNode* current = list->first;
    for(int i = 1; i <= window; i++){
        if(i == kth){
            cout << current->data;
            break;
        }
        current = current->next;
    }
    //current store the kth data
    LinkedNode* now = nullptr;
    int beforeChange = current->data;
    for(int i = 0; i < loop; i++){
        int temp = 0;
        cin >> temp;
        int index = i % window;
        int beforeInt = listOrigin[index]->data;
        bool duplicate = false;
        int change;

        //see whether the kth data is changed
        listOrigin[index]->data = temp;
        if(current->data != beforeChange){
            current = current->next;
            duplicate = true;
        }
        now = current;

        //record how data will change position
        if(beforeInt < current->data && temp > current->data){
            change = 1;
        }else if(beforeInt > current->data && temp < current->data){
            change = 2;
        }else{
            change = 0;
        }

//        cout << endl <<" change --" << change << endl;
//        cout << endl << "current --" << current->data << endl;

        bool noChange = false;
        if(listOrigin[index]->prev && listOrigin[index]->next){
            if(listOrigin[index]->prev->data <= listOrigin[index]->data &&
               listOrigin[index]->next->data >= listOrigin[index]->data){
                noChange = true;
            }
        }else if(!listOrigin[index]->prev){
            if(listOrigin[index]->next->data >= listOrigin[index]->data){
                noChange = true;
            }
        }else if(!listOrigin[index]->next){
            if(listOrigin[index]->prev->data >= listOrigin[index]->data){
                noChange = true;
            }
        }


        //find the position of new data first, and insert it into the array
        if(!noChange){
            if(current->data < temp){
                while(now != nullptr){
                    if(now->data > temp){
                        list->insert(listOrigin[index], now->prev);
                        break;
                    }else if(now->next == nullptr){
                        list->insert(listOrigin[index], now);
                        break;
                    }
                    now = now->next;
                }
            }else if(current->data > temp){
                while(now != nullptr){
                    if(now->data < temp){
                        list->insert(listOrigin[index], now);
                        break;
                    }else if(now->prev == nullptr){
                        list->first = listOrigin[index];
                        if(listOrigin[index]->next){
                            listOrigin[index]->next->prev = listOrigin[index]->prev;
                        }
                        listOrigin[index]->prev->next = listOrigin[index]->next;

                        now->prev = listOrigin[index];
                        listOrigin[index]->next = now;
                        listOrigin[index]->prev = nullptr;
                        break;
                    }
                    now = now->prev;
                }
            }
        }


        if(!duplicate){
            if(change == 1){
                current = current->next;
            }else if(change == 2){
                current = current->prev;
            }
        }else{
            if(change == 2){
                current = current->prev->prev;
            }else if(change == 0){
                current = current->prev;
            }
        }
//        cout << endl << "current after --" << current->data << endl;
        beforeChange = current->data;
//        cout << endl;
//        list->printList();
        cout << endl << current->data;
    }
}

int main(){
    LinkedList* list = new LinkedList();
    int n = 0, window = 0, kth = 0;
    cin >> n >> window >> kth;
    LinkedNode** listOrigin = new LinkedNode*[window];

    //create list for sort and record position
    createList(listOrigin, list, window);
//    list -> printList();
//    cout << endl;

    //sort the window list first
    list->sort();
    findKth(listOrigin, list, kth, window, n - window);
    return 0;
}