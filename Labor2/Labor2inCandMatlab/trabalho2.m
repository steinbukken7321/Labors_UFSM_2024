% *****************************************************************************
% Trabalho 2: Trabalho 2: Gerar uma matriz de MxN números complexos Mat[m][n]=Re{Mat[m][n]}+jIm{Mat[m][n]},
% m=0,1...M-1, n=0,1...N-1, usando alocação dinâmica de memória para os MxN elementos da matriz. Mat[m][n]
% é tal que Re{Mat[m][n]}=(m+n)^2 e Im{Mat[m][n]}=sqrt(m+n).
% Gravar Mat[m][n] em disco com fwrite() no arquivo binário "Mat.dat" incluindo o número de linhas M e de colunas N.
% Ler "Mat.dat" do disco com fread() e gravar no arquivo texto “Mat.txt”. 
% Ler "Mat.txt" do disco determinando automaticamente o seu número de linhas e colunas
% e compare com os valores Mat[m][n] gerados originalmente. Verifique numericamente a
% coerência dos valores lidos de "Mat.txt" com os valores originais de Mat[m][n]. Qualquer
% procedimento/operação de leitura e/ou escrita em memória e/ou em disco deve ser parametrizável durante a
% execução em função dos valores das variáveis M e N
% *****************************************************************************/

clc;
clear;
close all;

% MAIN SCRIPT
% Obtendo as dimensões da matriz
M = input('Digite o numero de linhas (M): ');
N = input('Digite o numero de colunas (N): ');
% Gerando a matriz de números complexos
Mat = generate_complex_matrix(M, N);
disp('Matriz gerada:');
disp_complex_matrix(Mat);
% Escrevendo a matriz em disco no arquivo binário "Mat.dat"
write_complex_matrix_to_file(M, N, Mat);
disp('Matriz gravada no arquivo ''Mat.dat''.');
% Mensagem de impressão após escrever em "Mat.dat"
disp('Lendo a matriz do arquivo ''Mat.dat''...');
% Lendo a matriz do arquivo binário "Mat.dat" e gravando no arquivo texto "Mat.txt"
write_complex_matrix_to_text_file(M, N, Mat);
disp('Matriz gravada no arquivo ''Mat.txt''.');
% Mensagem de impressão após escrever em "Mat.txt"
disp('Lendo a matriz do arquivo ''Mat.txt''...');
% Lendo a matriz do arquivo texto "Mat.txt" determinando automaticamente o número de linhas e colunas
[M, N, Mat] = read_complex_matrix_from_text_file();
disp('Matriz lida do arquivo ''Mat.txt'':');
disp_complex_matrix(Mat);

% FUNC: generate_complex_matrix(M, N)
%
% DESC: Gera a matriz de números complexos conforme.
%
function Mat = generate_complex_matrix(M, N)
    Mat = zeros(M, N);
    for m = 1:M
        for n = 1:N
            real_part = (m - 1 + n - 1) ^ 2;
            imaginary_part = sqrt(m - 1 + n - 1);
            Mat(m, n) = complex(real_part, imaginary_part);
        end
    end
end

% FUNC: write_complex_matrix_to_file(M, N, Mat)
%
% DESC: Escreve a matriz de números complexos em disco no arquivo binário "Mat.dat".
%
function write_complex_matrix_to_file(M, N, Mat)
    file = fopen('Mat.dat', 'wb');
    if file == -1
        fprintf('Erro ao abrir o arquivo para escrita.\n');
        return;
    end

    % Escrevendo o número de linhas e colunas no arquivo
    fwrite(file, M, 'int');
    fwrite(file, N, 'int');

    % Escrevendo os elementos da matriz no arquivo
    fwrite(file, real(Mat), 'double');
    fwrite(file, imag(Mat), 'double');

    fclose(file);
end

% FUNC: write_complex_matrix_to_text_file(M, N, Mat)
%
% DESC: Grava a matriz de números complexos no arquivo texto "Mat.txt".
%
function write_complex_matrix_to_text_file(M, N, Mat)
    file = fopen('Mat.txt', 'w');
    if file == -1
        fprintf('Erro ao abrir o arquivo para escrita.\n');
        return;
    end

    % Escrevendo o número de linhas e colunas no arquivo texto
    fprintf(file, '%d %d\n', M, N);

    % Escrevendo a matriz no arquivo texto
    for m = 1:M
        for n = 1:N
            fprintf(file, '%.2f + %.2fi\t', real(Mat(m, n)), imag(Mat(m, n)));
        end
        fprintf(file, '\n');
    end

    fclose(file);
end

% FUNC: read_complex_matrix_from_text_file()
%
% DESC: Lê a matriz de números complexos do arquivo texto "Mat.txt",
%       determinando automaticamente o número de linhas e colunas.
%
function [M, N, Mat] = read_complex_matrix_from_text_file()
    file = fopen('Mat.txt', 'r');
    if file == -1
        fprintf('Erro ao abrir o arquivo para leitura.\n');
        return;
    end

    % Lendo o número de linhas e colunas do arquivo texto
    dims = fscanf(file, '%d %d', [1 2]);
    M = dims(1);
    N = dims(2);

    % Inicializando a matriz de números complexos
    Mat = zeros(M, N);

    % Lendo os elementos da matriz do arquivo texto
    for m = 1:M
        for n = 1:N
            real_part = fscanf(file, '%f', 1); % Lê a parte real do número complexo
            fscanf(file, '%s', 1); % Ignora o caractere de separação
            imaginary_part = fscanf(file, '%f', 1); % Lê a parte imaginária do número complexo
            fscanf(file, '%s', 1); % Ignora o caractere de separação
            Mat(m, n) = complex(real_part, imaginary_part);
        end
    end

    fclose(file);
end

% FUNC: disp_complex_matrix(Mat)
%
% DESC: Exibe a matriz de números complexos formatada com duas casas decimais após a vírgula.
%
function disp_complex_matrix(Mat)
    [M, N] = size(Mat);
    for m = 1:M
        for n = 1:N
            fprintf('%.2f + %.2fi\t', real(Mat(m, n)), imag(Mat(m, n)));
        end
        fprintf('\n');
    end
end
