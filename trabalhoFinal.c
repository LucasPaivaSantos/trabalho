#include <stdio.h>
#include <string.h>
#define LINHAS 8
#define COLUNAS 24
#define NUMTREINADORES 4
#define NUMCIDADES 16
#define TAMALGODEX 15

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
    int numAlgomons;
    Algomon algodex[TAMALGODEX];

} Jogador;

typedef struct
{
    char simbolo;
    int x;
    int y;
    Algomon superAlgomon;
} Treinador;

typedef struct
{
    char simbolo;
    int x;
    int y;
    Algomon algomon;
    Treinador treinador;

} Cidade;

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

Cidade criaCidade(int x, int y, Algomon algomon)
{
    Cidade cidade;
    cidade.simbolo = '#';
    cidade.x = x;
    cidade.y = y;
    cidade.algomon = algomon;
}

Cidade criaCidadeComTreinador(int x, int y, Algomon algomon, Treinador treinador)
{
    Cidade cidade = criaCidade(x, y, algomon);
    cidade.treinador = treinador;
    return cidade;
}

Treinador criaTreinador(char simbolo, Algomon algomon)
{
    Treinador treinador;
    treinador.simbolo = simbolo;
    treinador.superAlgomon = algomon;
    treinador.superAlgomon.vida = treinador.superAlgomon.vida + 20;
}

Jogador capturaAlgomon(Jogador jogador, Cidade cidade)
{
    if (jogador.numAlgomons < TAMALGODEX)
    {
        jogador.algodex[jogador.numAlgomons] = cidade.algomon;
        jogador.numAlgomons++;
    }
    return jogador;
}

