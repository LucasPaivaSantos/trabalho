#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LINHAS 8
#define COLUNAS 24
#define NUMTREINADORES 4
#define NUMCIDADES 16
#define TAMALGODEX 15
#define TAMMENU 3

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

typedef struct
{
    Jogador jogador;
    int indicePrimeiroExibido;
} ResultadoAcao;

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
        printf("Voce capturou %s!!", cidade.algomon.nome);
        jogador.algodex[jogador.numAlgomons] = cidade.algomon;
        jogador.numAlgomons++;
    }
    return jogador;
}

int possuiTodasAsInsignas(Jogador jogador)
{
    if (jogador.insignias == NUMTREINADORES)
    {
        printf("Parabens! voce conseguiu toda as 4 insignias e capturou cecplusplus");
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
        printf("Fim de jogo!\n Todos os seus algomons estao fracos demais para prosseguir");
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

void fimDeJogo()
{
    printf("\n Voce perdeu o jogo");
    exit(1);
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
    }
    fimDeJogo();
}

ResultadoBatalha batalhar(char mapa[LINHAS][COLUNAS], Cidade cidadeAnterior, Cidade cidade, Jogador jogador)
{
    ResultadoBatalha resultado;
    int quantidadeAlgomonsMortos = 0;
    int vidaOriginalAlgomonTreinador = cidade.treinador.algomon.vida;
    int indiceAlgomonJogador = primeiroAlgomonVivo(jogador);
    Algomon algomonJogador = jogador.algodex[indiceAlgomonJogador];
    int vezDoJogador = 1;
    int turno = 1;

    printf("\nInicio da batalha, apresentem seus algomons:");
    printf("\nTREINADOR -> %s: vida inicial: %d, tipo: %c, ataque: %d", cidade.treinador.algomon.nome, cidade.treinador.algomon.vida, cidade.treinador.algomon.tipo, cidade.treinador.algomon.atk);
    printf("\nJOGADOR -> %s: vida inicial: %d, tipo: %c, ataque: %d", algomonJogador.nome, algomonJogador.vida, algomonJogador.tipo, algomonJogador.atk);
    printf("\n\n---------------------");
    printf("\n---------------------");

    while (1 == 1)
    {
        if (algomonJogador.vida <= 0 && quantidadeAlgomonsMortos == 3)
        {
            cidade.treinador.algomon.vida = vidaOriginalAlgomonTreinador;
            jogador.x = cidadeAnterior.x;
            jogador.y = cidadeAnterior.y;
            puts("\nVoce PERDEU! :(");
            puts("\nEsta de volta a cidade de onde veio.");
            break;
        }
        else if (algomonJogador.vida <= 0 && quantidadeAlgomonsMortos < 3)
        {
            quantidadeAlgomonsMortos++;
            printf("%s esta muito fraco!\n", algomonJogador.nome);
            jogador.algodex[indiceAlgomonJogador].vida = 0;
            algomonJogador = jogador.algodex[primeiroAlgomonVivo(jogador)];
            printf("%s toma seu lugar e a batalha continua!", algomonJogador.nome);
        }
        else if (cidade.treinador.algomon.vida <= 0)
        {
            jogador.insignias++;
            mapa[cidade.y][cidade.x] = '+';
            jogador = capturaAlgomon(jogador, cidade);
            printf("\nVoce GANHOU!!! \nVoce tem agora %d insígnias.", jogador.insignias);
            break;
        }

        if (vezDoJogador)
        {
            if (cidade.treinador.algomon.tipo == 'C' && algomonJogador.tipo == 'R')
            {
                cidade.treinador.algomon.vida -= algomonJogador.atk * 2;
                printf("\nturno %d: %s atacou %s e inflingiu %d \n foi super efetivo!.", turno, algomonJogador.nome, cidade.treinador.algomon.nome, 2 * algomonJogador.atk);
            }
            else if (cidade.treinador.algomon.tipo == 'R' && algomonJogador.tipo == 'D')
            {
                cidade.treinador.algomon.vida -= algomonJogador.atk * 2;
                printf("\nturno %d: %s atacou %s e inflingiu %d \n foi super efetivo!.", turno, algomonJogador.nome, cidade.treinador.algomon.nome, 2 * algomonJogador.atk);
            }
            else if (cidade.treinador.algomon.tipo == 'D' && algomonJogador.tipo == 'C')
            {
                cidade.treinador.algomon.vida -= algomonJogador.atk * 2;
                printf("\nturno %d: %s atacou %s e inflingiu %d \n foi super efetivo!.", turno, algomonJogador.nome, cidade.treinador.algomon.nome, 2 * algomonJogador.atk);
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
                printf("\nturno %d: %s atacou %s e inflingiu %d \n foi super efetivo!.", turno, cidade.treinador.algomon.nome, algomonJogador.nome, 2 * cidade.treinador.algomon.atk);
            }
            else if (algomonJogador.tipo == 'R' && cidade.treinador.algomon.tipo == 'D')
            {
                algomonJogador.vida -= cidade.treinador.algomon.atk * 2;
                printf("\nturno %d: %s atacou %s e inflingiu %d \n foi super efetivo!.", turno, cidade.treinador.algomon.nome, algomonJogador.nome, 2 * cidade.treinador.algomon.atk);
            }
            else if (algomonJogador.tipo == 'D' && cidade.treinador.algomon.tipo == 'C')
            {
                algomonJogador.vida -= cidade.treinador.algomon.atk * 2;
                printf("\nturno %d: %s atacou %s e inflingiu %d \n foi super efetivo!.", turno, cidade.treinador.algomon.nome, algomonJogador.nome, 2 * cidade.treinador.algomon.atk);
            }
            else
            {
                algomonJogador.vida -= cidade.treinador.algomon.atk;
                printf("\nturno %d: %s atacou %s e inflingiu %d.", turno, cidade.treinador.algomon.nome, algomonJogador.nome, cidade.treinador.algomon.atk);
            }
            vezDoJogador = 1;
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
            // cidade = resultadoBatalha.cidade;
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
            // cidade = resultadoBatalha.cidade;
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
            // cidade = resultadoBatalha.cidade;
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
            // cidade = resultadoBatalha.cidade;
            break;
        }
    }
    return jogador;
}

ResultadoAcao leAcao(char mapa[LINHAS][COLUNAS], Cidade cidadesExistentes[], Jogador jogador, int indicePrimeiroExibido)
{
    ResultadoAcao resultado;
    resultado.indicePrimeiroExibido = indicePrimeiroExibido;

    int y, x = 0;

    char movimento;
    printf("Qual seu movimento (wasdrf)?");
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
            if (resultado.indicePrimeiroExibido > 0)
            {
                resultado.indicePrimeiroExibido--;
            }

            break;
        case 'f':
            if (resultado.indicePrimeiroExibido < jogador.numAlgomons - 3)
            {
                resultado.indicePrimeiroExibido++;
            }

            break;
        default:
            break;
        }
    };
    scanf("%*c");
    resultado.jogador = jogador;
    return resultado;
}

