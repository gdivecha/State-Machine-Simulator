#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct STATE{
    char currentState;
    struct STATE* next0;
    struct STATE* next1;
    bool deleted;
}state;

state* findStateIn0(char stateSymbol, state* head);
state* findStateIn1(char stateSymbol, state* head);
void change0(state* insertState, state* current);
void change1(state* insertState, state* current);
void getNumReachable(state* current, int reachable[]);
int getStateNum(char c);
bool getChoice(char c);
void getReachable(state* current, int reachable[8]);

state* findStateIn0(char stateSymbol, state* head){
    state* iterator = head;
    bool isLooping = false;
    while((!isLooping)&&(iterator!=NULL)&&((iterator->currentState)!=(stateSymbol))){
        if((iterator->currentState)==(iterator->next0->currentState)){
            isLooping = true;
            iterator = findStateIn1(stateSymbol, iterator);
        }
        if(!isLooping){
            iterator = iterator->next0;
            isLooping = false;
        }
    }
    return iterator;
}

state* findStateIn1(char stateSymbol, state* head){
    state* iterator = head;
    bool isLooping = false;
    while((!isLooping)&&(iterator!=NULL)&&((iterator->currentState)!=(stateSymbol))){
        if((iterator->currentState)==(iterator->next1->currentState)){
            isLooping = true;
            iterator = findStateIn0(stateSymbol, iterator);
        }
        if(!isLooping){
            iterator = iterator->next1;
            isLooping = false;
        }
    }
    return iterator;
}

void change0(state* insertState, state* current){
    current->next0 = insertState;
}

void change1(state* insertState, state* current){
    current->next1 = insertState;
}

int getStateNum(char c){
    switch(c){
        case 'A':
            return 0;
        case 'B':
            return 1;
        case 'C':
            return 2;
        case 'D':
            return 3;
        case 'E':
            return 4;
        case 'F':
            return 5;
        case 'G':
            return 6;
        case 'H':
            return 7;
    }
}

void getNumReachable(state* current, int reachable[8]){
    reachable[getStateNum(current->currentState)] = 1;
    if(0==reachable[getStateNum(current->next0->currentState)]){
        getNumReachable(current->next0, reachable);
    }
    if(0==reachable[getStateNum(current->next1->currentState)]){
        getNumReachable(current->next1, reachable);
    }
}

void getReachable(state* current, int reachable[8]){
    int i;
    for(i=0; i<8; i++){
        reachable[i] = 0;
    }
    getNumReachable(current, reachable);
}

bool getChoice(char c){
    if((c=='A')||(c=='B')||(c=='C')||(c=='D')||(c=='E')||(c=='F')||(c=='G')||(c=='H')){
        return true;
    }
    return false;
}

