/*
   HEAP é uma árvore binária completa, ou seja, uma árvore binaria onde cada nivel
   é preenchido da esquerda pra direita e deve estar completo antes que o próximo
   nível seja preenchido.
   Há uma restrição especial: cada nó da heap deve conter um valor maior (ou menor)
   do que todos os valores contidos por nós descendentes dele.

    Pode ser utilizado em:
                       - Simulações
                       - Compressão de dados
                       - Algoritmos de grafos
                       - IA
                       - Estatística
                       - SO

    Devido ao fato de a HEAP ser "previsivel", é possível representá-la de forma
    através de um único vetor.
    Pai: [(j-1)/2]
    Filhos: [2j+1] e [2j+2]

    Primeiro nó que tem filhos, considerando leitura de baixo pra cima e da direita pra esquerda: n/2 - 1

*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>

#define INFINITY 100000000000
#define SIZE 15

using namespace std;

int last; //ultimo elemento da heap


void print(int *vet){
    for(int i = 0; i < SIZE; i++){
        cout << vet[i] << " ";
    }
    cout << endl;
}


void heapfy_menor(int *vet, int n, int pai){
    int esq = 2*pai + 1; //filho esquerdo
    int dir = 2*pai + 2; //filho direito
    int menor, aux;

    //Escolhe maior valor entre filhos
    menor = pai;
    if((esq < n) && (vet[esq] < vet[menor])){
        menor = esq;
    }  
    if((dir < n) && (vet[dir] < vet[menor])){
        menor = dir;
    }

    // se um dos filhos for maior que o pai, troca
    if(menor != pai){
        aux = vet[menor];
        vet[menor] = vet[pai];
        vet[pai] = aux;

        //continua descida
        heapfy_menor(vet, n, menor);
    }
}

void create_heap_menor(int *vet, int n){
    // para cada nó que não é folha
    for(int i = n/2-1; i >= 0; i--){
        heapfy_menor(vet, n, i); // ajusta a heap de baixo pra cima
    }
}

void heapsort(int *vet, int n){
    int aux;
    create_heap_menor(vet, n);
    for(int i=n-1; i>0; i--){
        //troca o maior elemento com o ultimo
        aux = vet[0];
        vet[0] = vet[i];
        vet[i] = aux;
        n--; // diminui o tamanho da heap (ultimo elemento ja ordenado)
        heapfy_menor(vet, n, 0); //ajusta a heap
    }
}

bool empty(int *vet){
    return last == 0;
}

bool full(int *vet){
    return last == SIZE;
}

void push(int *vet, int elemento){
    if full(vet){
        vet[last] = elemento;
        last++;
        create_heap_menor(vet, last);
    }else{
        cout << "Heap cheia" << endl;
    }
    print(vet);
}

int pop(int *vet){
    int aux = -1;
    if empty(vet){
        cout << "Heap vazia" << endl;
    }else{
        aux = vet[0];
        vet[0] = vet[last-1];
        last--;
        heapfy_menor(vet, last, 0);
    }
    print(vet);
    return aux;
}

int top(int *vet){
    return vet[0];
}



int main(){
    int vetor[SIZE]; //HEAP
    last = 0;
    
    for(int i = 0; i<SIZE; i++){
        vetor[i] = rand() % 100;
    }

    cout << "Heap desajustada: " << endl;
    print(vetor);

    //Ordena
    //heapsort(vetor,N);
    create_heap_maior(vetor, SIZE);

    cout << "Heap ajustada (maior): " << endl;
    print(vetor);

    create_heap_menor(vetor, SIZE);
    cout << "Heap ajustada (menor): " << endl;
    print(vetor);

    cout << "Heap sort: " << endl;
    heapsort(vetor, SIZE);
    print(vetor);

    return 0;
}