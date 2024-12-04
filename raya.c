#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
//deklarasi struct data yang berisi nama, nrp, dan nomor hp
struct Data{
    char nama[50];
    char nrp[50];
    char hp[50];
};

//deklarasi node dari linked list yang berisi struct data yang dideklarasikan sebelumnya
struct Node{
    struct Data data_mhs;
    struct Node* next; // di sini terdapat pointer ke alamat node selanjutnya
};

//ini adalah function untuk membuat suatu node baru
struct Node* createNode(struct Data new_data){
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node)); //mengalokasikan memori untuk new_node
    new_node->data_mhs = new_data; //mengisi elemen dalam node yaitu data_mhs dengan new_data yang akan diterima
    new_node->next = NULL; //mengset node selanjutnya NULL
    return new_node; //mengembalikan node baru
};

//function untuk memasukkan node baru ke posisi head (paling awal)
struct Node* insertAtFront(struct Node* head, struct Data new_data) {
    struct Node* new_node = createNode(new_data); //membuat node baru dengan function createNode yang menerima new_data
    new_node->next = head; //pointer new node diset menjadi head yang mana new node akan menjadi node baru mengisi posisi head
    return new_node; //mengembalikan pointer new_node sebagai head baru di linked list
}

// head-> node -> node

//function untuk memasukkan node di posisi akhir
struct Node* insertAtEnd(struct Node* head, struct Data new_data)
{
    struct Node* new_node = createNode(new_data); //membuat node baru  dengan function createNode
    if (head == NULL) {
        return new_node;
    } //jika head tidak ada isinya, maka mengembalikan pointer new_node
    struct Node* last = head; //last diset dengan head

    //pindah ke node selanjutnya apabila selanjutnya masih ada isinya
    while (last->next != NULL) {
        last = last->next;
    }
    //apabila node selanjutnya kosong (berarti node sekarang ini berada di tail)
    last->next = new_node; //mengisi node selanjutnya dengan new_node (node baru)
    return head; //mengembalikan pointer head
}

//untuk mengisi node di posisi tertentu
struct Node* insertPos(struct Node* head, struct Data new_data, int position){
    if (position < 1) return head; //jika posisi kurang dari 1 (yang berarti tidak valid) mengembalikan head
    //case apabila posisi satu yang berarti index 0 (head)
    if(position == 1){
        struct Node *newNode = createNode(new_data); //membuat node baru dengan createNode
        newNode->next = head; //pointer newNode diset menjadi head di mana new node akan menjadi node baru di posisi head
        return newNode; 
        //ini sasma seperti insert at front
    }

    struct Node* curr = head; //set curr menjadi head karena dimulai dari head
    for (int i = 1; i < position - 1 && curr != NULL; i++) { //position-1 dikarenakan index dari 0, loop sampai terakhir
        curr = curr->next; //mengubah curr menjadi node selanjutnya
    }

    if (curr == NULL) return head; //kalau curr kosong (berarti sudah sampai akhir) mengembalikan head

    struct Node *newNode = createNode(new_data); //membuat node baru dengan createNode
    // memperbarui pointer selanjutnya
    newNode->next = curr->next; 
    curr->next = newNode;

    return head; //mengembalikan head setelah diproses
}

struct Node* deleteHead(struct Node* head) {
    // check head kosong atau tidak
    if (head == NULL)
        return NULL;
    //menaruh head ke variabel temp
    struct Node* temp = head;
    // memindah pounter head ke node selanjutnya
    head = head->next;
    // free memory node head yang lama
    free(temp);

    return head;
}

//menghapus node di posisi tail
struct Node* removeLastNode(struct Node* head)
{
    // check head ada isinya atau tidak
    if (head == NULL) {
        return NULL;
    }

    // jika list hanya ada 1 node, hapus node lalu return NULL
    if (head->next == NULL) {
        free(head);
        return NULL;
    }

    // untuk mencari node terakhir yang kedua
    struct Node* second_last = head;
    while (second_last->next->next != NULL) {
        second_last = second_last->next;
    }

    // menghapus node terakhir
    free(second_last->next);

    // mengubah setelah second last menjadi NULL
    second_last->next = NULL;

    return head;
}

//function ini menerima parameter posisi juga untuk menghapus pada posisi tertentu (pos - 1)
struct Node* deletePos(struct Node* head, int pos){
    struct Node* temp = head; //set variabel temporary dengan head
    struct Node* prev = NULL; //set node sebelumnya dengan null

    if(temp == NULL) return head; //apabila temp == NULL yang mana tidak ada isinya, return head
    //ini dilakukan jika yang dihapus adalah index 0 (head)
    if (pos == 1) {
        head = temp->next;
        free(temp);
        return head;
    }
    
    //case sesuai posisi (apabila ditengah)
    for (int i = 1; temp != NULL && i < pos; i++) {
        prev = temp;
        temp = temp->next;
    }

    //jika ditemukan, hapus node yang dipilih
    if (temp != NULL) {
        prev->next = temp->next;
        free(temp);
    }
    else {
        printf("Data tidak ada\n");
    }

    return head;
}

//untuk menampilkan node yang dimulai dari head (posisi paling awal)
void printList(struct Node* head) {
    struct Node* curr = head; //set current menjadi head karena dimulai paling awal
    while (curr != NULL) { //loop dijalankan apabila curr ada isinya dan berhenti apabila sudah di tail
        printf("%s\n", curr->data_mhs.nama); //menampilkan nama 
        printf("%s\n", curr->data_mhs.nrp); //menampilkan nrp
        printf("%s", curr->data_mhs.hp); //menampilkan no hp
        printf("\n");
        curr = curr->next; //curr diisi node selanjutnya untuk ditampilkan 
    }
    printf("\n");
}


int main(){
    //mengisi data
    struct Data data1 = {"Raya", "5027241041", "088111111"};
    struct Data data2 = {"sulaiman", "5027241042", "0881112"};
    struct Data data3 = {"prabowo", "5027241043", "08811123"};

    struct Data front = {"windah basudara", "5027241044", "081111234"};
    struct Data end = {"windy", "5027241045", "0811112345"};
    struct Data index = {"sendy", "5027241046", "08811123456"};
    //membuat node
    struct Node* head = createNode(data1);
    head->next = createNode(data2);
    head->next->next = createNode(data3);

    //memasukkan node di posisi head
    head = insertAtFront(head, front);
    //memasukkan node di posisi tail
    head = insertAtEnd(head, end);
    //memasukkan node di posisi tertentu
    head = insertPos(head, index, 3); //masuk ke index 2 karena position-1

    //menampilkan node (original)
    printList(head);

    //mulai dari sini akan ditampilkan node setelah dihapus
    printf("linked list setelah head dihapus: \n");
    head = deleteHead(head);
    printList(head); //bisa dilihat tidak ada data windah basudara di output

    printf("linked list setelah tail dihapus: \n");
    head = removeLastNode(head);
    printList(head); //bisa dilihat tidak ada data windy setelah dihapus

    printf("linked list setelah suatu index dihapus (contoh index 2): \n");
    head = deletePos(head, 3); 
    printList(head); //dapat dilihat di output tidak ada data sulaiman yang sebelumnya berada di index 2

    return 0;
}