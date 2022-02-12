#include <stdio.h>
#define LINHAS 8
#define COLUNAS 24

typedef struct
{
  int linha;
  int coluna;
  int insignas;
  char simbolo;
} Jogador;

typedef struct
{
  char nome[20];
  int atk;
  int health;
  char tipo;
} Algmon;

void exibeMapa(char mtzMapa[LINHAS][COLUNAS], Jogador jogador)
{
  int l, c = 0;
  for (l = 0; l < LINHAS; l++)
  {
    for (c = 0; mtzMapa[l][c] != '\0'; c++)
    {
      if (jogador.linha == l && jogador.coluna == c)
      {
        printf("%c", jogador.simbolo);
      }
      else
      {
        printf("%c", mtzMapa[l][c]);
      }
    }
    printf("\n");
  }
}

int podeMoverPara(char mapa[LINHAS][COLUNAS], int l, int c)
{
  char permitidos[25 + 1] = "|-+#abcdefghijklmnopqXYZR";
  int i;
  for (i = 0; permitidos[i] != '\0'; i++)
  {
    if (mapa[l][c] == permitidos[i])
    {
      return 1;
    }
  }
  return 0;
}

Jogador moverParaONorte(char mapa[LINHAS][COLUNAS], Jogador jogador)
{
  printf("\n");
  while (jogador.linha > 0 && podeMoverPara(mapa, jogador.linha - 1, jogador.coluna))
  {
    jogador.linha--;
  }
  return jogador;
}
Jogador moverParaOSul(char mapa[LINHAS][COLUNAS], Jogador jogador)
{
  printf("\n");
  while (jogador.linha < COLUNAS && podeMoverPara(mapa, jogador.linha + 1, jogador.coluna))
  {
    jogador.linha++;
  }
  return jogador;
}
Jogador moverParaOOeste(char mapa[LINHAS][COLUNAS], Jogador jogador)
{
  printf("\n");
  while (jogador.linha > 0 && podeMoverPara(mapa, jogador.linha, jogador.coluna - 1))
  {
    jogador.coluna--;
  }
  return jogador;
}
Jogador moverParaOLeste(char mapa[LINHAS][COLUNAS], Jogador jogador)
{
  printf("\n");
  while (jogador.linha < LINHAS && podeMoverPara(mapa, jogador.linha, jogador.coluna + 1))
  {
    jogador.coluna++;
  }
  return jogador;
}

Jogador leAcao(char mtzMapa[LINHAS][COLUNAS], Jogador jogador)
{
  int v, h = 0;
  /*char rolagem;
  rolagem = acao; */
  char direcao;
  printf("Qual seu movimento (wasdrf)?");
  scanf("%c", &direcao);
  {
    switch (direcao)
    {
    case 'w':
      jogador = moverParaONorte(mtzMapa, jogador);

      break;
    case 's':
      jogador = moverParaOSul(mtzMapa, jogador);

      break;
    case 'a':
      jogador = moverParaOOeste(mtzMapa, jogador);

      break;
    case 'd':
      jogador = moverParaOLeste(mtzMapa, jogador);

      break;
    default:
      break;
    }
  };
  scanf("%*c");
  return jogador;
}

int main()
{
  printf("\tBEM VINDO A ALGMON!!!\n\n");

  int nAlgmons = 0;
  int nInsignas = 0;
  Jogador jogador = {3, 6, 0, 'A'};


  char mtzMapa[LINHAS][COLUNAS] = {
      {"Z     #                "},
      {"|     |     #-----#    "},
      {"|     |     |     |    "},
      {"#-----+-----#-----#---X"},
      {"      |               |"},
      {"      |   #-----------#"},
      {"      |   |            "},
      {"Y-----#---#-----#-----R"}};

  while (jogador.insignas != 5)
  {
    exibeMapa(mtzMapa, jogador);
    jogador = leAcao(mtzMapa, jogador);
  }

  return 0;
}