#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 100
#define MAX_ROW_SIZE 100
#define MAX_COL_SIZE 100

typedef struct
{
    int width;
    int height;
    char map[MAX_ROW_SIZE][MAX_COL_SIZE];
    int flower_x;
    int flower_y;
} Forest;

typedef struct
{
    int coord_x;
    int coord_y;
    int numb_of_bottle;
    int numb_of_collect_flw;
} Botanist;

void end(Forest *forest, Botanist *botanist)
{

    FILE *file = fopen("last.txt", "w");
    if (file == NULL)
    {
        printf("The file does not exist\n");
    }
    int i = 0;
    int j = 0;

    for (i = 0; i < forest->height; i++)
    {
        for (j = 0; j < forest->width; j++)
        {
            fprintf(file, "%c,", forest->map[i][j]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "Botanist: (%d,%d)\n", botanist->coord_x, botanist->coord_y);
    fprintf(file, "Number of the bottle:%d\n", botanist->numb_of_bottle);
    fprintf(file, "Number of the collected flowers:%d\n", botanist->numb_of_collect_flw);

    fclose(file);
}
int is_done(Forest *forest, Botanist *botanist)
{

    int i = 0;
    int j = 0;
    int flag = 0;

    for (i = 0; i < forest->height; i++)
    {
        for (j = 0; j < forest->width; j++)
        {

            if (forest->map[i][j] == 'X')
            {
                flag = 1;
            }
        }
    }

    return flag;
}
void init_game(Forest *forest, Botanist *botanist)
{

    FILE *file = fopen("init.txt", "r");

    if (file == NULL)
    {
        printf("The file does not exist\n");
    }

    char line[MAX_LINE_LENGTH];

    fgets(line, MAX_LINE_LENGTH, file);
    sscanf(line, "%d,%d", &forest->height, &forest->width);
    printf("%d,%d\n", forest->height, forest->width);

    fgets(line, MAX_LINE_LENGTH, file);
    sscanf(line, "%d,%d,%d", &botanist->coord_x, &botanist->coord_y, &botanist->numb_of_bottle);
    printf("%d,%d,%d\n", botanist->coord_x, botanist->coord_y, botanist->numb_of_bottle);

    char ch;
    int row = 0;
    int col = 0;

    while (fscanf(file, "%c", &ch) != EOF)
    {
        if (ch == '\n')
        {
            row++;
            col = 0;
        }

        else
        {
            if (ch == ',')
            {
                continue;
            }

            forest->map[row][col] = ch;

            if (ch == 'X')
            {
                forest->flower_x = row;
                forest->flower_y = col;
            }

            else if (ch == 'B')
            {
                botanist->coord_x = row;
                botanist->coord_y = col;
            }

            col++;
        }
    }

    fclose(file);
}

void display_forest(Forest *forest, Botanist *botanist)
{

    int i = 0;
    int j = 0;

    for (i = 0; i < forest->height; i++)
    {
        for (j = 0; j < forest->width; j++)
        {
            printf("%c", forest->map[i][j]);
            if (j < forest->width - 1)
            {
                printf(",");
            }
        }
        printf("\n");
    }

    printf("Botanist: (%d,%d)\n", botanist->coord_x, botanist->coord_y);
    printf("Number of the bottle:%d\n", botanist->numb_of_bottle);
}

void search(Forest *forest, Botanist *botanist, int x, int y)
{
    if (is_done(forest, botanist) == 0)
    {
        printf("Flowers collected\n");
        printf("Number of the collected flowers:%d\n", botanist->numb_of_collect_flw);
        end(forest, botanist);
        exit(1);
    }
    char direction;
    printf("enter first move\n");
    scanf(" %c", &direction);

    switch (direction)
    {
    case 'w':
        if (forest->map[botanist->coord_x - 1][botanist->coord_y] == ' ')
        {
            forest->map[botanist->coord_x][botanist->coord_y] = ' ';
            forest->map[botanist->coord_x - 1][botanist->coord_y] = 'B';
            botanist->coord_x--;
        }
        else if (forest->map[botanist->coord_x - 1][botanist->coord_y] == 'X')
        {
            forest->map[botanist->coord_x][botanist->coord_y] = ' ';
            forest->map[botanist->coord_x - 1][botanist->coord_y] = 'B';
            botanist->coord_x--;
            botanist->numb_of_bottle--;
            botanist->numb_of_collect_flw++;
        }
        else
            printf("Can't move \n");
        break;

    case 'a':
        if (forest->map[botanist->coord_x][botanist->coord_y - 1] == ' ')
        {
            forest->map[botanist->coord_x][botanist->coord_y] = ' ';
            forest->map[botanist->coord_x][botanist->coord_y - 1] = 'B';
            botanist->coord_y--;
        }
        else if (forest->map[botanist->coord_x][botanist->coord_y - 1] == 'X')
        {
            forest->map[botanist->coord_x][botanist->coord_y] = ' ';
            forest->map[botanist->coord_x][botanist->coord_y - 1] = 'B';
            botanist->coord_y--;
            botanist->numb_of_bottle--;
            botanist->numb_of_collect_flw++;
        }
        else
            printf("Can't move\n");
        break;
    case 's':
        if (forest->map[botanist->coord_x + 1][botanist->coord_y] == ' ')
        {
            forest->map[botanist->coord_x][botanist->coord_y] = ' ';
            forest->map[botanist->coord_x + 1][botanist->coord_y] = 'B';
            botanist->coord_x++;
        }
        else if (forest->map[botanist->coord_x + 1][botanist->coord_y] == 'X')
        {
            forest->map[botanist->coord_x][botanist->coord_y] = ' ';
            forest->map[botanist->coord_x + 1][botanist->coord_y] = 'B';
            botanist->coord_x++;
            botanist->numb_of_bottle--;
            botanist->numb_of_collect_flw++;
        }
        else
            printf("Can't move \n");
        break;
    case 'd':
        if (forest->map[botanist->coord_x][botanist->coord_y + 1] == ' ')
        {
            forest->map[botanist->coord_x][botanist->coord_y] = ' ';
            forest->map[botanist->coord_x][botanist->coord_y + 1] = 'B';
            botanist->coord_y++;
        }
        else if (forest->map[botanist->coord_x][botanist->coord_y + 1] == 'X')
        {
            forest->map[botanist->coord_x][botanist->coord_y] = ' ';
            forest->map[botanist->coord_x][botanist->coord_y + 1] = 'B';
            botanist->coord_y++;
            botanist->numb_of_bottle--;
            botanist->numb_of_collect_flw++;
        }
        else
            printf("Can't move \n");
        break;
    case 'e':
        end(forest, botanist);
        exit(1);
        break;
    default:

        printf("Warning\n");
        break;
    }
    display_forest(forest, botanist);
    search(forest, botanist, x, y);
}

int main()
{
    Forest forest;
    Botanist botanist;
    botanist.numb_of_collect_flw = 0;

    init_game(&forest, &botanist);
    display_forest(&forest, &botanist);
    search(&forest, &botanist, botanist.coord_x, botanist.coord_y);
    return 0;
}
