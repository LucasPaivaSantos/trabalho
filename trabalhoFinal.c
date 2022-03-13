#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LINHAS 8
#define COLUNAS 24
#define NUMTREINADORES 4
#define NUMCIDADES 16
#define TAMALGODEX 18

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
    Algomon algomon;
} Treinador;

typedef struct
{
    char simbolo;
    int x;
    int y;
    Algomon algomon;
    Treinador treinador;
} Cidade;

typedef struct
{
    Jogador jogador;
    Cidade cidade;
    char mapa[LINHAS][COLUNAS];
} ResultadoBatalha;

Algomon criaAlgomon(char nome[], int atk, int vida, char tipo)
{
    Algomon algomon;
    int i = 0;

    strcpy(algomon.nome, nome);
    algomon.atk = atk;
    algomon.vida = vida;
    algomon.tipo = tipo;
    return algomon;
}

Treinador criaTreinador(char simbolo, Algomon algomon)
{
    Treinador treinador;
    treinador.simbolo = simbolo;
    treinador.algomon = algomon;
    treinador.algomon.vida = treinador.algomon.vida + 20;
    return treinador;
}

Cidade criaCidade(int x, int y, Algomon algomon)
{
    Cidade cidade;
    cidade.simbolo = '#';
    cidade.x = x;
    cidade.y = y;
    cidade.algomon = algomon;
    return cidade;
}

Cidade criaCidadeComTreinador(int x, int y, Algomon algomon, Treinador treinador)
{
    Cidade cidade = criaCidade(x, y, algomon);
    cidade.treinador = treinador;
    return cidade;
}

Jogador capturaAlgomon(Jogador jogador, Cidade cidade)
{
    if (jogador.numAlgomons < TAMALGODEX)
    {
        printf("\nVoce capturou %s!!", cidade.algomon.nome);
        jogador.algodex[jogador.numAlgomons] = cidade.algomon;
        jogador.numAlgomons++;
    }
    return jogador;
}

int possuiTodasAsInsignas(Jogador jogador)
{
    if (jogador.insignias == NUMTREINADORES)
    {
        for (int i = 0; i < 21; i++)
        {
            printf("\n");
        }

        printf("\nParabens!!!\nVoce conseguiu toda as 4 insignias e capturou cecplusplus!!\nSegundo a lenda esse algomon sinaliza uma nova etapa...");
        printf("\nDesenvolvido por Lucas Paiva dos Santos e Italo de Almeida Ribeiro");
        exit(0);
        return 1;
    }
    else
    {
        return 0;
    }
}

