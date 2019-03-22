#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define TAM 8  /* Tamanho da grade */

/* Funções */
void grade(char mapa[][TAM]);
int valid_moves(char mapa[][TAM], int moves[][TAM], char player);
void faz_movim(char mapa[][TAM], int linha, int col, char player);
void computer_move(char mapa[][TAM], int moves[][TAM], char player);
int melhor_move(char mapa[][TAM], int moves[][TAM], char player);
int c_pontos(char mapa[][TAM], char player);

int main()
{
  char mapa [TAM][TAM] = { 0 };  /* A grade             */
  int moves[TAM][TAM] = { 0 };    /* Movimentos validos  */
  int linha = 0;                      /* idice da linha   */
  int col = 0;                      /* indice da coluna  */
  int num_jog = 0;              /* Numero de jogadas     */
  int conta_moves = 0;              /* conta movimentos     */
  int invalid_moves = 0;            /* conta movimentos invalidos  */
  int comp_pont = 0;               /* pontuação do computador      */
  int user_pont = 0;               /* pontuação do jogador        */
  char y = 0;                       /* letra da coluna       */
  int x = 0;                        /* numero da linha     */
  char repete = 0;                   /* repetição */
  int player = 0;                   /* indicador jogador    */
  char joga1[20],joga2[20];         /* jogadores */
  int escol = 0;                         /*indica se vai ser multiplayer ou nao */

   printf("\nOTHELLO\n\n");
  printf("Iniciando o jogo.\n");
  printf("   Jogador 1 sera - (O)\n   Jogador 2 sera   - (@).\n");
  printf("Digite o nome do primeiro jogador :\n");
  gets(joga1); /* escreve o nome do jogador 1*/

  printf("Digite o nome do segundo jogador :\n");
  gets(joga2);  /* escreve o nome do jogador 2*/

 printf("Caso deseje jogar contra o computador digite: 1 \n ");
  scanf("%d",&escol);  /* caso queira jogar contra o computador */


  printf("INSTRUCOES selecione o local digitando um numero para a linha\n "
    "e sem dar espaco selecione a coluna deste mesmo local .\n");
  printf("\nBoa Sorte!  Precione enter para iniciar.\n");
  scanf("%c", &repete);



   /* onde sera solicitado para jogar */
 /* O laço de repetição principal do jogo */
   do
   {
     /* em jogos par o jogador 1 que comeca */
     /* em jogos impares o jogador 2 comeca*/
     player = ++ num_jog % 2;
     conta_moves = 4;                /* Comeca com quatro marcadores */

     /* anulando todas casas da grade */
     for(linha = 0; linha < TAM; linha++)
       for(col = 0; col < TAM; col++)
         mapa[linha][col] = ' ';

     /* colaca os quatro marcadores para iniciar no centro*/
     mapa[TAM/2 - 1][TAM/2 - 1] = mapa[TAM/2][TAM/2] = 'O';
     mapa[TAM/2 - 1][TAM/2] = mapa[TAM/2][TAM/2 - 1] = '@';

     /* o laco de repeticao do jogo */
     do
     {
       grade(mapa);             /* Mostrar a grade  */
       if(player++ % 2)
       { /*   e a vez do jogador 1                    */
         if(valid_moves(mapa, moves, 'O'))
         {
           /* le os movimento do jogador ate que o movimento seja valido */
           for(;;)
           {
             fflush(stdin);              /*   limpa o buffer do teclado */
             printf("digite o movimento %s ",joga1," linha depois coluna:\n ");
             scanf("%d%c", &x, &y);              /* le a oq foi digitado        */
             y = tolower(y) - 'a';         /* Converte o indice da coluna */
             x--;                          /* Converte a linha do indice    */
             if( x>=0 && y>=0 && x<TAM && y<TAM && moves[x][y])
             {
               faz_movim(mapa, x, y, 'O');
               conta_moves++;              /* conta movimento */
               break;
             }
             else
               printf("Movimento nao valido digite de novo.\n");
           }
         }
         else                              /* nao valida movimento */
           if(++invalid_moves<2)
           {
             fflush(stdin);
             printf("\n Voce tem q passar precione enter");
             scanf("%c", &repete);
           }
           else
             printf("\n Nem um pode seguir o jogo acabou.\n");
       }
       else
if(escol==1){
{ /* e a vez do jogador 2    */
         if(valid_moves(mapa, moves, '@')) /* Verifica a existencia de movimento validos */
         {
           invalid_moves = 0;               /* redefine contagem invalida   */
           computer_move(mapa, moves, '@');
           conta_moves++;                   /* conta movimento */
         }
         else
         {
           if(++invalid_moves<2)
             printf("\n Voce tem q passar precione enter\n"); /* Nao valido movimento */
           else
             printf("\n Nem um pode serguir o jogo acabou.\n");
         }
       }
}
else
if(escol!=1){
 if(valid_moves(mapa, moves, '@'))
         {
           /* le os movimento do jogador ate que o movimento seja valido */
           for(;;)
           {
             fflush(stdin);              /*   Libera o buffer do teclado */
             printf("digite o movimento %s ",joga2," linha depois coluna:\n ");
             scanf("%d%c", &x, &y);              /* le a oq foi digitado        */
             y = tolower(y) - 'a';         /* Converte o indice da coluna */
             x--;                          /* Converte a linha do indice    */
             if( x>=0 && y>=0 && x<TAM && y<TAM && moves[x][y])
             {
               faz_movim(mapa, x, y, '@');
               conta_moves++;              /* conta movimento */
               break;
             }
             else
               printf("Movimento nao valido digite de novo.\n");
           }
         }
         else                              /* nao valida movimento */
           if(++invalid_moves<2)
           {
             fflush(stdin);
             printf("\nVoce tem q passar precione enter");
             scanf("%c", &repete);
           }
           else
             printf("\n Nem um pode serguir o jogo acabou.\n");
}
     }while(conta_moves < TAM*TAM && invalid_moves<2);

     /* O jogo acabou */
     grade(mapa);  /* mostra grade final*/

     /* a pontuação final e exibida */
     comp_pont = user_pont = 0;
     for(linha = 0; linha < TAM; linha++)
       for(col = 0; col < TAM; col++)
       {
         comp_pont += mapa[linha][col] == '@';
         user_pont += mapa[linha][col] == 'O';
       }
     printf("A pontuacao final e:\n");
     printf("%s %d \n",joga1,user_pont);
     if(escol!=1)
     printf("%s %d \n\n",joga2,comp_pont);
     if(escol==1)
     printf("Computador %d \n\n",comp_pont);

     fflush(stdin);               /* limpa o buffer de entrada */
     printf("Voce quer jogar novamente (y/n): ");
     scanf("%c", &repete);         /* Y para sim N para nao             */
   }while(tolower(repete) == 'y'); /* para ir novamente y         */

   printf("\n tchau \n");
}

