#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <ncurses.h>

#define GRID_WIDTH 40
#define GRID_HEIGHT 10

//int grid[GRID_WIDTH][GRID_HEIGHT];

int pos_y[25], pos_x[25];

int fruit_x=5, fruit_y =5;

int direction = 0;

int snake_body_lenght = 0;

int draw_grid(int width_param, int height_param)
{

bool draw = false;

printw("\n Aperte WASD para controlar ou Q para sair");


    for (int x = 0;  x <= height_param ; x++)
    {
        printw("\n ");
        for(int y = 0 ; y <= width_param ; y++)
        {
            //desenha borda
            if( x == 0 || x == height_param )
            {
                printw("-");
                draw=true;

            }else if( y == 0 || y == width_param)
            {
                printw("|");
                draw=true;
            }
            //desenha cabeça
            else if( x == pos_x[0] && y == pos_y[0])
            {
                printw("@");
                draw=true;
            }
            //desenha fruta
            else if(x == fruit_x && y == fruit_y)
            {
                printw("o");
                draw=true;
            }
            //desenha corpo
            else if(snake_body_lenght > 0)
            {
                for (int l = snake_body_lenght ; l > 0  ; l--)
                {
                    if (x == pos_x[l] && y == pos_y[l])
                    {
                        printw("0");
                        draw=true;
                        break;
                    }
                }
            }

            if (draw==false)
            {
                printw(" ");

            }

            draw=false;
        }

    }

    printw("\n");
    printw("Pontos %i", snake_body_lenght);
    return 0;
}


bool player_input()
{
    char key_pressed = getch();
    switch(key_pressed)
    {
        case 'w':
            direction = 0;
            break;
        case 's':
            direction = 1;
            break;
        case 'a':
            direction = 2;
            break;
        case 'd':
            direction = 3;
            break;
        case 'q':
            return false;
            break;
    }

    return true;
}

void move_player()
{
    for(int l = snake_body_lenght ; l > 0; l--)
    {
        pos_x[l]=pos_x[l-1];
        pos_y[l]=pos_y[l-1];
    }

    switch(direction)
    {
        case 0:
            pos_x[0]-=1;
            break;

        case 1:
            pos_x[0]+=1;
            break;

        case 2:
            pos_y[0]-=1;
            break;

        case 3:
            pos_y[0]+=1;
            break;
    }
}

bool check_game_over()
{
    if(pos_y[0] > GRID_WIDTH-1 || pos_y[0] < 1 || pos_x[0] > GRID_HEIGHT-1 || pos_x[0] < 1)
    {
        printw("Game OVER");
        return true;
    }
    else
    {
        // primeiro verifica se tem tamanho suficiente para evitar loop desnecessário
        if (snake_body_lenght > 3 )
        {
            // se a cobra for maior que 3, então verifica a colisão com o corpo
            // começando por 1 (inicio do corpo) ate o snake_lenght
            for(int l = 1 ; l <= snake_body_lenght ; l++)
            {
                if ( pos_x[0] == pos_x[l] && pos_y[0] == pos_y[l] )
                {
                    printw("Game OVER");
                    return true;
                }
            }
        }


    }
    return false;
}

void check_eat_fruit()
{
    // verifica se cabeça colidio com a fruta
    if(pos_x[0] == fruit_x && pos_y[0] == fruit_y)
    {
        // aumenta o corpo da cobra
        snake_body_lenght +=1;

        // se a nova localização for no mesmo lugar da cabeça, gera uma nova posição
        while(pos_x[0] == fruit_x && pos_y[0] == fruit_y)
        {
             // Gera um número aleatório entre 'min =1' e 'max = GRID-1'
            fruit_x = 1 + ( rand() % ((GRID_HEIGHT - 1) )) ;
            fruit_y = 1 + ( rand() % ((GRID_WIDTH - 1 ) )) ;
        }
    }
}
//programa principal
int main(void)
{

//habilitar timer para numeros aleatorios
srand(time(0));

//define posição inicial da cobra
pos_y[0] = 3;
pos_x[0] = 3;

// define game over falso
bool running = true;

//inicia tela para desenho
initscr();

printw("\n *********************************************" );
printw("\n *    SNAKE C                                *");
printw("\n *   by gr4v4t1nh4                           *");
printw("\n ********************************************* ");
printw("\n");
printw("\n [    pressione qualquer tecla para iniciar   ]");



getch();

//game loop
while(running == true)
{

    //limpa tela
    clear();
    //desenha a tela
    draw_grid(GRID_WIDTH, GRID_HEIGHT);
    refresh();

    //verifica tecla pressionada
    running = player_input() ;

    //atualiza personagens
    move_player();

    //verifica se colidiu com parede ou corpo
    if (check_game_over())
    {
        clear();
        running = false;
        printw("\n # you lose ###");
        getch();
    };

    //verifica se comeu fruta
    check_eat_fruit();



};

endwin();

return 0;
}
