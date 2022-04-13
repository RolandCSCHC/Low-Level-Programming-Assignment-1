#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define X 10
#define Y 10

// Prints the grid
void print_grid(char grid[X][Y])
{
    int i, j;
    printf("   A  B  C  D  E  F  G  H  I  J\n");
    for (i = 0; i < X; i++)
    {
        printf("%d ", i);
        for (j = 0; j < Y; j++)
        {
            printf("[%c]", grid[i][j]);
        }
        printf(" %d\n", i);
    }
    printf("   A  B  C  D  E  F  G  H  I  J\n");
    printf("\n");
}

// Places the mouse and returns his position
int * place_mouse(char grid[X][Y])
{
    time_t t;
    srand((unsigned) time(&t));
    static int mouse_coords[2];
    while (true)
    {
        int mouse_x_coord = rand() % 10;
        int mouse_y_coord = rand() % 10;
        if (grid[mouse_x_coord][mouse_y_coord] != '_')
        {
            continue;
        }
        else
        {
            grid[mouse_x_coord][mouse_y_coord] = 'M';
            mouse_coords[0] = mouse_x_coord;
            mouse_coords[1] = mouse_y_coord;
            return mouse_coords;
        }
    }
}

// Places the cat and returns his position
int * place_cat(char grid[X][Y])
{
    time_t t;
    srand((unsigned) time(&t));
    static int cat_coords[2];
    while (true)
    {
        int cat_x_coord = rand() % 10;
        int cat_y_coord = rand() % 10;
        if (grid[cat_x_coord][cat_y_coord] != '_')
        {
            continue;
        }
        else
        {
            grid[cat_x_coord][cat_y_coord] = 'C';
            cat_coords[0] = cat_x_coord;
            cat_coords[1] = cat_y_coord;
            return cat_coords;
        }
    }
}

// Checks if the coordinates are a valid movement
// UNFINISHED
bool is_valid_movement(char grid[X][Y], char * coord)
{
    int x_coord = coord[0];
    int y_coord = coord[1];
    if (grid[x_coord][y_coord] == 'W')
    {
        return false;
    }
    return true;
}

// Transforms position letter to integer
int letter_to_int(char * letter)
{
    if(strcmp(letter, "A") == 0) {return 0;}
    else if (strcmp(letter, "B") == 0) {return 1;}
    else if (strcmp(letter, "C") == 0) {return 2;}
    else if (strcmp(letter, "D") == 0) {return 3;}
    else if (strcmp(letter, "E") == 0) {return 4;}
    else if (strcmp(letter, "F") == 0) {return 5;}
    else if (strcmp(letter, "G") == 0) {return 6;}
    else if (strcmp(letter, "H") == 0) {return 7;}
    else if (strcmp(letter, "I") == 0) {return 8;}
    else if (strcmp(letter, "J") == 0) {return 9;}
    else {return 9999;}
}

// Transforms position integer to letter
char * int_to_letter(int number)
{
    if (number == 0) {return "A";}
    else if (number == 1) {return "B";}
    else if (number == 2) {return "C";}
    else if (number == 3) {return "D";}
    else if (number == 4) {return "E";}
    else if (number == 5) {return "F";}
    else if (number == 6) {return "G";}
    else if (number == 7) {return "H";}
    else if (number == 8) {return "I";}
    else if (number == 9) {return "J";}
    else {return "ERROR";}
}