void fimDeJogo()
{
    for (int i = 0; i < 21; i++)
    {
        printf("\n");
    }

    printf("Todos os seus algomons estao fracos demais para prosseguir\nTente novamente reorganizando os algomons\nFim de jogo!!");
    printf("\nDesenvolvido por Lucas Paiva dos Santos e Italo de Almeida Ribeiro");
    exit(0);
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
        fimDeJogo();
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

int primeiroAlgomonVivo(Jogador jogador)
{
    int i = 0;
    for (i = 0; i < jogador.numAlgomons; i++)
    {
        if (jogador.algodex[i].vida > 0)
        {
            return i;
        }
        else
        {
            fimDeJogo();
        }
    }
}

Jogador rolaMenuParaBaixo(Jogador jogador)
{
    int indiceFinalDaAlgodex = jogador.numAlgomons - 1;
    Algomon algomonAux;
    algomonAux = jogador.algodex[0];

    for (int i = 0; i < indiceFinalDaAlgodex; i++)
    {
        jogador.algodex[i] = jogador.algodex[i + 1];
    }
    jogador.algodex[indiceFinalDaAlgodex] = algomonAux;
    return jogador;
}

Jogador rolaMenuParaCima(Jogador jogador)
{
    int indiceFinalDaAlgodex = jogador.numAlgomons - 1;
    Algomon algomonAux;
    algomonAux = jogador.algodex[indiceFinalDaAlgodex];

    for (int i = indiceFinalDaAlgodex; i > 0; i--)
    {
        jogador.algodex[i] = jogador.algodex[i - 1];
    }
    jogador.algodex[0] = algomonAux;
    return jogador;
}

ResultadoBatalha batalhar(char mapa[LINHAS][COLUNAS], Cidade cidadeAnterior, Cidade cidade, Jogador jogador)
{
    ResultadoBatalha resultado;
    int quantidadeAlgomonsMortos = 0;
    int vidaOriginalAlgomonTreinador = cidade.treinador.algomon.vida;
    int vidaSobrando = 0;
    int indiceAlgomonJogador = primeiroAlgomonVivo(jogador);
    int indiceFinalAlgodex = jogador.numAlgomons;
    Algomon algomonJogador = jogador.algodex[0];
    Algomon algomonAuxiliar = jogador.algodex[0];
    int vezDoJogador = 1;
    int turno = 1;

    while (1 == 1)
    {
        if ((jogador.x == 0) && (jogador.y == 0) && (jogador.insignias == 3)) // caso do treinador Z com as 3 insignias
        {

            if (algomonJogador.vida <= 0 && quantidadeAlgomonsMortos == 3)
            {
                cidade.treinador.algomon.vida = vidaOriginalAlgomonTreinador;
                jogador.x = cidadeAnterior.x;
                jogador.y = cidadeAnterior.y;
                printf("\nVoce foi derrotado!\nEsta de volta a cidade de onde veio.");
                break;
            }
            else if (algomonJogador.vida <= 0 && quantidadeAlgomonsMortos < 3)
            {
                printf("\n%s esta muito fraco e volta a sua algobola!", algomonJogador.nome);
                int indiceFinalAlgodex = jogador.numAlgomons - 1;
                Algomon algomonAux = jogador.algodex[0];
                for (int i = 0; i < indiceFinalAlgodex; i++)
                {
                    jogador.algodex[i] = jogador.algodex[i + 1];
                }
                jogador.algodex[indiceFinalAlgodex] = algomonAux;
                jogador.algodex[indiceFinalAlgodex].vida = 0;
                algomonJogador = jogador.algodex[quantidadeAlgomonsMortos - 1];
                quantidadeAlgomonsMortos++;
                printf("\n%s toma seu lugar e a batalha continua!", algomonJogador.nome);
            }
            else if (cidade.treinador.algomon.vida <= 0)
            {
                jogador.algodex[0].vida = vidaSobrando;
                jogador.insignias++;
                mapa[cidade.y][cidade.x] = '+';
                jogador = capturaAlgomon(jogador, cidade);
                printf("\nVoce venceu!! \nAgora voce tem %d insígnias.", jogador.insignias);
                break;
            }

            if (vezDoJogador)
            {
                if (cidade.treinador.algomon.tipo == 'C' && algomonJogador.tipo == 'R')
                {
                    cidade.treinador.algomon.vida -= algomonJogador.atk * 2;
                    printf("\nturno %d: %s atacou %s e inflingiu %d \nFoi super efetivo!!.", turno, algomonJogador.nome, cidade.treinador.algomon.nome, 2 * algomonJogador.atk);
                }
                else if (cidade.treinador.algomon.tipo == 'R' && algomonJogador.tipo == 'D')
                {
                    cidade.treinador.algomon.vida -= algomonJogador.atk * 2;
                    printf("\nturno %d: %s atacou %s e inflingiu %d \nFoi super efetivo!!.", turno, algomonJogador.nome, cidade.treinador.algomon.nome, 2 * algomonJogador.atk);
                }
                else if (cidade.treinador.algomon.tipo == 'D' && algomonJogador.tipo == 'C')
                {
                    cidade.treinador.algomon.vida -= algomonJogador.atk * 2;
                    printf("\nturno %d: %s atacou %s e inflingiu %d \nFoi super efetivo!!.", turno, algomonJogador.nome, cidade.treinador.algomon.nome, 2 * algomonJogador.atk);
                }
                else
                {
                    cidade.treinador.algomon.vida -= algomonJogador.atk;
                    printf("\nturno %d: %s atacou %s e inflingiu %d.", turno, algomonJogador.nome, cidade.treinador.algomon.nome, algomonJogador.atk);
                }
                vezDoJogador = 0;
            }

            else
            {
                if (algomonJogador.tipo == 'C' && cidade.treinador.algomon.tipo == 'R')
                {
                    algomonJogador.vida -= cidade.treinador.algomon.atk * 2;
                    printf("\nturno %d: %s atacou %s e inflingiu %d \nFoi super efetivo!!.", turno, cidade.treinador.algomon.nome, algomonJogador.nome, 2 * cidade.treinador.algomon.atk);
                }
                else if (algomonJogador.tipo == 'R' && cidade.treinador.algomon.tipo == 'D')
                {
                    algomonJogador.vida -= cidade.treinador.algomon.atk * 2;
                    printf("\nturno %d: %s atacou %s e inflingiu %d \nFoi super efetivo!!.", turno, cidade.treinador.algomon.nome, algomonJogador.nome, 2 * cidade.treinador.algomon.atk);
                }
                else if (algomonJogador.tipo == 'D' && cidade.treinador.algomon.tipo == 'C')
                {
                    algomonJogador.vida -= cidade.treinador.algomon.atk * 2;
                    printf("\nturno %d: %s atacou %s e inflingiu %d \nFoi super efetivo!!.", turno, cidade.treinador.algomon.nome, algomonJogador.nome, 2 * cidade.treinador.algomon.atk);
                }
                else
                {
                    algomonJogador.vida -= cidade.treinador.algomon.atk;
                    printf("\nturno %d: %s atacou %s e inflingiu %d.", turno, cidade.treinador.algomon.nome, algomonJogador.nome, cidade.treinador.algomon.atk);
                }
                vidaSobrando = algomonJogador.vida;
                vezDoJogador = 1;
            }
        }
        else if ((jogador.x == 0) && (jogador.y == 0) && (jogador.insignias < 3)) // caso do treinador Z sem as 3 insignias
        {
            jogador.x = cidadeAnterior.x;
            jogador.y = cidadeAnterior.y;
            printf("\nVoce ainda não esta preparado para essa batalha!");
            printf("\nEsta de volta a cidade de onde veio.");
            break;
        }
        else // caso dos demais treinadores
        {
            if (algomonJogador.vida <= 0 && quantidadeAlgomonsMortos == 3)
            {
                cidade.treinador.algomon.vida = vidaOriginalAlgomonTreinador;
                jogador.x = cidadeAnterior.x;
                jogador.y = cidadeAnterior.y;
                printf("\nVoce foi derrotado!\nEsta de volta a cidade de onde veio.");
                break;
            }
            else if (algomonJogador.vida <= 0 && quantidadeAlgomonsMortos < 3)
            {
                printf("\n%s esta muito fraco e volta a sua algobola!", algomonJogador.nome);
                int indiceFinalAlgodex = jogador.numAlgomons - 1;
                Algomon algomonAux = jogador.algodex[0];
                for (int i = 0; i < indiceFinalAlgodex; i++)
                {
                    jogador.algodex[i] = jogador.algodex[i + 1];
                }
                jogador.algodex[indiceFinalAlgodex] = algomonAux;
                jogador.algodex[indiceFinalAlgodex].vida = 0;
                algomonJogador = jogador.algodex[quantidadeAlgomonsMortos - 1];
                quantidadeAlgomonsMortos++;
                printf("\n%s toma seu lugar e a batalha continua!", algomonJogador.nome);
            }
            else if (cidade.treinador.algomon.vida <= 0)
            {
                jogador.algodex[0].vida = vidaSobrando;
                jogador.insignias++;
                mapa[cidade.y][cidade.x] = '+';
                jogador = capturaAlgomon(jogador, cidade);
                printf("\nVoce venceu!! \nAgora voce tem %d insígnias.", jogador.insignias);
                break;
            }

            if (vezDoJogador)
            {
                if (cidade.treinador.algomon.tipo == 'C' && algomonJogador.tipo == 'R')
                {
                    cidade.treinador.algomon.vida -= algomonJogador.atk * 2;
                    printf("\nturno %d: %s atacou %s e inflingiu %d \nFoi super efetivo!!.", turno, algomonJogador.nome, cidade.treinador.algomon.nome, 2 * algomonJogador.atk);
                }
                else if (cidade.treinador.algomon.tipo == 'R' && algomonJogador.tipo == 'D')
                {
                    cidade.treinador.algomon.vida -= algomonJogador.atk * 2;
                    printf("\nturno %d: %s atacou %s e inflingiu %d \nFoi super efetivo!!.", turno, algomonJogador.nome, cidade.treinador.algomon.nome, 2 * algomonJogador.atk);
                }
                else if (cidade.treinador.algomon.tipo == 'D' && algomonJogador.tipo == 'C')
                {
                    cidade.treinador.algomon.vida -= algomonJogador.atk * 2;
                    printf("\nturno %d: %s atacou %s e inflingiu %d \nFoi super efetivo!!.", turno, algomonJogador.nome, cidade.treinador.algomon.nome, 2 * algomonJogador.atk);
                }
                else
                {
                    cidade.treinador.algomon.vida -= algomonJogador.atk;
                    printf("\nturno %d: %s atacou %s e inflingiu %d.", turno, algomonJogador.nome, cidade.treinador.algomon.nome, algomonJogador.atk);
                }
                vezDoJogador = 0;
            }

            else
            {
                if (algomonJogador.tipo == 'C' && cidade.treinador.algomon.tipo == 'R')
                {
                    algomonJogador.vida -= cidade.treinador.algomon.atk * 2;
                    printf("\nturno %d: %s atacou %s e inflingiu %d \nFoi super efetivo!!.", turno, cidade.treinador.algomon.nome, algomonJogador.nome, 2 * cidade.treinador.algomon.atk);
                }
                else if (algomonJogador.tipo == 'R' && cidade.treinador.algomon.tipo == 'D')
                {
                    algomonJogador.vida -= cidade.treinador.algomon.atk * 2;
                    printf("\nturno %d: %s atacou %s e inflingiu %d \nFoi super efetivo!!.", turno, cidade.treinador.algomon.nome, algomonJogador.nome, 2 * cidade.treinador.algomon.atk);
                }
                else if (algomonJogador.tipo == 'D' && cidade.treinador.algomon.tipo == 'C')
                {
                    algomonJogador.vida -= cidade.treinador.algomon.atk * 2;
                    printf("\nturno %d: %s atacou %s e inflingiu %d \nFoi super efetivo!!.", turno, cidade.treinador.algomon.nome, algomonJogador.nome, 2 * cidade.treinador.algomon.atk);
                }
                else
                {
                    algomonJogador.vida -= cidade.treinador.algomon.atk;
                    printf("\nturno %d: %s atacou %s e inflingiu %d.", turno, cidade.treinador.algomon.nome, algomonJogador.nome, cidade.treinador.algomon.atk);
                }
                vidaSobrando = algomonJogador.vida;
                vezDoJogador = 1;
            }
        }

        printf("\nTREINADOR -> vida %s: %d", cidade.treinador.algomon.nome, cidade.treinador.algomon.vida);
        printf("\nJOGADOR -> vida %s: %d", algomonJogador.nome, algomonJogador.vida);
        puts("\n\n---------------------");

        turno++;
    }

    resultado.jogador = jogador;
    resultado.cidade = cidade;
    return resultado;
}

Jogador moverParaONorte(char mapa[LINHAS][COLUNAS], Cidade cidadesExistentes[], Jogador jogador)
{
    int y = jogador.y - 1;
    int x = jogador.x;
    Cidade cidadeAnterior = localizaCidade(cidadesExistentes, jogador.x, jogador.y);
    while (y >= 0 && mapa[y][x] != ' ')
    {
        if (mapa[y][x] == '|')
        {
            y--;
        }
        else if (mapa[y][x] == '#')
        {
            Cidade cidade = localizaCidade(cidadesExistentes, x, y);
            jogador.y = y;
            jogador = capturaAlgomon(jogador, cidade);
            mapa[y][x] = '+';
            break;
        }
        else if (mapa[y][x] == '+')
        {
            jogador.y = y;
            break;
        }
        else
        {
            Cidade cidade = localizaCidade(cidadesExistentes, x, y);
            jogador.y = y;
            ResultadoBatalha resultadoBatalha = batalhar(mapa, cidadeAnterior, cidade, jogador);
            jogador = resultadoBatalha.jogador;
            mapa = resultadoBatalha.mapa;
            break;
        }
    }
    return jogador;
}

Jogador moverParaOSul(char mapa[LINHAS][COLUNAS], Cidade cidadesExistentes[], Jogador jogador)
{
    int y = jogador.y + 1;
    int x = jogador.x;
    Cidade cidadeAnterior = localizaCidade(cidadesExistentes, jogador.x, jogador.y);
    while (y < LINHAS && mapa[y][x] != ' ')
    {
        if (mapa[y][x] == '|')
        {
            y++;
        }
        else if (mapa[y][x] == '#')
        {
            Cidade cidade = localizaCidade(cidadesExistentes, x, y);
            jogador.y = y;
            jogador = capturaAlgomon(jogador, cidade);
            mapa[y][x] = '+';
            break;
        }
        else if (mapa[y][x] == '+')
        {
            jogador.y = y;
            break;
        }
        else
        {
            Cidade cidade = localizaCidade(cidadesExistentes, x, y);
            jogador.y = y;
            ResultadoBatalha resultadoBatalha = batalhar(mapa, cidadeAnterior, cidade, jogador);
            jogador = resultadoBatalha.jogador;
            mapa = resultadoBatalha.mapa;
            break;
        }
    }
    return jogador;
}

Jogador moverParaOOeste(char mapa[LINHAS][COLUNAS], Cidade cidadesExistentes[], Jogador jogador)
{
    int y = jogador.y;
    int x = jogador.x - 1;
    Cidade cidadeAnterior = localizaCidade(cidadesExistentes, jogador.x, jogador.y);
    while (x >= 0 && mapa[y][x] != ' ')
    {
        if (mapa[y][x] == '-')
        {
            x--;
        }
        else if (mapa[y][x] == '#')
        {
            Cidade cidade = localizaCidade(cidadesExistentes, x, y);
            jogador.x = x;
            jogador = capturaAlgomon(jogador, cidade);
            mapa[y][x] = '+';
            break;
        }
        else if (mapa[y][x] == '+')
        {
            jogador.x = x;
            break;
        }
        else
        {
            Cidade cidade = localizaCidade(cidadesExistentes, x, y);
            jogador.x = x;
            ResultadoBatalha resultadoBatalha = batalhar(mapa, cidadeAnterior, cidade, jogador);
            jogador = resultadoBatalha.jogador;
            mapa = resultadoBatalha.mapa;
            break;
        }
    }
    return jogador;
}

Jogador moverParaOLeste(char mapa[LINHAS][COLUNAS], Cidade cidadesExistentes[], Jogador jogador)
{
    int y = jogador.y;
    int x = jogador.x + 1;
    Cidade cidadeAnterior = localizaCidade(cidadesExistentes, jogador.x, jogador.y);
    while (x < (COLUNAS - 1) && mapa[y][x] != ' ')
    {
        if (mapa[y][x] == '-')
        {
            x++;
        }
        else if (mapa[y][x] == '#')
        {
            Cidade cidade = localizaCidade(cidadesExistentes, x, y);
            jogador.x = x;
            jogador = capturaAlgomon(jogador, cidade);
            mapa[y][x] = '+';
            break;
        }
        else if (mapa[y][x] == '+')
        {
            jogador.x = x;
            break;
        }
        else
        {
            Cidade cidade = localizaCidade(cidadesExistentes, x, y);
            jogador.x = x;
            ResultadoBatalha resultadoBatalha = batalhar(mapa, cidadeAnterior, cidade, jogador);
            jogador = resultadoBatalha.jogador;
            mapa = resultadoBatalha.mapa;
            break;
        }
    }
    return jogador;
}

Jogador leAcao(char mapa[LINHAS][COLUNAS], Cidade cidadesExistentes[], Jogador jogador)
{

    int y, x = 0;

    char movimento;
    printf("\nQual seu movimento (wasdrf)?");
    scanf("%c", &movimento);
    {
        switch (movimento)
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
        case 'r':
            jogador = rolaMenuParaCima(jogador);

            break;
        case 'f':
            jogador = rolaMenuParaBaixo(jogador);

            break;
        default:
            break;
        }
    };
    scanf("%*c");
    return jogador;
}