int possuiTodasAsInsignas(Jogador jogador)
{
    if (jogador.insignias == NUMTREINADORES)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int todosAlgomonsMortos(Jogador jogador)
{
    int i = 0;
    int contVivos = 0;
    for (i = 0; i < jogador.numAlgomons; i++)
    {
        if (jogador.algodex[i].vida > 0)
        {
            contVivos++;
        }
    }
    if (contVivos == 0)
    {
        return 1;
    }

    return 0;
}

void exibeMapa(char mapa[LINHAS][COLUNAS], Jogador jogador)
{
    int y, x = 0;
    for (y = 0; y < LINHAS; y++)
    {
        for (x = 0; mapa[y][x] != '\0'; x++)
        {
            if (jogador.y == y && jogador.x == x)
            {
                printf("%c", jogador.simbolo);
            }
            else
            {
                printf("%c", mapa[y][x]);
            }
        }
        printf("\n");
    }
}

/*int podeMoverPara(char mapa[LINHAS][COLUNAS], int y, int x)
{
    char permitidos[4 + 1] = "|-+#";
    int i;
    for (i = 0; permitidos[i] != '\0'; i++)
    {
        if (mapa[y][x] == permitidos[i])
        {
            return 1;
        }
    }
    return 0;
}*/

Cidade localizaCidade(Cidade cidadesExistentes[], int x, int y)
{
    int i = 0;
    for (i = 0; i < NUMCIDADES; i++)
    {
        if (cidadesExistentes[i].x == x && cidadesExistentes[i].y == y)
        {
            return cidadesExistentes[i];
        }
    }
}

Jogador moverParaONorte(char mapa[LINHAS][COLUNAS], Cidade cidadesExistentes[], Jogador jogador)
{
    int y = jogador.y - 1;
    int x = jogador.x;
    Cidade cidade = localizaCidade(cidadesExistentes, x, y);
    while (y >= 0 && mapa[y][x] != ' ')
    {
        if (mapa[y][x] == '|')
        {
            y--;
        }
        else if (mapa[y][x] == '#')
        {
            jogador.y = y;
            jogador = capturaAlgomon(jogador, cidade);
            break;
        }
        else if (mapa[y][x] == '+')
        {
            jogador.y = y;
            break;
        }
        else
        {
            // TODO batalhar e pegar pokemon
            jogador.y = y;
            break;
        }
    }
    return jogador;
}

Jogador moverParaOSul(char mapa[LINHAS][COLUNAS], Cidade cidadesExistentes[], Jogador jogador)
{
    int y = jogador.y + 1;
    int x = jogador.x;
    Cidade cidade = localizaCidade(cidadesExistentes, x, y);
    while (y < 8 && mapa[y][x] != ' ')
    {
        if (mapa[y][x] == '|')
        {
            y++;
        }
        else if (mapa[y][x] == '#')
        {
            jogador.y = y;
            jogador = capturaAlgomon(jogador, cidade);
            break;
        }
        else if (mapa[y][x] == '+')
        {
            jogador.y = y;
            break;
        }
        else
        {
            // TODO batalhar e pegar pokemon
            jogador.y = y;
            break;
        }
    }
    return jogador;
}

Jogador moverParaOOeste(char mapa[LINHAS][COLUNAS], Cidade cidadesExistentes[], Jogador jogador)
{
    int y = jogador.y;
    int x = jogador.x - 1;
    Cidade cidade = localizaCidade(cidadesExistentes, x, y);
    while (x >= 0 && mapa[y][x] != ' ')
    {
        if (mapa[y][x] == '-')
        {
            x--;
        }
        else if (mapa[y][x] == '#')
        {
            jogador.x = x;
            jogador = capturaAlgomon(jogador, cidade);
            break;
        }
        else if (mapa[y][x] == '+')
        {
            jogador.x = x;
            break;
        }
        else
        {
            // TODO batalhar e pegar pokemon
            jogador.x = x;
            break;
        }
    }
    return jogador;
}

Jogador moverParaOLeste(char mapa[LINHAS][COLUNAS], Cidade cidadesExistentes[], Jogador jogador)
{
    int y = jogador.y;
    int x = jogador.x + 1;
    Cidade cidade = localizaCidade(cidadesExistentes, x, y);
    while (x < 23 && mapa[y][x] != ' ')
    {
        if (mapa[y][x] == '-')
        {
            x++;
        }
        else if (mapa[y][x] == '#')
        {
            jogador.x = x;
            jogador = capturaAlgomon(jogador, cidade);
            break;
        }
        else if (mapa[y][x] == '+')
        {
            jogador.x = x;
            break;
        }
        else
        {
            // TODO batalhar e pegar pokemon
            jogador.x = x;
            break;
        }
    }
    return jogador;
}

Jogador leAcao(char mapa[LINHAS][COLUNAS], Cidade cidadesExistentes[], Jogador jogador)
{
    int y, x = 0;

    char direcao;
    printf("Qual seu movimento (wasdrf)?");
    scanf("%c", &direcao);
    {
        switch (direcao)
        {
        case 'w':
            jogador = moverParaONorte(mapa, cidadesExistentes, jogador);

            break;
        case 's':
            jogador = moverParaOSul(mapa, cidadesExistentes, jogador);

            break;
        case 'a':
            jogador = moverParaOOeste(mapa, cidadesExistentes, jogador);

            break;
        case 'd':
            jogador = moverParaOLeste(mapa, cidadesExistentes, jogador);

            break;
        default:
            break;
        }
    };
    scanf("%*c");
    return jogador;
}

/*Jogador rolaAlgodexParaCima(Jogador jogador)
{
    int i, idxFinal = 0;
    Algomon algomonAux;
    idxFinal = strlen(jogador.algodex);
    for (i = 0; i < idxFinal; i++)
    {
        jogador.algodex[i] = algomonAux;
        jogador.algodex[i] = jogador.algodex[i + 1];
        jogador.algodex[idxFinal] = algomonAux;
    }
    return jogador;
}*/

/*void exibeMenu(Jogador jogador)
{
    printf("Algodex (%d/15) Algomons: %d Insignias: %d \n", jogador.numAlgomons, jogador.numAlgomons, jogador.insignias);
    printf("%s                Atk: %d HP: %d Type: %c\n", jogador.algodex[0].nome, jogador.algodex[0].atk, jogador.algodex[0].vida, jogador.algodex[0].tipo);
    printf("%s                Atk: %d HP: %d Type: %c\n", jogador.algodex[1].nome, jogador.algodex[1].atk, jogador.algodex[1].vida, jogador.algodex[1].tipo);
    printf("%s                Atk: %d HP: %d Type: %c\n", jogador.algodex[2].nome, jogador.algodex[2].atk, jogador.algodex[2].vida, jogador.algodex[2].tipo);
}*/

int main()
{

    Algomon algumonsDisponiveis[18];
    algumonsDisponiveis[0] = criaAlgomon("Ifssauro", 5, 20, 'C');
    algumonsDisponiveis[1] = criaAlgomon("Whiledle", 3, 40, 'R');
    algumonsDisponiveis[2] = criaAlgomon("Vectoray", 4, 30, 'D');
    algumonsDisponiveis[3] = criaAlgomon("Stringle", 5, 18, 'C');
    algumonsDisponiveis[4] = criaAlgomon("Structurer", 3, 36, 'R');
    algumonsDisponiveis[5] = criaAlgomon("Arrayzard", 2, 50, 'D');
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

    Treinador treinadoresExistentes[NUMTREINADORES];
    treinadoresExistentes[0] = criaTreinador('Z', algumonsDisponiveis[17]);
    treinadoresExistentes[1] = criaTreinador('X', algumonsDisponiveis[16]);
    treinadoresExistentes[2] = criaTreinador('Y', algumonsDisponiveis[15]);
    treinadoresExistentes[3] = criaTreinador('R', algumonsDisponiveis[14]);

    Cidade cidadesExistentes[NUMCIDADES];
    cidadesExistentes[0] = criaCidade(6, 0, algumonsDisponiveis[3]);
    cidadesExistentes[1] = criaCidade(12, 1, algumonsDisponiveis[4]);
    cidadesExistentes[2] = criaCidade(18, 1, algumonsDisponiveis[5]);
    cidadesExistentes[3] = criaCidade(0, 3, algumonsDisponiveis[6]);
    cidadesExistentes[4] = criaCidade(6, 3, algumonsDisponiveis[7]);
    cidadesExistentes[5] = criaCidade(12, 3, algumonsDisponiveis[8]);
    cidadesExistentes[6] = criaCidade(18, 3, algumonsDisponiveis[9]);
    cidadesExistentes[7] = criaCidade(10, 5, algumonsDisponiveis[10]);
    cidadesExistentes[8] = criaCidade(22, 5, algumonsDisponiveis[11]);
    cidadesExistentes[9] = criaCidade(6, 7, algumonsDisponiveis[12]);
    cidadesExistentes[10] = criaCidade(10, 7, algumonsDisponiveis[13]);
    cidadesExistentes[11] = criaCidade(16, 7, algumonsDisponiveis[14]);
    cidadesExistentes[12] = criaCidadeComTreinador(0, 0, algumonsDisponiveis[17], treinadoresExistentes[0]);
    cidadesExistentes[13] = criaCidadeComTreinador(22, 3, algumonsDisponiveis[16], treinadoresExistentes[1]);
    cidadesExistentes[14] = criaCidadeComTreinador(0, 7, algumonsDisponiveis[15], treinadoresExistentes[2]);
    cidadesExistentes[15] = criaCidadeComTreinador(22, 7, algumonsDisponiveis[14], treinadoresExistentes[3]);

    Jogador jogador1;
    jogador1.simbolo = 'A';
    jogador1.x = 6;
    jogador1.y = 3;
    jogador1.numAlgomons = 3;
    jogador1.algodex[0] = algumonsDisponiveis[0];
    jogador1.algodex[1] = algumonsDisponiveis[1];
    jogador1.algodex[2] = algumonsDisponiveis[2];

    char mapa[LINHAS][COLUNAS] = {
        {"Z     #                "},
        {"|     |     #-----#    "},
        {"|     |     |     |    "},
        {"#-----+-----#-----#---X"},
        {"      |               |"},
        {"      |   #-----------#"},
        {"      |   |            "},
        {"Y-----#---#-----#-----R"}};

    while (!todosAlgomonsMortos(jogador1) && !possuiTodasAsInsignas(jogador1))
    {
        printf("\n");
        exibeMapa(mapa, jogador1);
        jogador1 = leAcao(mapa, cidadesExistentes, jogador1);
        printf("%d", jogador1.numAlgomons);
    }

    return 0;
}