/*
 * Função para exibir as casas *
  * Estado atual de linha e coluna *
  * Letras para identificar as casas. *
  * Parâmetro é a matriz bordo
 */

void grade(char mapa[][TAM])
{
   int linha  = 0;          /* linha indice      */
   int col = 0;           /* coluna indice   */
   char col_label = 'a';  /* coluna certa   */

   printf("\n ");         /* comeca a linha superior */
   for(col = 0 ; col<TAM ;col++)
     printf("   %c", col_label+col); /* Mostra a linha superior */
   printf("\n");                     /* fim da linha superior    */

   /* exibir as linhas intermediarias */
   for(linha = 0; linha < TAM; linha++)
   {
     printf("  +");
     for(col = 0; col<TAM; col++)
       printf("---+");
     printf("\n%2d|",linha + 1);

     for(col = 0; col<TAM; col++)
       printf(" %c |", mapa[linha][col]);  /* contador da grade */
     printf("\n");
   }

   printf("  +");                  /* Comeca a linha de fundo  */
   for(col = 0 ; col<TAM ;col++)
     printf("---+");               /* mostra a linha de fundo */
   printf("\n");                   /* fim da linha de fundo    */
}

/*
/* confera quais casas são movimentos válidos *
  * registra movimentos validos para os jogadores *
  * 0 indica um movimento inválido e 1 valido. *
  *um dos principais parâmetro é a matriz movimentos *
  * outro parâmetro identifica o jogador *
  * Retorna contagem movimento válido. *
 */