int main (void){
    state a, b, c, d, e, f, g, h;
    
    a.currentState = 'A';
    b.currentState = 'B';
    c.currentState = 'C';
    d.currentState = 'D';
    e.currentState = 'E';
    f.currentState = 'F';
    g.currentState = 'G';
    h.currentState = 'H';

    a.deleted = false;
    b.deleted = false;
    c.deleted = false;
    d.deleted = false;
    e.deleted = false;
    f.deleted = false;
    g.deleted = false;
    h.deleted = false;

    state* startingState;
    startingState = &h;

    h.next0 = &b;
    h.next1 = &f;
    a.next0 = &e;
    a.next1 = &h;
    b.next0 = &b;
    b.next1 = &c;
    c.next0 = &a;
    c.next1 = &e;
    d.next0 = &f;
    d.next1 = &a;
    e.next0 = &g;
    e.next1 = &d;
    f.next0 = &h;
    f.next1 = &g;
    g.next0 = &d;
    g.next1 = &b;

    state* listOfStates[] = {&a, &b, &c, &d, &e, &f, &g, &h};

    printf("%c\n", h.currentState);

    int i;
    int countNum = 0;
    char input[6];
    bool error = false;
    state* current = startingState;
    int reachable[] = {0,0,0,0,0,0,0,0};
    while(!error){
        for(i=0; i<6; i++){
            input[i] = '\0';
        }
        gets(input);
        if((input[0]!='0')&&(input[0]!='1')&&(input[0]!='c')&&(input[0]!='p')&&(input[0]!='g')&&(input[0]!='d')){
            printf("The program has been terminated!\n");
            error = true;
        }
        else if((input[0])=='0'){
            current = current->next0;
            printf("%c\n", current->currentState);
            error = false;
        }
        else if((input[0])=='1'){
            current = current->next1;
            printf("%c\n", current->currentState);
            error = false;
        }
        else{
            switch(input[0]){
                case 'c':
                    if(listOfStates[getStateNum(input[4])]->deleted==false){
                        if(input[2]=='0'){
                            if((reachable[getStateNum(input[4])]==0)&&((listOfStates[getStateNum(input[4])]->deleted)==false)){
                                reachable[getStateNum(input[4])]=1;
                                state* intendedState = listOfStates[getStateNum(input[4])];
                                change0(intendedState, current);
                            }
                            else{
                                state* intendedState = findStateIn0(input[4], startingState);
                                change0(intendedState, current);
                            }
                        }
                        else if(input[2]=='1'){
                            if((reachable[getStateNum(input[4])]==0)&&((listOfStates[getStateNum(input[4])]->deleted)==false)){
                                reachable[getStateNum(input[4])]=1;
                                state* intendedState = listOfStates[getStateNum(input[4])];
                                change1(intendedState, current);
                            }
                            else{
                                state* intendedState = findStateIn0(input[4], startingState);
                                change1(intendedState, current);
                            }
                        }
                    }
                    break;
                case 'p':
                    getReachable(current, reachable);
                    for(i=0; i<8; i++){
                        if(listOfStates[i]->deleted==false){
                            char currentName = listOfStates[i]->currentState;
                            char currentNext0Name = listOfStates[i]->next0->currentState;
                            char currentNext1Name = listOfStates[i]->next1->currentState;
                            printf("%c %c %c\n", currentName, currentNext0Name, currentNext1Name);
                        }
                    }
                    error = false;
                    break;
                case 'g':
                    getReachable(current, reachable);
                    countNum = 0;
                    int j = 0;
                    for(i=0; i<8; i++){
                        if(reachable[i]==1){
                            j++;
                        }
                    }
                    if(j!=8){
                        printf("Garbage: ");
                    }
                    for(i=0; i<8; i++){
                        if((reachable[i]==0)&&(listOfStates[i]->deleted==false)){
                            char currentName = listOfStates[i]->currentState;
                            printf("%c ", currentName);
                        }
                        else{
                            countNum++;
                        }
                    }
                    if(countNum==8){
                        printf("No Garbage");
                    }
                    printf("\n");
                    error = false;
                    break;
                case 'd':
                    getReachable(current, reachable);
                    if(input[2]=='\0'){
                        printf("Deleted: ");
                        for(i=0; i<8; i++){
                            if((reachable[i]==0)&&(listOfStates[i]->deleted==false)){
                                listOfStates[i]->next0 = NULL;
                                listOfStates[i]->next1 = NULL;
                                listOfStates[i]->deleted = true;
                                printf("%c ", listOfStates[i]->currentState);
                            }
                        }
                    }
                    else if(!getChoice(input[2])){
                        printf("No states deleted.");
                    }
                    else if(getChoice(input[2])){
                        int counter = 0;
                        for(i=0; i<8; i++){
                            if(((reachable[i]==0)&&(listOfStates[i]->deleted==false))&&(listOfStates[i]->currentState==input[2])){
                                listOfStates[i]->next0 = NULL;
                                listOfStates[i]->next1 = NULL;
                                listOfStates[i]->deleted = true;
                                printf("Deleted.");
                                counter++;
                            }
                        }
                        if(counter==0){
                            printf("Not Deleted.");
                        }
                    }
                    printf("\n");
                    error = false;
                    break;
            }
        }
    }
}