void exibeMenu(Jogador jogador)
{

    printf("Algodex (%d/%d) Algomons: %d Insignias: %d \n", jogador.numAlgomons, TAMALGODEX, jogador.numAlgomons, jogador.insignias);
    printf("%-10s                Atk: %d HP: %d Type: %c\n", jogador.algodex[0].nome, jogador.algodex[0].atk, jogador.algodex[0].vida, jogador.algodex[0].tipo);
    printf("%-10s                Atk: %d HP: %d Type: %c\n", jogador.algodex[1].nome, jogador.algodex[1].atk, jogador.algodex[1].vida, jogador.algodex[1].tipo);
    printf("%-10s                Atk: %d HP: %d Type: %c\n", jogador.algodex[2].nome, jogador.algodex[2].atk, jogador.algodex[2].vida, jogador.algodex[2].tipo);
    printf("Autoria: Lucas Paiva dos Santos e Italo de Almeida Ribeiro");
}

int main()
{
    Algomon algomonsDisponiveis[TAMALGODEX];
    algomonsDisponiveis[0] = criaAlgomon("Ifssauro", 5, 20, 'C');
    algomonsDisponiveis[1] = criaAlgomon("Whiledle", 3, 40, 'R');
    algomonsDisponiveis[2] = criaAlgomon("Vectoray", 4, 30, 'D');
    algomonsDisponiveis[3] = criaAlgomon("Elsenite", 4, 38, 'C');
    algomonsDisponiveis[4] = criaAlgomon("Forlax", 4, 37, 'R');
    algomonsDisponiveis[5] = criaAlgomon("Arrayzard", 5, 32, 'D');
    algomonsDisponiveis[6] = criaAlgomon("Switcheve", 4, 55, 'C');
    algomonsDisponiveis[7] = criaAlgomon("Doiling", 7, 23, 'R');
    algomonsDisponiveis[8] = criaAlgomon("Stringle", 4, 43, 'D');
    algomonsDisponiveis[9] = criaAlgomon("Elsifee", 7, 21, 'C');
    algomonsDisponiveis[10] = criaAlgomon("Loopoise", 4, 41, 'R');
    algomonsDisponiveis[11] = criaAlgomon("Structurer", 5, 29, 'D');
    algomonsDisponiveis[12] = criaAlgomon("Endifee", 4, 39, 'C');
    algomonsDisponiveis[13] = criaAlgomon("Jynext", 3, 55, 'R');
    algomonsDisponiveis[14] = criaAlgomon("Mewboolean", 8, 23, 'D');
    algomonsDisponiveis[15] = criaAlgomon("Unlesonix", 3, 47, 'C');
    algomonsDisponiveis[16] = criaAlgomon("Foreach", 7, 22, 'R');
    algomonsDisponiveis[17] = criaAlgomon("Eveeinteger", 5, 28, 'D');
    algomonsDisponiveis[18] = criaAlgomon("Ceepluplus", 7, 40, 'L');

    Treinador treinadoresExistentes[NUMTREINADORES];
    treinadoresExistentes[0] = criaTreinador('Z', algomonsDisponiveis[18]);
    treinadoresExistentes[1] = criaTreinador('X', algomonsDisponiveis[4]);
    treinadoresExistentes[2] = criaTreinador('Y', algomonsDisponiveis[15]);
    treinadoresExistentes[3] = criaTreinador('R', algomonsDisponiveis[11]);

    Cidade cidadesExistentes[NUMCIDADES];
    cidadesExistentes[0] = criaCidade(6, 0, algomonsDisponiveis[3]);
    cidadesExistentes[1] = criaCidade(12, 1, algomonsDisponiveis[5]);
    cidadesExistentes[2] = criaCidade(18, 1, algomonsDisponiveis[6]);
    cidadesExistentes[3] = criaCidade(0, 3, algomonsDisponiveis[7]);
    cidadesExistentes[4] = criaCidade(6, 3, algomonsDisponiveis[8]);
    cidadesExistentes[5] = criaCidade(12, 3, algomonsDisponiveis[9]);
    cidadesExistentes[6] = criaCidade(18, 3, algomonsDisponiveis[10]);
    cidadesExistentes[7] = criaCidade(10, 5, algomonsDisponiveis[12]);
    cidadesExistentes[8] = criaCidade(22, 5, algomonsDisponiveis[13]);
    cidadesExistentes[9] = criaCidade(6, 7, algomonsDisponiveis[14]);
    cidadesExistentes[10] = criaCidade(10, 7, algomonsDisponiveis[16]);
    cidadesExistentes[11] = criaCidade(16, 7, algomonsDisponiveis[17]);
    cidadesExistentes[12] = criaCidadeComTreinador(0, 0, algomonsDisponiveis[18], treinadoresExistentes[0]);
    cidadesExistentes[13] = criaCidadeComTreinador(22, 3, algomonsDisponiveis[4], treinadoresExistentes[1]);
    cidadesExistentes[14] = criaCidadeComTreinador(0, 7, algomonsDisponiveis[15], treinadoresExistentes[2]);
    cidadesExistentes[15] = criaCidadeComTreinador(22, 7, algomonsDisponiveis[11], treinadoresExistentes[3]);

    Jogador jogador1;
    jogador1.simbolo = 'A';
    jogador1.x = 6;
    jogador1.y = 3;
    jogador1.numAlgomons = 3;
    jogador1.insignias = 0;
    jogador1.algodex[0] = algomonsDisponiveis[0];
    jogador1.algodex[1] = algomonsDisponiveis[1];
    jogador1.algodex[2] = algomonsDisponiveis[2];

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
        exibeMenu(jogador1);
        jogador1 = leAcao(mapa, cidadesExistentes, jogador1);
    }

    return 0;
}