// Creates the game
void create_game(char grid[X][Y])
{
    time_t t;
    srand((unsigned) time(&t));
    // Creating the Walls
    // First Wall
    int x_coord_1st_Wall = rand() % 10;
    int y_coord_1st_Wall = rand() % 10;
    // If a wall is in the corner
    while (true)
    {
        if (x_coord_1st_Wall == 0 || y_coord_1st_Wall == 0 || x_coord_1st_Wall == 9 || y_coord_1st_Wall == 9)
        {
            x_coord_1st_Wall = rand() % 10;
            y_coord_1st_Wall = rand() % 10;
        }
        else
        {
            break;
        }
    }
    grid[x_coord_1st_Wall][y_coord_1st_Wall] = 'W';
    // Top Wall
    if (x_coord_1st_Wall == 0 && (y_coord_1st_Wall != 0 && y_coord_1st_Wall != 9))
    {
        int options[3][2] = 
        {
        {0, y_coord_1st_Wall - 1},
        {0, y_coord_1st_Wall + 1},
        {1, y_coord_1st_Wall}
        };
        int random_number = rand() % 3;
        int next_wall_coord[2];
        next_wall_coord[0] = options[random_number][0];
        next_wall_coord[1] = options[random_number][1];
        grid[next_wall_coord[0]][next_wall_coord[1]] = 'W';
    }
    // Bottom Wall
    else if (x_coord_1st_Wall == 9 && (y_coord_1st_Wall != 0 && y_coord_1st_Wall != 9))
    {
        int options[3][2] =
        {
            {9, y_coord_1st_Wall - 1},
            {9, y_coord_1st_Wall + 1},
            {8, y_coord_1st_Wall}
        };
        int random_number = rand() % 3;
        int next_wall_coord[2];
        next_wall_coord[0] = options[random_number][0];
        next_wall_coord[1] = options[random_number][1];
        grid[next_wall_coord[0]][next_wall_coord[1]] = 'W';
    }
    // Left Wall
    else if (y_coord_1st_Wall == 0 && (x_coord_1st_Wall != 0 && x_coord_1st_Wall != 9))
    {
        int options[3][2] = 
        {
            {x_coord_1st_Wall - 1, 0},
            {x_coord_1st_Wall + 1, 0},
            {x_coord_1st_Wall, 1}
        };
        int random_number = rand() % 3;
        int next_wall_coord[2];
        next_wall_coord[0] = options[random_number][0];
        next_wall_coord[1] = options[random_number][1];
        grid[next_wall_coord[0]][next_wall_coord[1]] = 'W';
    }
    // Right Wall
    else if (y_coord_1st_Wall == 9 && (x_coord_1st_Wall != 0 && x_coord_1st_Wall != 9))
    {
        int options[3][2] =
        {
            {x_coord_1st_Wall - 1, 9},
            {x_coord_1st_Wall + 1, 9},
            {x_coord_1st_Wall, 8}
        };
        int random_number = rand() % 3;
        int next_wall_coord[2];
        next_wall_coord[0] = options[random_number][0];
        next_wall_coord[1] = options[random_number][1];
        grid[next_wall_coord[0]][next_wall_coord[1]] = 'W';
    }
    // Middle section
    else if (x_coord_1st_Wall != 0 && x_coord_1st_Wall != 9 && y_coord_1st_Wall != 0 && y_coord_1st_Wall != 9)
    {
        int options[4][2] = 
        {
            {x_coord_1st_Wall, y_coord_1st_Wall - 1},
            {x_coord_1st_Wall, y_coord_1st_Wall + 1},
            {x_coord_1st_Wall - 1, y_coord_1st_Wall},
            {x_coord_1st_Wall + 1, y_coord_1st_Wall}
        };
        int random_number = rand() % 4;
        int next_wall_coord[2];
        next_wall_coord[0] = options[random_number][0];
        next_wall_coord[1] = options[random_number][1];
        grid[next_wall_coord[0]][next_wall_coord[1]] = 'W';
    }
    // Second Wall
    int x_coord_2nd_Wall = rand() % 10;
    int y_coord_2nd_Wall = rand() % 10;
    // If Walls cross each other
    while (true)
    {
        if (x_coord_1st_Wall == x_coord_2nd_Wall || y_coord_1st_Wall == y_coord_2nd_Wall)
        {
           x_coord_2nd_Wall = rand() % 10;
           y_coord_2nd_Wall = rand() % 10;
        }
        else
        {
            break;
        }
    }
    // If a wall is in the corner
    while (true)
    {
        if (x_coord_2nd_Wall == 0 || y_coord_2nd_Wall == 0 || x_coord_2nd_Wall == 9 || y_coord_2nd_Wall == 9)
        {
            x_coord_2nd_Wall = rand() % 10;
            y_coord_2nd_Wall = rand() % 10;
        }
        else
        {
            break;
        }
    }
    grid[x_coord_2nd_Wall][y_coord_2nd_Wall] = 'W';
    // Top Wall
    if (x_coord_2nd_Wall == 0 && (y_coord_2nd_Wall != 0 && y_coord_2nd_Wall != 9))
    {
        int options[3][2] = 
        {
        {0, y_coord_2nd_Wall - 1},
        {0, y_coord_2nd_Wall + 1},
        {1, y_coord_2nd_Wall}
        };
        int random_number = rand() % 3;
        int next_wall_coord[2];
        next_wall_coord[0] = options[random_number][0];
        next_wall_coord[1] = options[random_number][1];
        grid[next_wall_coord[0]][next_wall_coord[1]] = 'W';
    }
    // Bottom Wall
    else if (x_coord_2nd_Wall == 9 && (y_coord_2nd_Wall != 0 && y_coord_2nd_Wall != 9))
    {
        int options[3][2] =
        {
            {9, y_coord_2nd_Wall - 1},
            {9, y_coord_2nd_Wall + 1},
            {8, y_coord_2nd_Wall}
        };
        int random_number = rand() % 3;
        int next_wall_coord[2];
        next_wall_coord[0] = options[random_number][0];
        next_wall_coord[1] = options[random_number][1];
        grid[next_wall_coord[0]][next_wall_coord[1]] = 'W';
    }
    // Left Wall
    else if (y_coord_2nd_Wall == 0 && (x_coord_2nd_Wall != 0 && x_coord_2nd_Wall != 9))
    {
        int options[3][2] = 
        {
            {x_coord_2nd_Wall - 1, 0},
            {x_coord_2nd_Wall + 1, 0},
            {x_coord_2nd_Wall, 1}
        };
        int random_number = rand() % 3;
        int next_wall_coord[2];
        next_wall_coord[0] = options[random_number][0];
        next_wall_coord[1] = options[random_number][1];
        grid[next_wall_coord[0]][next_wall_coord[1]] = 'W';
    }
    // Right Wall
    else if (y_coord_2nd_Wall == 9 && (x_coord_2nd_Wall != 0 && x_coord_2nd_Wall != 9))
    {
        int options[3][2] =
        {
            {x_coord_2nd_Wall - 1, 9},
            {x_coord_2nd_Wall + 1, 9},
            {x_coord_2nd_Wall, 8}
        };
        int random_number = rand() % 3;
        int next_wall_coord[2];
        next_wall_coord[0] = options[random_number][0];
        next_wall_coord[1] = options[random_number][1];
        grid[next_wall_coord[0]][next_wall_coord[1]] = 'W';
    }
    // Middle section
    else if (x_coord_2nd_Wall != 0 && x_coord_2nd_Wall != 9 && y_coord_2nd_Wall != 0 && y_coord_2nd_Wall != 9)
    {
        int options[4][2] = 
        {
            {x_coord_2nd_Wall, y_coord_2nd_Wall - 1},
            {x_coord_2nd_Wall, y_coord_2nd_Wall + 1},
            {x_coord_2nd_Wall - 1, y_coord_2nd_Wall},
            {x_coord_2nd_Wall + 1, y_coord_2nd_Wall}
        };
        int random_number = rand() % 4;
        int next_wall_coord[2];
        next_wall_coord[0] = options[random_number][0];
        next_wall_coord[1] = options[random_number][1];
        grid[next_wall_coord[0]][next_wall_coord[1]] = 'W';
    }
}

