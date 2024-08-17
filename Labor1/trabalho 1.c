/*****************************************************************************
* Trabalho 1: Gerar um vetor de N números complexos V[n]=Re{V[n]}+jIm{V[n]}, n=0,1...N-1,
* usando alocação dinâmica de memória para os N elementos do vetor. V[n] é tal que Re{V[n]}=n^2
* e Im{V[n]}=sqrt(n). Gravar V[n] em disco com fwrite() no arquivo binário “v.dat” incluindo
* o número de elementos N. Ler “v.dat” do disco com fread() e gravar no arquivo texto “v.txt”.
* Ler “v.txt” do disco determinando automaticamente o número de elementos nele armazenado e comparar
* com os valores V[n] gerados originalmente. Verificar numericamente a coerência dos valores lidos
* de “v.txt” com os valores originais de V[n]. Qualquer procedimento/operação de leitura e/ou escrita
* em memória e/ou em disco deve ser parametrizável durante a execução em função do valor da variável N.
*****************************************************************************/

/*****************************************************************************
* HEADERS:
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*****************************************************************************
* DEFINIÇÃO DA STRUCT COMPLEX:
*****************************************************************************/
typedef struct Complex {
    float Re; // parte real da variável do tipo COMPLEX
    float Im; // parte imaginária da variável do tipo COMPLEX
} COMPLEX;

/*****************************************************************************
* FUNCTION PROTOTYPES:
*****************************************************************************/
void generate_complex_vector(int N, COMPLEX *Vec);
void write_complex_vector_to_binary_file(int N, COMPLEX *Vec);
void read_complex_vector_from_binary_file(int *N, COMPLEX **Vec);
void write_complex_vector_to_text_file(int N, COMPLEX *Vec);
void read_complex_vector_from_text_file(int *N, COMPLEX **Vec);

