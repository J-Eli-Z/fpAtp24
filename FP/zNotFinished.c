#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char name[50], nrp[15], hp[15];
    struct node* next;
};

struct node* createNode(char name[], char nrp[], char hp[]) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    strcpy(newNode->name, name);
    strcpy(newNode->nrp, nrp);
    strcpy(newNode->hp, hp);
    newNode->next = NULL;
    return newNode;
}

void insertBeginning(struct node** head, char name[], char nrp[], char hp[]){
    struct node* newNode = createNode(name, nrp, hp); 
    newNode->next = *head;
    *head = newNode;
}

void printList(struct node *head){
    struct node* temp = head; 
    int pos = 1;
    while(temp != NULL){
        printf("Nama mahasiswa %d = %s\n", pos, temp->name);
        printf("NRP mahasiswa %d = %s\n", pos, temp->nrp);
        printf("No. HP mahasiswa %d = %s\n", pos, temp->hp);
        pos++; temp = temp->next;
    }
    printf("Sudah selesai listmu!");
}

int main(){
    struct node* head = NULL;
    
    int n; scanf("Tentukan jumlah mahasiswa yang ada: %d", &n);getchar();

    char name[n][50], nrp[n][15], hp[n][15];
    for(int i = 0; i<n; i++){
        printf("Tentukan nama mahasiswa %d:", (i+1)); 
        scanf("%[^\n]", name[i]); 
        getchar();
        printf("Tentukan NRP mahasiswa %d:", (i+1)); 
        scanf("%[^\n]", nrp[i]); 
        getchar();
        printf("Tentukan no. HP mahasiswa %d:", (i+1)); 
        scanf("%[^\n]", hp[i]); 
        getchar();
    }

    for(int i = 0; i<n; i++){
        insertBeginning(&head, name[i], nrp[i], hp[i]);
    }

    printList(head);
}