int valid_moves(char mapa[][TAM], int moves[][TAM], char player)
{
   int linhadelta = 0;     /* Incrementa em uma linha da grade    */
   int coldelta = 0;     /* Incrementa em uma coluna da grade */
   int linha = 0;          /* linha indice                        */
   int col = 0;          /* coluna indice                     */
   int x = 0;            /* indice de linha na busca         */
   int y = 0;            /* indice de coluna na busca      */
   int conta_moves = 0;  /* numero de movimentos validos            */

   /* definir adversario           */
   char opponent = (player == 'O')? '@' : 'O';

   /* Incializa os movimentos com a matriz em 0 */
   for(linha = 0; linha < TAM; linha++)
     for(col = 0; col < TAM; col++)
       moves[linha][col] = 0;

   /* encontra casa para se movimentar.                           */
   /* Um movimento valido deve estar em um quadrado e deve ser anexado */
   /* deve aver pelo menos um quadrado do oponente no meio das duas pecas */
   for(linha = 0; linha < TAM; linha++)
     for(col = 0; col < TAM; col++)
     {
       if(mapa[linha][col] != ' ')   /* e um quadrado vazio  */
         continue;                  /* se nao pode passar para proxima */

       /* verifica todos os quadrados ao redor das casas  */
       /* contar as do adversario                     */
       for(linhadelta = -1; linhadelta <= 1; linhadelta++)
         for(coldelta = -1; coldelta <= 1; coldelta++)
         {
           /* nao marca fora da matriz ou do quadrado atual */
           if(linha + linhadelta < 0 || linha + linhadelta >= TAM ||
              col + coldelta < 0 || col + coldelta >= TAM ||
                                       (linhadelta==0 && coldelta==0))
             continue;

           /* agora verrifica a casa da grade */
           if(mapa[linha + linhadelta][col + coldelta] == opponent)
           {
             /* movese para a direcao delta  */
             /* conta as jogadas do jogador */
             x = linha + linhadelta;                /* move se          */
             y = col + coldelta;                /* casa do adversario  */

             /* procura por uma casa na direcao delta */
             for(;;)
             {
               x += linhadelta;                  /* vai para a proxima casa */
               y += coldelta;                  /* na direcao delta*/

               /* se mover fora da matriz desistir */
               if(x < 0 || x >= TAM || y < 0 || y >= TAM)
                 break;

               /* se encontrar uma casa em branco ir */
               if(mapa[x][y] == ' ')
                 break;
                /*  se a grade tem uma jogada */
                /*  temos movimento valido          */
               if(mapa[x][y] == player)
               {
                 moves[linha][col] = 1;   /* marcar como valido */
                 conta_moves++;         /* aumenta movimentos validos*/
                 break;                 /* verrifica outro quadrado    */
               }
             }
           }
         }
     }
   return conta_moves;
}

/*
* Encontrar a melhor jogada para o computador. *
  * De parâmetro é a matriz contendo movimentos movimentos válidos. *
 */
void computer_move(char mapa[][TAM], int moves[][TAM], char player)
{
   int linha = 0;                          /* linha indice               */
   int col = 0;                          /* coluna indice            */
   int best_linha = 0;                     /* melhor indice da linha          */
   int best_col = 0;                     /* melhor indice da coluna  */
   int i = 0;                            /* repete indice              */
   int j = 0;                            /* repete indice             */
   int new_score = 0;                    /* Contagem para o movimento atual  */
   int score = 100;                      /* pontuação minima do adversario  */
   char temp_mapa[TAM][TAM];          /* copia o local da grade     */
   int temp_moves[TAM][TAM];           /* local da matriz movimento validos */
   char opponent = (player == 'O')? '@' : 'O'; /* indentifica oponente */

   /* passa por todos movimento validos */
   for(linha = 0; linha < TAM; linha++)
     for(col = 0; col < TAM; col++)
     {
       if(moves[linha][col] == 0)
         continue;

       /* primeiro faz copias dos tabuleiros e move as matrizes */
       for(i = 0; i < TAM; i++)
         for(j = 0; j < TAM; j++)
           temp_mapa[i][j] = mapa[i][j];

       /* agora faz o moviemnto no tabuleiro temporario*/
       faz_movim(temp_mapa, linha, col, player);

       /* encontar movimentos validos para o adversario apos o movimento */
       valid_moves(temp_mapa, temp_moves, opponent);

       /* agora encontra melhor jogada para o adversario*/
       new_score = melhor_move(temp_mapa, temp_moves, opponent);

       if(new_score<score)    /* É PIOR?           */
       {                      /* sim para salvar este movimento */
         score = new_score;   /* grava pontuacao */
         best_linha = linha;  /* melhor registro na linha             */
         best_col = col;  /* e na coluna                       */
       }
     }

   /* faca a melhor jogada */
   faz_movim(mapa, best_linha, best_col, player);
}

/*
 * Calcula a contagem para a posição atual  *
  * parametros para identificar o jogador *
  * Valor de retorno é a pontuação. *
 */
