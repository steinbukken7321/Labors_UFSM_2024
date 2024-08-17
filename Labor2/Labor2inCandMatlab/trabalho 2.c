/*****************************************************************************
* Trabalho 2: Trabalho 2: Gerar uma matriz de MxN números complexos Mat[m][n]=Re{Mat[m][n]}+jIm{Mat[m][n]},
m=0,1...M-1, n=0,1...N-1, usando alocação dinâmica de memória para os MxN elementos da matriz. Mat[m][n]
é tal que Re{Mat[m][n]}=(m+n)^2 e Im{Mat[m][n]}=sqrt(m+n).
Gravar Mat[m][n] em disco com fwrite() no arquivo binário “Mat.dat” incluindo o número de linhas M e de colunas N.
Ler “Mat.dat” do disco com fread() e gravar no arquivo texto “Mat.txt”. 
Ler “Mat.txt” do disco determinando automaticamente o seu número de linhas e colunas
e compare com os valores Mat[m][n] gerados originalmente. Verifique numericamente a
coerência dos valores lidos de “Mat.txt” com os valores originais de Mat[m][n]. Qualquer
procedimento/operação de leitura e/ou escrita em memória e/ou em disco deve ser parametrizável durante a
execução em função dos valores das variáveis M e N
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
    float Re; // parte real
    float Im; // parte imaginária
} COMPLEX;

/*****************************************************************************
* FUNCTION PROTOTYPES:
*****************************************************************************/
void generate_complex_matrix(int M, int N, COMPLEX **Mat);
void write_complex_matrix_to_file(int M, int N, COMPLEX **Mat);
void read_complex_matrix_from_file(int *M, int *N, COMPLEX ***Mat);
void write_complex_matrix_to_text_file(int M, int N, COMPLEX **Mat);
void read_complex_matrix_from_text_file(int *M, int *N, COMPLEX ***Mat);

/*****************************************************************************
* main():
*****************************************************************************/
int main(void){
    int M, N;
    COMPLEX **Mat;

    // Obtendo as dimensões da matriz
    printf("Digite o numero de linhas (M): ");
    scanf("%d", &M);
    printf("Digite o numero de colunas (N): ");
    scanf("%d", &N);

    // Alocando memória para a matriz
    Mat = (COMPLEX **)malloc(M * sizeof(COMPLEX *));
    if (Mat == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }
    for (int i = 0; i < M; i++) {
        Mat[i] = (COMPLEX *)malloc(N * sizeof(COMPLEX));
        if (Mat[i] == NULL) {
            printf("Erro ao alocar memoria.\n");
            return 1;
        }
    }

    // Gerando a matriz de números complexos
    generate_complex_matrix(M, N, Mat);
    printf("Matriz gerada:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%.2f + %.2fi\t", Mat[i][j].Re, Mat[i][j].Im);
        }
        printf("\n");
    }

    // Escrevendo a matriz em disco no arquivo binário "Mat.dat"
    write_complex_matrix_to_file(M, N, Mat);
    printf("Matriz gravada no arquivo 'Mat.dat'.\n");

    // Lendo a matriz do arquivo binário "Mat.dat" e gravando no arquivo texto "Mat.txt"
    read_complex_matrix_from_file(&M, &N, &Mat);
    write_complex_matrix_to_text_file(M, N, Mat);
    printf("Matriz gravada no arquivo 'Mat.txt'.\n");

    // Lendo a matriz do arquivo texto "Mat.txt" determinando automaticamente o número de linhas e colunas
    read_complex_matrix_from_text_file(&M, &N, &Mat);
    printf("Matriz lida do arquivo 'Mat.txt':\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%.2f + %.2fi\t", Mat[i][j].Re, Mat[i][j].Im);
        }
        printf("\n");
    }

    // Liberando memória alocada para a matriz
    for (int i = 0; i < M; i++) {
        free(Mat[i]);
    }
    free(Mat);

    return 0;
}


/*****************************************************************************
* FUNC: generate_complex_matrix(int M, int N, COMPLEX **Mat)
*
* DESC: Gera a matriz de números complexos conforme as especificações dadas.
******************************************************************************/
void generate_complex_matrix(int M, int N, COMPLEX **Mat) {
    for (int m = 0; m < M; m++) {
        for (int n = 0; n < N; n++) {
            float real_part = pow((m + n), 2);
            float imaginary_part = sqrt(m + n);
            Mat[m][n].Re = real_part;
            Mat[m][n].Im = imaginary_part;
        }
    }
}


