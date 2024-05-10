/*

 Requisitos Funcionais
-O sistema deve ter uma fila de tarefas pendentes, uma lista de tarefas concluídas e uma 
 pilha de tarefas em rascunho
-Toda tarefa criada pelo usuário deve ser enviada primeiro para a Fila de Tarefas Pendentes
-Toda tarefa que sair da Fila de Tarefas Pendentes deve ir para Lista de Tarefas Concluídas
-O usuário deve selecionar as tarefas que devem sair da Lista de Tarefas Concluídas indicando o ID da tarefa
-Toda tarefa que sair da Lista de Tarefas Concluídas deve ir para Pilha de Tarefas em Rascunho
-Toda tarefa que sair da Pilha de Tarefas em Rascunho deve ir para Fila de Tarefas Pendentes
-O usuário deve ter a opção de visualizar todo conteúdo de cada uma das estruturas mencionadas
-Todas as estruturas mencionadas devem se comportar de acordo com suas definições 
(Fila deve ser uma FIFO e Pilha uma LIFO)

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DESCRIPTION_SIZE 100

typedef struct Task {
    int id;
    char description[MAX_DESCRIPTION_SIZE];
    struct Task* prox;
} TASK;

// ASSISTANT STRUCTURES
TASK* tailCompletedList = NULL;
TASK* tailPendingQueue = NULL;
TASK* headDraftStack = NULL;
TASK* headPendingQueue = NULL;
TASK* headCompletedList = NULL;

// REPEATED FUNCTIONS
void addToList(TASK* newTask, TASK** head, TASK** tail);
TASK* popFirstElement(TASK** head);
void seeAllElements(TASK* head);

// CONSTRUCTOR
TASK* createTask(int id, char* description);
TASK* createTaskByScanf(void);

// LIST
void addToCompletedList(TASK* newTask);
TASK* removeFromCompletedListByItsId(int id);
void seeAllCompletedList(void);

// QUEUE
void putToPendingQueue(TASK* newTask);
TASK* getFromPendingQueue(void);
void seeAllPendingQueue(void);

// STACK
void pushToDraftStack(TASK* newTask);
TASK* popFirstElementDraftStack(void);
void seeAllDraftStack(void);

// MENU
void displayMenu(void);

int main(void) {
    int choice;
    printf("################# TASK MANAGER SYSTEM #################");

    do {
        displayMenu();
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // CREATE A TASK, THEN ADD TO PENDING QUEUE
                TASK* newTask = createTaskByScanf();
                putToPendingQueue(newTask);
                break;

            case 2:
                // SEE ALL TASKS FROM PENDING QUEUE
                seeAllPendingQueue();
                break;

            case 3:
                // COMPLETE FIRST PENDING TASK
                TASK* firstTask = getFromPendingQueue();
                if(firstTask != NULL) {
                    addToCompletedList(firstTask);
                }
                break;

            case 4:
                // SEE ALL TASKS FROM COMPLETED LIST
                seeAllCompletedList();
                break;

            case 5:
                // SET COMPLETED TASK TO DRAFT
                int id;
                printf("Enter Task ID (number): ");
                scanf("%d", &id);

                TASK* task = removeFromCompletedListByItsId(id);
                if(task != NULL) {
                    pushToDraftStack(task);
                }
                break;

            case 6:
                // SEE ALL TASKS FROM DRAFT STACK
                seeAllDraftStack();
                break;

            case 7:
                // SET LAST DRAFT AS PENDING TASK
                TASK* lastTask = popFirstElementDraftStack();
                if(lastTask != NULL) {
                    putToPendingQueue(lastTask);
                }
                break;

            case 0:
                printf("Exiting program\n");
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    } while (choice != 0);

    printf("################# SYSTEM SHUT DOWN #################");
}

// CONSTRUCTOR
TASK* createTask(int id, char* description) {
    TASK* newTask = (TASK*) malloc(sizeof(TASK));

    newTask->id = id;
    strcpy(newTask->description, description);
    newTask->prox = NULL;

    return newTask;
}

TASK* createTaskByScanf(void) {
    int id;
    char description[MAX_DESCRIPTION_SIZE];

    printf("Enter Task ID (number): ");
    scanf("%d", &id);

    getchar();
    printf("Enter Task Description (string): ");

    fgets(description, MAX_DESCRIPTION_SIZE, stdin);
    description[strcspn(description, "\n")] = '\0';

    return createTask(id, description);
}

// REPEATED FUNCTIONS
void addToList(TASK* newTask, TASK** head, TASK** tail){
    if(*head ==  NULL){
        *head = newTask;
        *tail = *head;
    }else{
        (*tail)->prox = newTask;
        *tail = (*tail)->prox;
    }
}

TASK* popFirstElement(TASK** head){
    if(*head != NULL){
        TASK* firstTask = *head;
        *head = (*head)->prox;
        firstTask->prox = NULL;
        return firstTask;
    }
    return NULL;
}

void seeAllElements(TASK* head){
    TASK* assistant = head;
    while(assistant != NULL){
        printf("%d | ",assistant->id);
        assistant = assistant->prox;
    }
}

// QUEUE
void putToPendingQueue(TASK* newTask) {
    printf("Putting Task to Pending Queue\n");
    // YOUR CODE HERE
    addToList(newTask, &headPendingQueue, &tailPendingQueue);
}

TASK* getFromPendingQueue(void) {
    printf("Getting Task from Pending Queue\n");
    // YOUR CODE HERE
    return popFirstElement(&headPendingQueue);
}

void seeAllPendingQueue(void) {
    printf("Printing All Pending Queue\n");
    // YOUR CODE HERE
    seeAllElements(headPendingQueue);
}

// LIST
void addToCompletedList(TASK* newTask) {
    printf("Adding Task to Completed List\n");
    // YOUR CODE HERE
    addToList(newTask, &headCompletedList, &tailCompletedList);
}

TASK* removeFromCompletedListByItsId(int id){
    printf("Removing Task from Completed List\n");
    TASK* assistant = headCompletedList; 
    TASK* desiredTask = NULL;
    // YOUR CODE HERE 
    if(headCompletedList == NULL){
        return NULL;
    }
    if(headCompletedList->id == id){
        desiredTask = headCompletedList;
        headCompletedList = headCompletedList->prox;
        desiredTask->prox = NULL;

        return desiredTask;

    }else{
        while(assistant->prox->id != id && assistant->prox != NULL){
            assistant = assistant->prox;
            
        }if(assistant->prox->id == id){
            desiredTask = assistant->prox;
            assistant->prox = assistant->prox->prox;
            desiredTask->prox = NULL;

            return desiredTask;

        }else{
            return NULL;
        }
    }
}

void seeAllCompletedList(void) {
    printf("Printing All Completed List\n");
    // YOUR CODE HERE
    seeAllElements(headCompletedList);
}

// STACK
void pushToDraftStack(TASK* newTask) {
    printf("Pushing Task to Draft Stack\n");
    // YOUR CODE HERE
    if(headDraftStack == NULL){
        headDraftStack = newTask;
    }else{
        newTask->prox = headDraftStack;
        headDraftStack = newTask; 
    }
}

TASK* popFirstElementDraftStack(void) {
    printf("Popping Task to Draft Stack\n");
    // YOUR CODE HERE
    return popFirstElement(&headDraftStack);
}

void seeAllDraftStack(void) {
    printf("Printing All Draft Stack\n");
    // YOUR CODE HERE
    seeAllElements(headDraftStack);
}

// MENU
void displayMenu(void) {
    printf("\nMenu:\n");
    printf("1 - Create New Pending Task\n");
    printf("2 - See All Pending Tasks\n");
    printf("3 - Complete First Pending Task\n");
    printf("4 - See All Completed Tasks\n");
    printf("5 - Set Completed Task as Draft by its ID\n");
    printf("6 - See All Draft Tasks\n");
    printf("7 - Set Last Draft Task as Pending Task\n");
    printf("0 - Exit\n");
}

