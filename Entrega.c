#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000000
#define BLOCO 100

void preencher(int x[]);
void bubble(int x[], int y);
void arquivo(int *x, int y, const char *arquivo);
int busca(int *indice, int tam, const char *arquivo, int chave);

int main(){
    int *registros = (int*) malloc(MAX * sizeof(int));
    int blocos = MAX / BLOCO;
    int *indice = (int*) malloc(blocos * sizeof(int));
    srand(time(NULL));

    preencher(registros);
    bubble(registros,MAX);
    arquivo(registros, MAX, "ordenados.txt");

    indices(indice, BLOCO, "ordenados.txt");

    int chave;
    scanf("%d", &chave);

    int resultado = busca(indice, BLOCO, "ordenados.txt", chave);
    if(resultado != -1){
        printf("Número %d encontrado!\n", resultado);
    }else{
        printf("Número não encontrado.\n");
    }

    free(registros);
    free(indice);
    return 0;
}

void preencher(int x[]){
    for (int i = 0; i < MAX; i++){
        x[i] = rand();
        
    }
    
}

void bubble(int x[], int y){
    for(int i = 0; i < y - 1; i++){
        for(int j = 0; j < y - i - 1; j++){
            if(x[j] > x[j + 1]){
                int guarda = x[j];
                x[j] = x[j + 1];
                x[j + 1] = guarda;
            }
        }
    }
}

void arquivo(int *x, int y, const char *arquivo){
    FILE *file = fopen(arquivo, "w");
    
    for(int i = 0; i < y; i++){
        fprintf(file, "%d\n", x[i]);  
    }

    fclose(file);
}

void indices(int *indice, int tam, const char *arquivo) {
    FILE *file = fopen(arquivo, "r");
    
    int valor;
    int i = 0;
    int bloco = 0;
    while(fscanf(file, "%d", &valor) == 1){
        if(i % tam == 0){
            indice[bloco] = valor;
            bloco++;
        }
        i++;
    }

    fclose(file);
}

int busca(int *indice, int tam, const char *arquivo, int chave){
    FILE *file = fopen(arquivo, "r");
    
    int bloco = -1;
    for(int i = 0; i < MAX / tam; i++){
        if(indice[i] > chave){
            bloco = i - 1;
            break;
        }
    }
    if(bloco == -1) bloco = (MAX / tam) - 1;

    fseek(file, bloco * tam * sizeof(int), SEEK_SET);

    int valor;
    for(int i = 0; i < tam; i++){
        if(fscanf(file, "%d", &valor)!= 1)break;
        if(valor == chave){
            fclose(file);
            return valor;  
        }
    }

    fclose(file);
    return -1;  
}
