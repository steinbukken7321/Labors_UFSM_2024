% *****************************************************************************
% Trabalho 1: Gerar um vetor de N números complexos V[n]=Re{V[n]}+jIm{V[n]}, n=0,1...N-1, usando alocação
% dinâmica de memória para os N elementos do vetor. V[n] é tal que Re{V[n]}=n^2 e Im{V[n]}=sqrt(n). 
% Gravar V[n] em disco com fwrite() no arquivo binário "v.dat" incluindo o número de elementos N. 
% Ler "v.dat" do disco com fread() e gravar no arquivo texto “v.txt”. 
% Ler "v.txt" do disco determinando automaticamente o número de elementos nele armazenado
% e compare com os valores V[n] gerados originalmente. Verifique numericamente a
% coerência dos valores lidos de "v.txt" com os valores originais de V[n]. Qualquer procedimento/operação de
% leitura e/ou escrita em memória e/ou em disco deve ser parametrizável durante a execução em função do valor
% da variável N.
% *****************************************************************************/


clc;
clear;
close all;


% MAIN SCRIPT
% Solicita ao usuário o tamanho do vetor
N = input('Digite o tamanho do vetor (N): ');
% Gera o vetor de números complexos
Vec = generate_complex_vector(N);
% Exibe os valores do vetor antes de gravar em disco
disp('Valores do vetor antes de gravar em disco:');
for i = 1:N
    % Imprime os valores do vetor formatados
    fprintf('V[%d] = %.2f + %.2fi\n', i-1, real(Vec(i)), imag(Vec(i)));
end
% Grava o vetor em um arquivo binário
write_complex_vector_to_binary_file(Vec);
% Exibe mensagem indicando que os valores foram gravados com sucesso
disp('Valores gravados em v.dat com sucesso!');
% Lê o vetor do arquivo binário
Vec = read_complex_vector_from_binary_file();
% Exibe mensagem indicando que os valores estão sendo lidos do arquivo binário
disp('Lendo valores do arquivo binario v.dat...');
% Grava o vetor em um arquivo de texto
write_complex_vector_to_text_file(Vec);
% Exibe mensagem indicando que os valores foram gravados com sucesso no arquivo de texto
disp('Valores gravados em v.txt com sucesso!');
% Lê o vetor do arquivo de texto
Vec = read_complex_vector_from_text_file();
% Exibe mensagem indicando que os valores estão sendo lidos do arquivo de texto
disp('Lendo valores do arquivo texto v.txt...');
% Exibe os valores do vetor após a leitura do arquivo de texto
disp('Valores do vetor depois de ler do arquivo texto v.txt:');
for i = 1:N
    % Imprime os valores do vetor formatados
    fprintf('V[%d] = %.2f + %.2fi\n', i-1, real(Vec(i)), imag(Vec(i)));
end

% FUNCTION: generate_complex_vector(N)
%
% DESC: Gera o vetor de números complexos conforme as especificações dadas.
%       Esta função recebe o tamanho N do vetor e retorna o vetor de números complexos gerado.
%       Para cada posição n no vetor, o valor da parte real é dado pelo quadrado do índice n,
%       enquanto o valor da parte imaginária é a raiz quadrada de n, multiplicada por 'i'.
function Vec = generate_complex_vector(N)
    Vec = zeros(1, N);
    for n = 1:N
        real_part = (n-1)^2; % Adjust index to start from 0
        imaginary_part = sqrt(n-1); % Adjust index to start from 0
        Vec(n) = real_part + imaginary_part * 1i;
    end
end

% FUNCTION: write_complex_vector_to_binary_file(Vec)
%
% DESC: Escreve o vetor de números complexos em disco no arquivo binário "v.dat".
%       Esta função recebe o vetor de números complexos e escreve-os em um arquivo binário.
function write_complex_vector_to_binary_file(Vec)
    N = length(Vec);
    fileID = fopen('v.dat', 'wb');
    fwrite(fileID, N, 'int');
    fwrite(fileID, real(Vec), 'double');
    fwrite(fileID, imag(Vec), 'double');
    fclose(fileID);
end

% FUNCTION: read_complex_vector_from_binary_file()
%
% DESC: Lê o vetor de números complexos do arquivo binário "v.dat".
%       Esta função lê os números complexos armazenados em um arquivo binário e retorna o vetor.
function Vec = read_complex_vector_from_binary_file()
    fileID = fopen('v.dat', 'rb');
    N = fread(fileID, 1, 'int');
    realPart = fread(fileID, N, 'double');
    imagPart = fread(fileID, N, 'double');
    Vec = realPart + 1i * imagPart;
    fclose(fileID);
end

% FUNCTION: write_complex_vector_to_text_file(Vec)
%
% DESC: Grava o vetor de números complexos no arquivo texto "v.txt".
%       Esta função recebe o vetor de números complexos e escreve-os em um arquivo de texto.
function write_complex_vector_to_text_file(Vec)
    N = length(Vec);
    fileID = fopen('v.txt', 'w');
    fprintf(fileID, '%d\n', N);
    for n = 1:N
        fprintf(fileID, '%.2f %.2f\n', real(Vec(n)), imag(Vec(n)));
    end
    fclose(fileID);
end

% FUNCTION: read_complex_vector_from_text_file()
%
% DESC: Lê o vetor de números complexos do arquivo texto "v.txt".
%       Esta função lê os números complexos armazenados em um arquivo texto e retorna o vetor.
function Vec = read_complex_vector_from_text_file()
    fileID = fopen('v.txt', 'r');
    N = fscanf(fileID, '%d', 1);
    Vec = zeros(1, N);
    for n = 1:N
        C = fscanf(fileID, '%f', 2);
        Vec(n) = C(1) + 1i * C(2);
    end
    fclose(fileID);
end
