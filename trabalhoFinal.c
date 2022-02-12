#include <stdio.h>
#define LINHAS 8
#define COLUNAS 24

typedef struct
{
    char nome[20];
    int atk;
    int vida;
    char tipo;

} Algomon;

typedef struct
{
    char simbolo;
    int x;
    int y;
    int insignias;
    Algomon algodex[15];

} Jogador;

typedef struct
{
    char simbolo;
    int x;
    int y;
    Algomon algomon;

} Cidade;

typedef struct
{
    char simbolo;
    int x;
    int y;
    Algomon superAlgomon;
} Treinador;

Algomon criaAlgomon(char nome[], int atk, int vida, char tipo)
{
    Algomon algomon;
    int i = 0;
    for (i = 0; i != '\0'; i++)
    {
        algomon.nome[i] = nome[i];
    }
    algomon.atk = atk;
    algomon.vida = vida;
    algomon.tipo = tipo;

    return algomon;
}

Cidade criaCidade(char simbolo, int x, int y, Algomon algomon)
{
    Cidade cidade;
    cidade.simbolo = simbolo;
    cidade.x = x;
    cidade.y = y;
    cidade.algomon = algomon;
}

Treinador criaTreinador(char simbolo, int x, int y, Algomon algomon)
{
    Treinador treinador;
    treinador.simbolo = simbolo;
    treinador.x = x;
    treinador.y = y;
    treinador.superAlgomon = algomon;
    treinador.superAlgomon.vida = treinador.superAlgomon.vida + 20;
}

int main()
{

    Algomon algumonsDisponiveis[18];
    algumonsDisponiveis[0] = criaAlgomon("Ifssauro", 5, 20, 'C');
    algumonsDisponiveis[1] = criaAlgomon("Whiledle", 3, 40, 'R');
    algumonsDisponiveis[2] = criaAlgomon("Vectoray", 4, 30, 'D');
    algumonsDisponiveis[3] = criaAlgomon("a", 5, 18, 'C');
    algumonsDisponiveis[4] = criaAlgomon("b", 3, 36, 'R');
    algumonsDisponiveis[5] = criaAlgomon("c", 2, 50, 'D');
    algumonsDisponiveis[6] = criaAlgomon("d", 5, 22, 'C');
    algumonsDisponiveis[7] = criaAlgomon("e", 3, 40, 'R');
    algumonsDisponiveis[8] = criaAlgomon("f", 4, 32, 'D');
    algumonsDisponiveis[9] = criaAlgomon("g", 7, 15, 'C');
    algumonsDisponiveis[10] = criaAlgomon("h", 4, 25, 'R');
    algumonsDisponiveis[11] = criaAlgomon("i", 5, 30, 'D');
    algumonsDisponiveis[12] = criaAlgomon("j", 6, 42, 'C');
    algumonsDisponiveis[13] = criaAlgomon("k", 3, 30, 'R');
    algumonsDisponiveis[14] = criaAlgomon("l", 3, 28, 'D');
    algumonsDisponiveis[15] = criaAlgomon("m", 2, 38, 'C');
    algumonsDisponiveis[16] = criaAlgomon("n", 6, 26, 'R');
    algumonsDisponiveis[17] = criaAlgomon("Ceepluplus", 8, 50, 'L');

    Cidade cidadesExistentes[12];
    cidadesExistentes[0] = criaCidade('#', 6, 0, algumonsDisponiveis[3]);
    cidadesExistentes[1] = criaCidade('#', 12, 1, algumonsDisponiveis[4]);
    cidadesExistentes[2] = criaCidade('#', 18, 1, algumonsDisponiveis[5]);
    cidadesExistentes[3] = criaCidade('#', 0, 3, algumonsDisponiveis[6]);
    cidadesExistentes[4] = criaCidade('#', 6, 3, algumonsDisponiveis[7]);
    cidadesExistentes[5] = criaCidade('#', 12, 3, algumonsDisponiveis[8]);
    cidadesExistentes[6] = criaCidade('#', 18, 3, algumonsDisponiveis[9]);
    cidadesExistentes[7] = criaCidade('#', 10, 5, algumonsDisponiveis[10]);
    cidadesExistentes[8] = criaCidade('#', 22, 5, algumonsDisponiveis[11]);
    cidadesExistentes[9] = criaCidade('#', 6, 7, algumonsDisponiveis[12]);
    cidadesExistentes[10] = criaCidade('#', 10, 7, algumonsDisponiveis[13]);
    cidadesExistentes[11] = criaCidade('#', 16, 7, algumonsDisponiveis[14]);

    Treinador treinadoresExistentes[4];
    treinadoresExistentes[0] = criaTreinador('Z', 0, 0, algumonsDisponiveis[17]);
    treinadoresExistentes[1] = criaTreinador('X', 22, 3, algumonsDisponiveis[16]);
    treinadoresExistentes[2] = criaTreinador('Y', 0, 7, algumonsDisponiveis[15]);
    treinadoresExistentes[3] = criaTreinador('R', 22, 7, algumonsDisponiveis[14]);

    Jogador jogador1;
    jogador1.simbolo = 'A';
    jogador1.x = 6;
    jogador1.y = 3;
    jogador1.algodex[0] = algumonsDisponiveis[0];
    jogador1.algodex[1] = algumonsDisponiveis[1];
    jogador1.algodex[2] = algumonsDisponiveis[2];

    return 0;
}