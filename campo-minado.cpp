//
// Created by Isabela Spinelli on 10/08/2023.
// Campo minado usando c++

#include<bits/stdc++.h>
using namespace std;

#define Iniciante 0
#define Intermediario 1
#define Avancado 2
#define ladoMax 25
#define maxMinas 99
#define qtdMovimentos 526 // (25 * 25 - 99)

int lado;
int minas;

//funcao booleana p checar se o quadrado selecionado existe
bool existe(int linha, int coluna)
{
    //retorna se ele está dentro da nossa matriz, a malha do jogo
    return (linha >= 0) && (linha < lado) &&
            (coluna >= 0) && (coluna < lado);


}
//função booleana pra indicar se há ou não bomba na posição em analise
bool minada (int linha, int coluna, char matriz[][ladoMax])
{
    if (matriz[linha][coluna] == '*')
        return (true);
    else
        return (false);
}

//função para pegar valores escolhidos pelo jogador
void jogada(int *x, int *y)
{
    printf("Selecione o quadrado desejado (linha,coluna): ");
    scanf("%d %d", x, y);
    return;
}

//função para printar a matriz que reflete o estado atual do jogo
void mostrarMatriz(char matrizAtual[][ladoMax])
{
    int i, j;

    printf ("    ");

    for (i=0; i<lado; i++)
        printf ("%d ", i);

    printf ("\n\n");

    for (i=0; i<lado; i++)
    {
        printf ("%d   ", i);

        for (j=0; j<lado; j++)
            printf ("%c ", matrizAtual[i][j]);
        printf ("\n");
    }
    return;
}


