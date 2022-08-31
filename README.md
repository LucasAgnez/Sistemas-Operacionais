# Sistemas Operacionais
Repositório para o a disciplina de Sistemas Operacionais ministrada por Gustavo Girao

## Modo de uso:
compilação:
    g++ -o createMat createMat.cpp
    g++ -o seqMat seqMat.cpp
    

uso:   
    ` ./createMat <R1> <C1> <R2> <C2> `
    ` ./seqMat <arquivo1> <arquivo2> `

### Os arquivos gerados e que podem ser lidos são os encontrados no diretório "resources/basic_matrixes". não é necessário colocar o caminho do arquivo nem a extensão para ler

## Descrição:
  O objetivo deste trabalho é comparar o tempo de execução do mesmo problema implementado de forma Sequencial, Paralelo com Thread e Paralelo com Processos