void exibeMenu(Jogador jogador, int indicePrimeiroExibido)
{

    printf("Algodex (%d/%d) Algomons: %d Insignias: %d \n", jogador.numAlgomons, TAMALGODEX, jogador.numAlgomons, jogador.insignias);
    for (int i = 0; i < TAMMENU; i++)
    {
        printf("%s\t\tAtk: %d HP: %d Type: %c\n", jogador.algodex[indicePrimeiroExibido + i].nome, jogador.algodex[indicePrimeiroExibido + i].atk, jogador.algodex[indicePrimeiroExibido + i].vida, jogador.algodex[indicePrimeiroExibido + i].tipo);
    }
}

int main()
{
    int indicePrimeiroExibido = 0;

    Algomon algomonsDisponiveis[TAMALGODEX];
    algomonsDisponiveis[0] = criaAlgomon("Ifssauro", 5, 20, 'C');
    algomonsDisponiveis[1] = criaAlgomon("Whiledle", 3, 40, 'R');
    algomonsDisponiveis[2] = criaAlgomon("Vectoray", 4, 30, 'D');
    algomonsDisponiveis[3] = criaAlgomon("Elsenite", 5, 18, 'C');
    algomonsDisponiveis[4] = criaAlgomon("Forlax", 3, 36, 'R');
    algomonsDisponiveis[5] = criaAlgomon("Arrayzard", 2, 50, 'D');
    algomonsDisponiveis[6] = criaAlgomon("Switcheve", 5, 22, 'C');
    algomonsDisponiveis[7] = criaAlgomon("Doiling", 3, 40, 'R');
    algomonsDisponiveis[8] = criaAlgomon("Stringle", 4, 32, 'D');
    algomonsDisponiveis[9] = criaAlgomon("Elsifee", 7, 15, 'C');
    algomonsDisponiveis[10] = criaAlgomon("Loopoise", 4, 25, 'R');
    algomonsDisponiveis[11] = criaAlgomon("Structurer", 4, 50, 'D');
    algomonsDisponiveis[12] = criaAlgomon("Ruby", 6, 42, 'C');
    algomonsDisponiveis[13] = criaAlgomon("Javaprie", 5, 30, 'R');
    algomonsDisponiveis[14] = criaAlgomon("Ceepluplus", 8, 50, 'L');

    Treinador treinadoresExistentes[NUMTREINADORES];
    treinadoresExistentes[0] = criaTreinador('Z', algomonsDisponiveis[14]);
    treinadoresExistentes[1] = criaTreinador('X', algomonsDisponiveis[13]);
    treinadoresExistentes[2] = criaTreinador('Y', algomonsDisponiveis[12]);
    treinadoresExistentes[3] = criaTreinador('R', algomonsDisponiveis[11]);

    Cidade cidadesExistentes[NUMCIDADES];
    cidadesExistentes[0] = criaCidade(6, 0, algomonsDisponiveis[3]);
    cidadesExistentes[1] = criaCidade(12, 1, algomonsDisponiveis[4]);
    cidadesExistentes[2] = criaCidade(18, 1, algomonsDisponiveis[5]);
    cidadesExistentes[3] = criaCidade(0, 3, algomonsDisponiveis[6]);
    cidadesExistentes[4] = criaCidade(6, 3, algomonsDisponiveis[7]);
    cidadesExistentes[5] = criaCidade(12, 3, algomonsDisponiveis[8]);
    cidadesExistentes[6] = criaCidade(18, 3, algomonsDisponiveis[9]);
    cidadesExistentes[7] = criaCidade(10, 5, algomonsDisponiveis[10]);
    cidadesExistentes[8] = criaCidade(22, 5, algomonsDisponiveis[11]);
    cidadesExistentes[9] = criaCidade(6, 7, algomonsDisponiveis[12]);
    cidadesExistentes[10] = criaCidade(10, 7, algomonsDisponiveis[13]);
    cidadesExistentes[11] = criaCidade(16, 7, algomonsDisponiveis[14]);
    cidadesExistentes[12] = criaCidadeComTreinador(0, 0, algomonsDisponiveis[14], treinadoresExistentes[0]);
    cidadesExistentes[13] = criaCidadeComTreinador(22, 3, algomonsDisponiveis[13], treinadoresExistentes[1]);
    cidadesExistentes[14] = criaCidadeComTreinador(0, 7, algomonsDisponiveis[12], treinadoresExistentes[2]);
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
        // system("clear");
        printf("\n");
        exibeMapa(mapa, jogador1);
        exibeMenu(jogador1, indicePrimeiroExibido);
        ResultadoAcao resultado = leAcao(mapa, cidadesExistentes, jogador1, indicePrimeiroExibido);
        jogador1 = resultado.jogador;
        indicePrimeiroExibido = resultado.indicePrimeiroExibido;
        printf("\n numAlgomons: %d", jogador1.numAlgomons);

        for (int i = 0; i < jogador1.numAlgomons; i++)
        {
            printf("\n jogador1.algodex[%d] -> %s", i, jogador1.algodex[i].nome);
        }
    }

    return 0;
}