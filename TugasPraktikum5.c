#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*===================Global=======================*/
typedef char* String;

typedef struct Node {
    String nm;
    struct Node* next;
} Node;

int n = 0;
String* kota = NULL;
Node** p = NULL;

/*================Modul Program===================*/
void displayMenu(){
    printf("\n=======Data Induk Asal Kota Mahasiswa=======\n");
    printf("Pilihan menu operasi: \n");
    printf("1. Tambah Kota\n");
    printf("2. Tambah Mahasiswa\n");
    printf("3. Hapus Kota\n");
    printf("4. Hapus Data Mahasiswa\n");
    printf("5. Tampilkan Data Mahasiswa per Kota\n");
    printf("6. Cari Mahasiswa\n");
    printf("7. Tampilkan Daftar Kota\n");
    printf("99. Keluar Program\n");
}

int chooseMenu(){
    int pilih;

    printf("Masukkan pilihan anda: ");
    scanf("%d", &pilih);

    return pilih;
}

int findKotaIndex(String kt) {
    for (int i = 0; i < n; i++) {
        if (strcmp(kt, kota[i]) == 0) {
            return i;
        }
    }
    return -2; // kota tidak ditemukan
}

void tambahKota() {
    String inputKota = (String) malloc(100 * sizeof(char));

    printf("Masukkan nama kota: ");
    scanf("%s", inputKota);

    n++;
    kota = (String*) realloc(kota, n * sizeof(String));
    kota[n-1] = (String) malloc((strlen(inputKota) + 1) * sizeof(char));
    strcpy(kota[n-1], inputKota);
    p = (Node**) realloc(p, n * sizeof(Node*));
    p[n-1] = NULL;

    free(inputKota);
}

void tambahMahasiswa() {
    char inputKota[50], inputMahasiswa[50];
    int kotaIndex;

    printf("Masukkan nama kota: ");
    scanf("%s", inputKota);

    kotaIndex = findKotaIndex(inputKota);
    if (kotaIndex == -2) {
        printf("Kota tidak ditemukan\n");
        return;
    }

    printf("Masukkan nama mahasiswa: ");
    scanf("%s", inputMahasiswa);

    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->nm = (char*) malloc((strlen(inputMahasiswa) + 1) * sizeof(char));
    strcpy(newNode->nm, inputMahasiswa);
    newNode->next = p[kotaIndex];
    p[kotaIndex] = newNode;
    
}

void hapusKota() {
    char inputKota[100];
    int countDelMhs = 0;

    printf("Masukkan nama kota: ");
    scanf("%s", &inputKota);

    int kotaidx = findKotaIndex(inputKota);

    if (kotaidx == -2) {
        printf("Kota tidak ditemukan\n");
        return;
    }

    Node* city = p[kotaidx];
    Node* prev = NULL;

    while (city != NULL) {
        Node* temp = city;
        city = city->next;
        free(temp);
        countDelMhs++;
    }

    if (prev == NULL) {
        p[kotaidx] = NULL;
    } else {
        prev->next = NULL;
    }

    // hapus nama kota dari array kota
    for (int i = kotaidx; i < n - 1; i++) {
        p[i] = p[i+1];
        strcpy(kota[i], kota[i+1]);
    }

    // kosongkan elemen terakhir di array p dan kota
    p[n-1] = NULL;
    strcpy(kota[n-1], "");

    // kurangi jumlah kota
    n--;

    printf("Kota %s dan nama-nama mahasiswa di dalamnya berhasil dihapus\n", inputKota);
}

void hapusMahasiswa() {
    char inputKota[50], inputMahasiswa[50];
    int kotaIndex;

    printf("Masukkan nama kota: ");
    scanf("%s", inputKota);

    kotaIndex = findKotaIndex(inputKota);
    if (kotaIndex == -1) {
        printf("Kota tidak ditemukan\n");
        return;
    }

    printf("Masukkan nama mahasiswa: ");
    scanf("%s", inputMahasiswa);

    Node* city = p[kotaIndex];
    Node* prev = NULL;
    while (city != NULL) {
        if (strcmp(city->nm, inputMahasiswa) == 0) {
            if (prev == NULL) {
                p[kotaIndex] = city->next;
            } else {
                prev->next = city->next;
            }
            free(city);
            printf("%s dihapus dari kota %s\n", inputMahasiswa, inputKota);
            return;
        }
        prev = city;
        city = city->next;
    }

    printf("%s tidak ditemukan di kota %s\n", inputMahasiswa, inputKota);
}

int countMahasiswaPerKota() {
    int count;
    for (int i = 0; i < n; i++) {
        count = 0;
        Node* city = p[i];
        while (city != NULL) {
            count++;
            city = city->next;
        }
    }

    return count;
}

void displayMahasiswaperKota() {
    char inputKota[100];
    int kotaIndex;

    int sumMhsKt = countMahasiswaPerKota();

    printf("Masukkan nama kota: ");
    scanf("%s", &inputKota);

    kotaIndex = findKotaIndex(inputKota);
    if (kotaIndex == -2) {
        printf("Kota tidak ditemukan\n");
        return;
    }

    printf("Mahasiswa pada kota %s berjumlah %d dengan nama-nama:\n", inputKota, sumMhsKt);
    Node* city = p[kotaIndex];
    int i =1;
    while (city != NULL) {
        printf("%d. %s\n",i, city->nm);
        city = city->next;
        i++;
    }
}

void cariMahasiswaAsalKota() {
    char inputMahasiswa[50];
    Node* city;

    printf("Masukkan nama mahasiswa: ");
    scanf("%s", inputMahasiswa);

    for (int i = 0; i < n; i++) {
        city = p[i];
        while (city != NULL) {
            if (strcmp(city->nm, inputMahasiswa) == 0) {
                printf("%s berasal dari kota %s\n", inputMahasiswa, kota[i]);
                return;
            }
            city = city->next;
        }
    }

    printf("%s tidak ditemukan di semua kota\n", inputMahasiswa);
}

int countKota() {
    int count = 0;
    for (int i = 0; i < n; i++) {
        count++;
    }
    return count;
}

void displayKota(){
    int sumKota = countKota();
    if(n!=0){
        printf("Kota yang terdaftar sebanyak %d kota\n", sumKota);
        printf("Berikut adalah daftar nama kota:\n");
        for (int i = 0; i < n; i++) {
            printf("%d. %s\n",(i+1), kota[i]);
        }
    }else{
        printf("Belum ada kota yang terdaftar\n");
    }
        
}




/*=================Main Program===================*/
int main(){
    int choice;
    
    while (1){
        displayMenu();
        choice = chooseMenu();
        switch (choice){
        case 1:
            tambahKota();
            break;
        case 2:
            tambahMahasiswa();
            
            break;
        case 3:
            hapusKota();
            break;
        case 4:
            hapusMahasiswa();
            break;
        case 5:
            displayMahasiswaperKota();
            break;
        case 6:
            cariMahasiswaAsalKota();
            break;
        case 7:
            displayKota();
            break;         
        case 99:
            exit(0);
            break;                        
        }
    }

}