/*****************************************************************************
* FUNC: write_complex_matrix_to_file(int M, int N, COMPLEX **Mat)
*
* DESC: Escreve a matriz de números complexos em disco no arquivo binário "Mat.dat".
******************************************************************************/
void write_complex_matrix_to_file(int M, int N, COMPLEX **Mat) {
    FILE *file = fopen("Mat.dat", "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Escrevendo o número de linhas e colunas no arquivo
    fwrite(&M, sizeof(int), 1, file);
    fwrite(&N, sizeof(int), 1, file);

    // Escrevendo os elementos da matriz no arquivo
    for (int m = 0; m < M; m++) {
        fwrite(Mat[m], sizeof(COMPLEX), N, file);
    }

    fclose(file);
}


/*****************************************************************************
* FUNC: read_complex_matrix_from_file(int *M, int *N, COMPLEX ***Mat)
*
* DESC: Lê a matriz de números complexos do arquivo binário "Mat.dat".
******************************************************************************/
void read_complex_matrix_from_file(int *M, int *N, COMPLEX ***Mat) {
    FILE *file = fopen("Mat.dat", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    // Lendo o número de linhas e colunas do arquivo
    fread(M, sizeof(int), 1, file);
    fread(N, sizeof(int), 1, file);

    // Alocando memória para a matriz
    *Mat = (COMPLEX **)malloc(*M * sizeof(COMPLEX *));
    if (*Mat == NULL) {
        printf("Erro ao alocar memoria.\n");
        return;
    }
    for (int i = 0; i < *M; i++) {
        (*Mat)[i] = (COMPLEX *)malloc(*N * sizeof(COMPLEX));
        if ((*Mat)[i] == NULL) {
            printf("Erro ao alocar memoria.\n");
            return;
        }
    }

    // Lendo os elementos da matriz do arquivo
    for (int m = 0; m < *M; m++) {
        fread((*Mat)[m], sizeof(COMPLEX), *N, file);
    }

    fclose(file);
}


/*****************************************************************************
* FUNC: write_complex_matrix_to_text_file(int M, int N, COMPLEX **Mat)
*
* DESC: Grava a matriz de números complexos no arquivo texto "Mat.txt". 
******************************************************************************/
void write_complex_matrix_to_text_file(int M, int N, COMPLEX **Mat) {
    FILE *file = fopen("Mat.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Escrevendo o número de linhas e colunas no arquivo texto
    fprintf(file, "%d %d\n", M, N);

    // Escrevendo a matriz no arquivo texto
    for (int m = 0; m < M; m++) {
        for (int n = 0; n < N; n++) {
            fprintf(file, "%.2f + %.2fi\t", Mat[m][n].Re, Mat[m][n].Im);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}


/*****************************************************************************
* FUNC: read_complex_matrix_from_text_file(int *M, int *N, COMPLEX ***Mat)
*
* DESC: Lê a matriz de números complexos do arquivo texto "Mat.txt", 
*       determinando automaticamente o número de linhas e colunas. 
******************************************************************************/
void read_complex_matrix_from_text_file(int *M, int *N, COMPLEX ***Mat) {
    FILE *file = fopen("Mat.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    // Lendo o número de linhas e colunas do arquivo texto
    fscanf(file, "%d %d", M, N);

    // Alocando memória para a matriz
    *Mat = (COMPLEX **)malloc(*M * sizeof(COMPLEX *));
    if (*Mat == NULL) {
        printf("Erro ao alocar memoria.\n");
        return;
    }
    for (int i = 0; i < *M; i++) {
        (*Mat)[i] = (COMPLEX *)malloc(*N * sizeof(COMPLEX));
        if ((*Mat)[i] == NULL) {
            printf("Erro ao alocar memoria.\n");
            return;
        }
    }

    // Lendo os elementos da matriz do arquivo texto
    for (int m = 0; m < *M; m++) {
        for (int n = 0; n < *N; n++) {
            fscanf(file, "%f + %fi", &(*Mat)[m][n].Re, &(*Mat)[m][n].Im);
        }
    }

    fclose(file);
}