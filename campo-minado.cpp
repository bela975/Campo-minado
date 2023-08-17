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

//criando a função responsavel pela lógica chave do jogo,
//que é contar a quantidade de minas nos quadrados adjacentes
int contarMinas(int linha, int coluna, int mines[][2],
                char matrizReal[][ladoMax]
{
    int i;
    int mineCount = 0;

    //vamos checar cada um dos adjacentes:
    //primeiro conferimos se é um quadrado de fato, chamando a existe
    //em cima:
    if(existe (linha-1, coluna) == true)
    {
        // se houver mina, add ao contador
        if(minada (linha-1, coluna, matrizReal) == true)
        mineCount++;
    }

    //em baixo
    if(existe (linha+1, coluna) == true)
    {
        // se houver mina, add ao contador
        if(minada (linha+1, coluna, matrizReal) == true)
            mineCount++;
    }

    //direita...e assim vai até contemplar todos os ladinhos
    if(existe (linha, coluna+1) == true)
    {
        // se houver mina, add ao contador
        if(minada (linha, coluna+1, matrizReal) == true)
            mineCount++;
    }

    if(existe (linha, coluna-1) == true)
    {
        // se houver mina, add ao contador
        if(minada (linha, coluna-1, matrizReal) == true)
            mineCount++;
    }

    if(existe (linha-1, coluna+1) == true)
    {
        // se houver mina, add ao contador
        if(minada (linha-1, coluna+1, matrizReal) == true)
            mineCount++;
    }

    if(existe (linha-1, coluna-1) == true)
    {
        // se houver mina, add ao contador
        if(minada (linha-1, coluna-1, matrizReal) == true)
            mineCount++;
    }

    if(existe (linha+1, coluna+1) == true)
    {
        // se houver mina, add ao contador
        if(minada (linha+1, coluna+1, matrizReal) == true)
            mineCount++;
    }

    if(existe (linha+1, coluna-1) == true)
    {
        // se houver mina, add ao contador
        if(minada (linha+1, coluna-1, matrizReal) == true)
            mineCount++;
    }

    return(mineCount);
}

//criando uma função recursiva contendo as mecanicas do jogo
bool jogoAtivo(char matrizAtual[][ladoMax], char matrizReal[][ladoMax],
               int minas[][2], int linha, int coluna, int *pRestantes)
{
    //estabelecendo o caso base da função recursiva:
    if(matrizAtual[linha][coluna] != '-')
        return (false);

    int i, j;

    //estabelecendo a situação de game over = abrir uma mina
    if (matrizReal[linha][coluna] == '*')
    {
        //se tiver uma bomba por default na posição tb vai ter na uma na gameplay
        matrizAtual[linha][coluna]='*';


        for (i=0; i<minas; i++)
            matrizAtual[minas[i][0]][mines[i][1]]='*';

        //printando a versão da matriz mostrando a bomba
        printMatriz (matrizAtual);
        printf ("\nQue pena, explodiu. Fim de jogo.\n");
        return (true);
    }

    else
    {
        //caso não haja bomba no quadrado escolhido,
        // mostraremos o numero de bombas adjacentes!
        int minecount = contarMinas(linha, coluna, minas, matrizReal);
        (*pRestantes)--;

        matrizAtual[linha][coluna] = mineCount +0;

        if(!mineCount)
        {
            //fazendo a analise de qtd de minas para cada um dos quadrados,
            //desde que existam na matriz
            if (existe (linha-1, coluna) == true)
            {
                //se livre de bombas, jogo continua rodando
                if (minada (linha-1, coluna, matrizReal) == false)
                    jogoAtivo(matrizAtual, matrizReal, minas, linha-1, coluna, pRestantes);
            }

            if (existe (linha+1, coluna) == true)
            {
                //se livre de bombas, jogo continua rodando
                if (minada (linha+1, coluna, matrizReal) == false)
                    jogoAtivo(matrizAtual, matrizReal, minas, linha+1, coluna, pRestantes);
            }

            if (existe (linha, coluna+1) == true)
            {
                //se livre de bombas, jogo continua rodando
                if (minada (linha, coluna+1, matrizReal) == false)
                    jogoAtivo(matrizAtual, matrizReal, minas, linha, coluna+1, pRestantes);
            }

            if (existe (linha, coluna-1) == true)
            {
                //se livre de bombas, jogo continua rodando
                if (minada (linha, coluna-1, matrizReal) == false)
                    jogoAtivo(matrizAtual, matrizReal, minas, linha, coluna-1, pRestantes);
            }

            if (existe (linha-1, coluna+1) == true)
            {
                //se livre de bombas, jogo continua rodando
                if (minada (linha-1, coluna+1, matrizReal) == false)
                    jogoAtivo(matrizAtual, matrizReal, minas, linha-1, coluna+1, pRestantes);
            }

            if (existe (linha+1, coluna+1) == true)
            {
                //se livre de bombas, jogo continua rodando
                if (minada (linha+1, coluna+1, matrizReal) == false)
                    jogoAtivo(matrizAtual, matrizReal, minas, linha+1, coluna+1, pRestantes);
            }

            if (existe (linha+1, coluna-1) == true)
            {
                //se livre de bombas, jogo continua rodando
                if (minada (linha+1, coluna-1, matrizReal) == false)
                    jogoAtivo(matrizAtual, matrizReal, minas, linha+1, coluna-1, pRestantes);
            }
        }

        return(false);
    }
}

//função responsável por gerar bombas aleatoriamente
void plantarMinas(int minas[][2], char matrizReal[][ladoMax])
{
    bool plantar[ladoMax*ladoMax];

    memset (plantar, false, sizeof (plantar));

    //criando um loop para que sejam criadas o total de bombas
    //estabelecidas quando o jogador selecionou a dificuldade
    for (int i=0; i<minas;)
    {
        int aleatorio = rand() % (lado*lado);
        int x = aleatorio / lado;
        int y = aleatorio % lado;

        //adicionando minas caso o espaço esteja sem nenhuma
        if (plantar[aleatorio] == false)
        {
            //coordenada em analise
            mines[i][0]= x;

            mines[i][1] = y;

            //aqui é feita a inserção da mina no espaço disponivel
            matrizReal[minas[i][0]][minas[i][1]] = '*';
            plantar[aleatorio] = true;
            i++;
        }
    }
    return;
}

//criando a função responsavel por inicializar o jogo
void iniciar(char matrizReal[][ladoMax], char matrizAtual[][ladoMax])
{
    srand(time(NULL));

    //inicializando os quadrados zerados
    for (int i=0; i<lado; i++)
    {
        for (int j=0; j<lado; j++)
        {
            matrizAtual[i][j] = matrizReal[i][j] = '-';
        }
    }

    return;
}
//função para realocar as minas para um quadrado
//caso ele esteja vazio.
void realoc (int linha, int coluna, char matriz[][ladoMax])
{
    //varrendo a matriz
    for (int i=0; i<lado; i++)
    {
        for (int j=0; j<lado; j++)
        {
            if (board[i][j] != '*')
            {
                board[i][j] = '*';
                board[row][col] = '-';
                return;
            }
        }
    }
    return;
}
//função responsavel pela jogabilidade
void jogando ()
{
    //inicializando:
    bool gameOver = false;
    char matrizReal[ladoMax][ladoMax], matrizAtual[ladoMax][ladoMax];

    int pRestantes = lado * lado - minas, x, y;
    //guardando as coordenadas de todas as minas
    int minas[maxMinas][2];

    iniciar(matrizReal, matrizAtual);

    plantarMinas(minas,matrizReal);

    int indiceJogada = 0;

    while(gameOver == false)
    {
        printf ("Estado atual do tabuleiro : \n");
        mostrarMatriz (matrizAtual);
        jogada (&x, &y, jogadas, indiceJogada);

        if (indiceJogada == 0)
        {
            //removendo a mina da primeira casa selecionada pelo jogador
            if (minada (x, y, matrizReal) == true)
                realoc (x, y, matrizReal);
        }

        indiceJogada ++;

        gameOver = jogoAtivo (matrizAtual, matrizReal, minas, x, y, &pRestantes);

        if ((gameOver == false) && (pRrestantes == 0))
        {
            printf ("\nParabéns, você ganhou!\n");
            gameOver = true;
        }
    }

    return;
}
//função que permite que o jogador selecione
// o tamanho do tabuleiro e a qtd de bombas:
void customizar (int l, int m)
{
    printf ("selecione as dimensões do seu tabuleiro, l: \n");
    scanf ("%d", &l);
    printf ("selecione a quantidade de minas desejada, m: \n");
    scanf ("%d", &m);

    int maxMinas = (l*l)*(15/100);

    if (m > maxMinas)
    {
        while(m > maxMinas)
        {
            printf("Você inseriu uma quantia muito alta. \n");
            printf("O máximo adequado de bombas para esse tabuleiro é %d.", maxMinas);
            printf("selecione uma nova quantia de minas desejada, m: \n");
            scanf("%d", &m);
        }
    } else
    {
        lado = l;
        minas = m;

    }

    return;
}

// Driver Program to test above functions
int main()
{
    /* Choose a level between
    --> BEGINNER = 9 * 9 Cells and 10 Mines
    --> INTERMEDIATE = 16 * 16 Cells and 40 Mines
    --> ADVANCED = 24 * 24 Cells and 99 Mines
    */
    chooseDifficultyLevel (BEGINNER);

    playMinesweeper ();
    return (0);


}