/*****************************************************************************
* main():
*****************************************************************************/
int main(void) {
    int N;
    COMPLEX *Vec;

    // Obtendo o tamanho do vetor
    printf("Digite o tamanho do vetor (N): ");
    scanf("%d", &N);

    // Alocando memória para o vetor
    Vec = (COMPLEX *)malloc(N * sizeof(COMPLEX));
    if (Vec == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // Gerando o vetor de números complexos
    generate_complex_vector(N, Vec);

    // Imprimindo o vetor antes de gravar em disco
    printf("Valores do vetor antes de gravar em disco:\n");
    for (int i = 0; i < N; i++) {
        printf("V[%d] = %.2f + %.2fi\n", i, Vec[i].Re, Vec[i].Im);
    }
    
    // Escrevendo o vetor em disco no arquivo binário "v.dat"
    write_complex_vector_to_binary_file(N, Vec);
    printf("Valores gravados em v.dat com sucesso!\n");
    
    // Lendo o vetor do arquivo binário "v.dat"
    printf("Lendo valores do arquivo binario v.dat...\n");
    read_complex_vector_from_binary_file(&N, &Vec);

    // Lendo o vetor do arquivo binário "v.dat" e gravando no arquivo texto "v.txt"
    write_complex_vector_to_text_file(N, Vec);
    printf("Valores gravados em v.txt com sucesso!\n");

    // Lendo o vetor do arquivo texto "v.txt" determinando automaticamente o número de elementos
    printf("Lendo valores do arquivo texto v.txt...\n");
    read_complex_vector_from_text_file(&N, &Vec);

    // Imprimindo o vetor depois de ler do arquivo texto "v.txt"
    printf("Valores do vetor depois de ler do arquivo texto v.txt:\n");
    for (int i = 0; i < N; i++) {
        printf("V[%d] = %.2f + %.2fi\n", i, Vec[i].Re, Vec[i].Im);
    }

    // Liberando memória alocada para o vetor
    free(Vec);

    return 0;
}

/*****************************************************************************
* FUNC: generate_complex_vector(int N, COMPLEX *Vec)
*
* DESC: Gera o vetor de números complexos conforme as especificações dadas.
*        Esta função recebe o tamanho N do vetor e um ponteiro para um vetor de números complexos.
*        Em seguida, ela preenche o vetor com números complexos calculados de acordo com as especificações fornecidas.
*        Para cada posição n no vetor, o valor da parte real é dado pelo quadrado do índice n,
*        enquanto o valor da parte imaginária é a raiz quadrada de n.
*        Ao finalizar a geração, o vetor resultante contendo números complexos é armazenado no ponteiro fornecido.
******************************************************************************/
void generate_complex_vector(int N, COMPLEX *Vec) {
    for (int n = 0; n < N; n++) {
        Vec[n].Re = pow(n, 2);
        Vec[n].Im = sqrt(n);
    }
}

/*****************************************************************************
* FUNC: write_complex_vector_to_binary_file(int N, COMPLEX *Vec)
*
* DESC: Escreve o vetor de números complexos em disco no arquivo binário "v.dat".
*        Esta função abre o arquivo "v.dat" para escrita em modo binário e escreve o número de elementos
*        do vetor no início do arquivo. Em seguida, ela escreve os elementos do vetor no arquivo.
*        Ao finalizar a escrita, o arquivo é fechado.
******************************************************************************/
void write_complex_vector_to_binary_file(int N, COMPLEX *Vec) {
    FILE *file = fopen("v.dat", "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Escrevendo o número de elementos no arquivo
    fwrite(&N, sizeof(int), 1, file);

    // Escrevendo os elementos do vetor no arquivo
    fwrite(Vec, sizeof(COMPLEX), N, file);

    fclose(file);
}

/*****************************************************************************
* FUNC: read_complex_vector_from_binary_file(int *N, COMPLEX **Vec)
*
* DESC: Lê o vetor de números complexos do arquivo binário "v.dat".
*        Esta função abre o arquivo "v.dat" para leitura em modo binário e lê o número de elementos armazenados
*        no início do arquivo. Em seguida, aloca dinamicamente a memória necessária para armazenar o vetor
*        com o tamanho especificado. Então, lê os elementos do vetor do arquivo e os armazena na memória alocada.
*        Ao finalizar a leitura, o arquivo é fechado.
******************************************************************************/
void read_complex_vector_from_binary_file(int *N, COMPLEX **Vec) {
    FILE *file = fopen("v.dat", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    // Lendo o número de elementos do arquivo
    fread(N, sizeof(int), 1, file);

    // Alocando memória para o vetor
    *Vec = (COMPLEX *)malloc((*N) * sizeof(COMPLEX));
    if (*Vec == NULL) {
        printf("Erro ao alocar memoria.\n");
        fclose(file);
        return;
    }

    // Lendo os elementos do vetor do arquivo
    fread(*Vec, sizeof(COMPLEX), *N, file);

    fclose(file);
}

/*****************************************************************************
* FUNC: write_complex_vector_to_text_file(int N, COMPLEX *Vec)
*
* DESC: Grava o vetor de números complexos no arquivo texto "v.txt".
*        Esta função abre o arquivo "v.txt" para escrita e, em seguida, escreve o número de elementos
*        do vetor no início do arquivo. Depois disso, os elementos do vetor são escritos no arquivo,
*        com cada elemento formatado como "parte_real parte_imaginaria", separados por um espaço.
*        Ao finalizar a escrita, o arquivo é fechado.
******************************************************************************/
void write_complex_vector_to_text_file(int N, COMPLEX *Vec) {
    FILE *file = fopen("v.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Escrevendo o número de elementos no arquivo texto
    fprintf(file, "%d\n", N);

    // Escrevendo o vetor no arquivo texto
    for (int n = 0; n < N; n++) {
        fprintf(file, "%.2f %.2f\n", Vec[n].Re, Vec[n].Im);
    }

    fclose(file);
}

/*****************************************************************************
* FUNC: read_complex_vector_from_text_file(int *N, COMPLEX **Vec)
*
* DESC: Lê o vetor de números complexos do arquivo texto "v.txt", determinando automaticamente o número de elementos.
*        Os elementos lidos são armazenados em um vetor alocado dinamicamente. Esta função atualiza os parâmetros
*        *N e **Vec com os valores lidos do arquivo.
******************************************************************************/
void read_complex_vector_from_text_file(int *N, COMPLEX **Vec) {
    FILE *file = fopen("v.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    // Lendo o número de elementos do arquivo texto
    fscanf(file, "%d", N);

    // Alocando memória para o vetor
    *Vec = (COMPLEX *)malloc((*N) * sizeof(COMPLEX));
    if (*Vec == NULL) {
        printf("Erro ao alocar memoria.\n");
        fclose(file);
        return;
    }

    // Lendo os elementos do vetor do arquivo texto
    for (int i = 0; i < *N; i++) {
        fscanf(file, "%f %f", &(*Vec)[i].Re, &(*Vec)[i].Im);
    }

    fclose(file);
}
