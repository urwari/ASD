#include <iostream>
#include <conio.h>

using namespace std;

namespace l {
struct element
{
    int value;
    element *next;
    element *early;
};
class list{
    element *first;
    element *last;
public:
    list(){
        first = NULL;
        last = NULL;
    }
    void push_back(int i){
        element *newelement = new element;
        newelement->value = i;
        if (first){
            newelement->early = first;
            first->next = newelement;
        }
        else
            last = newelement;
        newelement->next = last;
        last->early = newelement;
        first = newelement;
    }
    void print(){
        element *temp = first;
        if (first)
            do{
                   cout << temp->value << "\n";
                   temp = temp->early;
            } while(temp != first);
    }
};
}




int main()
{
    l::list testlist;
    for (int i = 1; i<10;i+=i)
         testlist.push_back(i);
    testlist.print();
    return 0;
}