int c_pontos(char mapa[][TAM], char player)
{
   int score = 0;      /* pontuação para a posição atual */
   int linha = 0;        /* linha indice                  */
   int col = 0;        /* coluna indice */
   char opponent = player == 'O' ? '@' : 'O';  /* indentifica adversario */

   /* verrefica as casas da grade */
   for(linha = 0; linha < TAM; linha++)
     for(col = 0; col < TAM; col++)
   {
     score -= mapa[linha][col] == opponent; /* diminui para o adversario */
     score += mapa[linha][col] == player;   /* incrementa para o jogador   */
   }
   return score;
}

/*
 * Calcula a pontuação para a melhor jogada  *
  * Para o jogador na posição actual. *
  * Parametros como a matriz que define movimentos movimentos válidos. *
  * outro parâmetro identifica o jogador *
  * A pontuação para a melhor jogada é devolvida *
 */
int melhor_move(char mapa[][TAM], int moves[][TAM], char player)
{
   int linha = 0;     /* linha indice    */
   int col = 0;     /* coluna indice*/
   int i = 0;       /* repete indice   */
   int j = 0;       /* repete coluna   */

   char opponent = player=='O'?'@':'O'; /* indentifica oponente */

   char new_mapa[TAM][TAM] = { 0 };  /* copia     */
   int score = 0;                       /* melhor pontuacao             */
   int new_score = 0;                   /*  contagem para o movimento atual */

   /* Verrifica os movimento validos para encontrar o melhor */
   for(linha = 0 ; linha<TAM ; linha++)
     for(col = 0 ; col<TAM ; col++)
     {
       if(!moves[linha][col])             /* nao a movimento      */
         continue;                      /* veja o proximo        */

       /* copia o conselho */
       for(i = 0 ; i<TAM ; i++)
         for(j = 0 ; j<TAM ; j++)
           new_mapa[i][j] = mapa[i][j];

       /* faz a jogada de copia */
       faz_movim(new_mapa, linha, col, player);

       /* obtem pontuação para o movimento */
       new_score = c_pontos(new_mapa, player);

       if(score<new_score)         /* é melhor?               */
               score = new_score;  /* S salva como melhor pontuação  */
     }
   return score;                   /* retorna melhor pontuação          */
}

/*
 * Faz um movimento.*
  * Todos os contadores do adversário afetadas pelo movimento. *
  * Alguns parâmetros são os índices de linha e coluna. *
  * identifica o jogador. *
 *************/
void faz_movim(char mapa[][TAM], int linha, int col, char player)
{
   int linhadelta = 0;                   /* incrementa linha              */
   int coldelta = 0;                   /* incrementa coluna           */
   int x = 0;                          /* indice da linha para pesquisa    */
   int y = 0;                          /* indice da coluna para pesquisa */
   char opponent = (player == 'O')? '@' : 'O';  /* indentifica oponente */

   mapa[linha][col] = player;           /* coloca o contador jogador   */

   /* verrifica todas as casa em torno desta */
   /* para contar o adversario               */
   for(linhadelta = -1; linhadelta <= 1; linhadelta++)
     for(coldelta = -1; coldelta <= 1; coldelta++)
     {
       /* nao vai para fora da grade ou do espaco atual */
       if(linha + linhadelta < 0 || linha + linhadelta >= TAM ||
          col + coldelta < 0 || col + coldelta >= TAM ||
                               (linhadelta==0 && coldelta== 0))
         continue;

       /* agora verrifica a casa */
       if(mapa[linha + linhadelta][col + coldelta] == opponent)
       {
         /* Se encotrar o adversario pesquisa na mesma direcao*/
         /* conta a jagada                                 */
         x = linha + linhadelta;        /* Movimento do adversario */
         y = col + coldelta;        /*pontuaçao          */

         for(;;)
         {
           x += linhadelta;           /* movese para      */
           y += coldelta;           /* proxima casa      */

           /* se estamos fora do tabuleiro desistir */
           if(x < 0 || x >= TAM || y < 0 || y >= TAM)
             break;

           /* se a casa esta em branco desistir */
           if(mapa[x][y] == ' ')
             break;

           /* se encontar jogada ir para tras */
           /* mudando todos as jogadas adversarias         */
           if(mapa[x][y] == player)
           {
             while(mapa[x-=linhadelta][y-=coldelta]==opponent) /* adversrio? */
               mapa[x][y] = player;    /* sim muda */
             break;                     /* vai ser feito    */
           }
         }
       }
     }
}