int main(int argc, char *argv[]) {

    // Two lines to get rid of 'unused variable' error.
    (void)argv;
    (void)argc;

    char grid[X][Y] = {
        {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', },
        {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', },
        {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', },
        {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', },
        {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', },
        {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', },
        {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', },
        {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', },
        {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', },
        {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', }
        };
        
    printf("\nWelcome to the Cat and Mouse Game!\n");
    printf("----------------------------------\n");

    // Choosing game mode.
    char game_mode[3];
    while (true)
    {   
        printf("In what game mode you want to play? (-v for VERSUS or -a for AUTOMATED): ");
        gets(game_mode);
        if (strncmp(game_mode, "-v", 3) == 0)
        {
            printf("You have picked: Versus mode!\n\n");
            break;
        }
        else if (strncmp(game_mode, "-a", 3) == 0)
        {
            printf("You have picked: Automated mode!\n\n");
            break;
        }    
        else
        {
            printf("Invalid command. Try again.\n");
        }
    }
    // Creating the game.
    create_game(grid);
    int * mouse_pos = place_mouse(grid);
    int * cat_pos = place_cat(grid);
    int mouse_points = 0;
    bool cat_wins = false;
    bool used_freeze = false;
    //char * cat_turn = "Cat's turn.";
    char * mouse_turn = "Mouse's turn.";
    
    // The game begins
    while (true)
    {
        // Versus mode
        if (strncmp(game_mode, "-v", 3) == 0)
        {
            while (mouse_points != 5)
            {
                printf("Mouse position: X:%d Y:%d\n", mouse_pos[0], mouse_pos[1]);
                printf("Cat position: X:%d Y:%d\n", cat_pos[0], cat_pos[1]);
                print_grid(grid);
                printf("Mouse Points: %d\n\n", mouse_points);
                printf("It's %s\n", mouse_turn);
                printf("Where do you want to move?: ");
                // Asking where to move
                char user_coord[20];
                fgets(user_coord, 20, stdin);
                char *token = strtok(user_coord, ",");
                int *user_tokens[20];
                bool is_frozen = false;
                int i = 0;
                while (token != NULL)
                {
                    // printf("A\n");
                    // printf("%s\n", token);
                    // printf("B\n");
                    printf("index: %d\n", i);
                    *user_tokens[i] = atoi(token);
                    // printf("C\n");
                    token = strtok(NULL, " ");
                    // printf("token: %s\n", token);
                    // printf("D\n");
                    i ++;
                }
                printf("hola\n");
                printf("x: %d y: %d f: %d\n", *user_tokens[0], *user_tokens[1], *user_tokens[2]);
                // Validating the coordinates
                while (*user_tokens[0] > 9 || *user_tokens[0] < 0 || *user_tokens[1] > 9 || *user_tokens[1] < 0)
                {
                    printf("Invalid coordinate.\n");
                    printf("Where do you want to move?: ");
                    char user_coord[15];
                    fgets(user_coord, 15, stdin);
                    char * token = strtok(user_coord, ",");
                    int i = 0;
                    while (token != NULL)
                    {
                        printf("%s\n", token);
                        printf("chao\n");
                        *user_tokens[i] = atoi(token);
                        token = strtok(NULL, " ");
                        i ++;
                    }
                    printf("x: %d y: %d\n", *user_tokens[0], *user_tokens[1]);
                }
                if (used_freeze)
                {
                    printf("You already used your freeze power!\n");
                }
                if ((int)*user_tokens[2] == 0 && is_frozen == false)
                {
                    printf("You have frozen the mouse!\n");
                    is_frozen = true;
                    used_freeze = true;
                    *user_tokens[2] = -1;
                }
                printf("--------\n");
                printf("Coord X: %d Coord Y: %d\n", *user_tokens[0], *user_tokens[1]);
                printf("--------\n");
                // int user_number_answer;
                // printf("Please enter a number: ");
                // scanf("%d", &user_number_answer);
                // char * user_letter = int_to_letter(user_number_answer);
                // printf("The number %d is the letter %s.\n", user_number_answer, user_letter);  
                
                char user_letter_answer[15];
                printf("Please enter a letter: ");
                scanf("%[^\n]%*c", user_letter_answer);
                // fgets(user_letter_answer, 3, stdin);
                printf("The letter is %s\n", user_letter_answer);
                int user_number = letter_to_int(user_letter_answer);
                printf("The letter %s is the number %d.\n", user_letter_answer, user_number);              
                

                // When the game ends
                if (cat_wins)
                {
                    break;
                }
                mouse_points ++;
            }
        }
        else if (strncmp(game_mode, "-a", 3) == 0)
        {
            printf("I'm sorry, Automated mode not yet implemented.\n\n");
            break;
        }
        else
        {
            break;
        }
        break;
    }
    // printf("Mouse position: X:%d Y:%d\n", mouse_pos[0], mouse_pos[1]);
    // printf("Cat position: X:%d Y:%d\n", cat_pos[0], cat_pos[1]);
    // print_grid(grid);
    // printf("Mouse Points: %d\n\n", mouse_points);
    if (mouse_points == 5)
    {
        printf("The mouse has won!");
    }
    else if (cat_wins)
    {
        printf("The cat has won!");
    }
    printf("ARGH!\n");
    return 0;
}