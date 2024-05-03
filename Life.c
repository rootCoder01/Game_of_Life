//Game_Of_Life

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

#define Cols_Size 120
#define Rows_Size 30

int static GLOBAL_ROWS, GLOBAL_COLUMNS;

int **Matrix_Assignment(int Rows, int Columns);

int AllocationMethod();

int ExecutionMethod();

void Manual_Assignment(int **);

void Random_Assignment(int **, int Rows, int Columns);

void Evaluator(int **, int Rows, int Columns);

int Live(int **, int Row, int Column);

void Print_Matrix(int **, int Rows, int Columns);

void Loading();

void gotoxy(int x, int y);

void DisableCursor();

void EnableCursor();

int main() {
    int **Main_Matrix;
    int Option = 0, Start = 0;
    system("cls");
    system("mode con: cols=Cols_Size lines=Rows_Size");
    Loading();
    system("cls");
    gotoxy((Cols_Size / 2) - (33 / 2), (Rows_Size / 2) - 5);
    printf(" _________________________________");
    gotoxy((Cols_Size / 2) - (33 / 2), (Rows_Size / 2) - 4);
    printf("%c                                 %c", 179, 179);
    gotoxy((Cols_Size / 2) - (33 / 2), (Rows_Size / 2) - 3);
    printf("%c      [ Matrix Assignment ]      %c", 179, 179);
    gotoxy((Cols_Size / 2) - (33 / 2), (Rows_Size / 2) - 2);
    printf("%c_________________________________%c", 179, 179);
    gotoxy((Cols_Size / 2) - (33 / 2), (Rows_Size / 2) - 1);
    printf("%c                                 %c", 179, 179);
    gotoxy((Cols_Size / 2) - (33 / 2), Rows_Size / 2);
    printf("%c    Assign No. of Rows:          %c", 179, 179);
    gotoxy((Cols_Size / 2) - (33 / 2), (Rows_Size / 2) + 1);
    printf("%c    Assign No. of Columns:       %c", 179, 179);
    gotoxy((Cols_Size / 2) - (33 / 2), (Rows_Size / 2) + 2);
    printf("%c_________________________________%c", 179, 179);
    gotoxy((Cols_Size / 2) + 9, Rows_Size / 2);
    scanf("%i", &GLOBAL_ROWS);
    gotoxy((Cols_Size / 2) + 12, (Rows_Size / 2) + 1);
    scanf("%i", &GLOBAL_COLUMNS);
    system("cls");
    Main_Matrix = Matrix_Assignment(GLOBAL_ROWS, GLOBAL_COLUMNS);
    for(;;){
        Option = AllocationMethod();
        switch (Option) {
            case 1:
                system("cls");
                Manual_Assignment(Main_Matrix);
                break;

            case 2:
                system("cls");
                Random_Assignment(Main_Matrix, GLOBAL_ROWS, GLOBAL_COLUMNS);
                break;

            default:
                break;
        }
        Start = ExecutionMethod();
        switch (Start) {
            case 1:
                Print_Matrix(Main_Matrix, GLOBAL_ROWS, GLOBAL_COLUMNS);
                system("pause");
                DisableCursor();
                for (int i = 0; i < 30; i++) {
                    Evaluator(Main_Matrix, GLOBAL_ROWS, GLOBAL_COLUMNS);
                    Print_Matrix(Main_Matrix, GLOBAL_ROWS, GLOBAL_COLUMNS);
                    Sleep(500);
                }
                EnableCursor();
                break;

            case 2:
                Print_Matrix(Main_Matrix, GLOBAL_ROWS, GLOBAL_COLUMNS);
                system("pause");
                for (int i = 0; i < 30; i++) {
                    Evaluator(Main_Matrix, GLOBAL_ROWS, GLOBAL_COLUMNS);
                    Print_Matrix(Main_Matrix, GLOBAL_ROWS, GLOBAL_COLUMNS);
                    system("pause");
                }
                break;

            default:
                break;
        }
        char Key;
        while(1){
            DisableCursor();
            system("cls");
            gotoxy((Cols_Size / 2) - (29 / 2), (Rows_Size / 2) - 1); 
            printf(" ___________________________ ");
            gotoxy((Cols_Size / 2) - (29 / 2),  Rows_Size / 2); 
            printf("%c                           %c", 179, 179);
            gotoxy((Cols_Size / 2) - (29 / 2), (Rows_Size / 2) + 1); 
            printf("%c   Back Menu   Exit Game   %c", 179, 179);
            gotoxy((Cols_Size / 2) - (29 / 2), (Rows_Size / 2) + 2); 
            printf("%c    [ <%c%c ]     [ esc ]    %c", 179, 196, 196 , 179);
            gotoxy((Cols_Size / 2) - (29 / 2), (Rows_Size / 2) + 3); 
            printf("%c___________________________%c", 179, 179);
            gotoxy((Cols_Size / 2) - (29 / 2), (Rows_Size / 2) + 4);
            Key = getch();
            if (Key == 8)
                break;
            else if(Key == 27)
                exit(1);
            EnableCursor();
        }
    }
    for (int i = 0; i < GLOBAL_ROWS; i++) {
        free(Main_Matrix[i]);
    }
    free(Main_Matrix);
    return 0;
}

int **Matrix_Assignment(int Rows, int Columns) {
    int **Matrix;
    Matrix = (int **) calloc(Rows, sizeof(int *));
    for (int i = 0; i < Rows; i++) {
        Matrix[i] = (int *) calloc(Columns, sizeof(int));
    }
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Columns; j++) {
            Matrix[i][j] = 0;
        }
    }
    return Matrix;
}

void Manual_Assignment(int **Matrix) {
    char Option;
    int Row = 0, Column = 0;
    for (;;) {
        system("cls");
        Print_Matrix(Matrix, GLOBAL_ROWS, GLOBAL_COLUMNS);
        printf("\n >");
        scanf("%i,%i", &Row, &Column);
        Matrix[Row][Column] = 1;
        printf("\n Add another element? [Y/N]");
        fflush(stdin);
        scanf("%c", &Option);
        if (Option == 'N' || Option == 'n')
            break;
    }
}

void Random_Assignment(int **Matrix, int Rows, int Columns) {
    srand(time(NULL));
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Columns; j++) {
            Matrix[i][j] = 0 + rand() % 2;
        }
    }
}

void Evaluator(int **Matrix, int Rows, int Columns) {
    int Copy[Rows][Columns];
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Columns; j++) {
            int living_temp = Live(Matrix, i, j);
            int status = living_temp == 2 ? Matrix[i, j] == 1 : living_temp == 3;
            Copy[i][j] = status;
        }
    }
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Columns; j++) {
            Matrix[i][j] = Copy[i][j];
        }
    }
}

int Live(int **Element, int Row, int Column) {
    int LivingCells = 0;
    for (int i = 0; i < 3; i++) {
        if (Row == 0 && i == 2) break;
        if (Row == GLOBAL_ROWS - 1 && i == 0) continue;
        for (int j = 0; j < 3; j++) {
            if (i == 1 && j == 1) continue;
            int row_temp = Row + 1 - i;
            int col_temp = Column + 1 - j;
            if (Column == 0 && j == 2) break;
            if (Column == GLOBAL_COLUMNS && j == 0) continue;
            if (Element[Row + 1 - i][Column + 1 - j] == 1) LivingCells++;
        }
    }
    return LivingCells;
}

int AllocationMethod() {
    int Option = 0;
    system("cls");
    gotoxy((Cols_Size / 2) - (44 / 2), (Rows_Size / 2) - 6);
    printf(" __________________________________________");
    gotoxy((Cols_Size / 2) - (44 / 2), (Rows_Size / 2) - 5);
    printf("%c                                          %c", 179, 179);
    gotoxy((Cols_Size / 2) - (44 / 2), (Rows_Size / 2) - 4);
    printf("%c       [ Select Allocation Method ]       %c", 179, 179);
    gotoxy((Cols_Size / 2) - (44 / 2), (Rows_Size / 2) - 3);
    printf("%c__________________________________________%c", 179, 179);
    gotoxy((Cols_Size / 2) - (44 / 2), (Rows_Size / 2) - 2);
    printf("%c                                          %c", 179, 179);
    gotoxy((Cols_Size / 2) - (44 / 2), (Rows_Size / 2) - 1);
    printf("%c 1). Initial State Assignment (Manually)  %c", 179, 179);
    gotoxy((Cols_Size / 2) - (44 / 2), Rows_Size / 2);
    printf("%c 2). Initial State Assignment (Randomly)  %c", 179, 179);
    gotoxy((Cols_Size / 2) - (44 / 2), (Rows_Size / 2) + 1);
    printf("%c                                          %c", 179, 179);
    gotoxy((Cols_Size / 2) - (44 / 2), (Rows_Size / 2) + 2);
    printf("%c           > Enter an Option:             %c", 179, 179);
    gotoxy((Cols_Size / 2) - (44 / 2), (Rows_Size / 2) + 3);
    printf("%c                                          %c", 179, 179);
    gotoxy((Cols_Size / 2) - (44 / 2), (Rows_Size / 2) + 4);
    printf("%c__________________________________________%c", 179, 179);
    gotoxy((Cols_Size / 2) + 9, (Rows_Size / 2) + 2);
    scanf("%i", &Option);
    return Option;
}

int ExecutionMethod() {
    int Option = 0;
    system("cls");
    gotoxy((Cols_Size / 2) - (27 / 2), (Rows_Size / 2) - 6);
    printf(" __________________________");
    gotoxy((Cols_Size / 2) - (27 / 2), (Rows_Size / 2) - 5);
    printf("%c                          %c", 179, 179);
    gotoxy((Cols_Size / 2) - (27 / 2), (Rows_Size / 2) - 4);
    printf("%c   [ Execution Method ]   %c", 179, 179);
    gotoxy((Cols_Size / 2) - (27 / 2), (Rows_Size / 2) - 3);
    printf("%c__________________________%c", 179, 179);
    gotoxy((Cols_Size / 2) - (27 / 2), (Rows_Size / 2) - 2);
    printf("%c                          %c", 179, 179);
    gotoxy((Cols_Size / 2) - (27 / 2), (Rows_Size / 2) - 1);
    printf("%c   1). Auto Execution     %c", 179, 179);
    gotoxy((Cols_Size / 2) - (27 / 2), Rows_Size / 2);
    printf("%c   2). Manual Execution   %c", 179, 179);
    gotoxy((Cols_Size / 2) - (27 / 2), (Rows_Size / 2) + 1);
    printf("%c                          %c", 179, 179);
    gotoxy((Cols_Size / 2) - (27 / 2), (Rows_Size / 2) + 2);
    printf("%c   > Enter an Option:     %c", 179, 179);
    gotoxy((Cols_Size / 2) - (27 / 2), (Rows_Size / 2) + 3);
    printf("%c                          %c", 179, 179);
    gotoxy((Cols_Size / 2) - (27 / 2), (Rows_Size / 2) + 4);
    printf("%c__________________________%c", 179, 179);
    gotoxy((Cols_Size / 2) + 9, (Rows_Size / 2) + 2);
    scanf("%i", &Option);
    return Option;
}

void Print_Matrix(int **Matrix, int Rows, int Columns) {
    system("cls");
    char Print_Matrix[Rows][Columns];
    gotoxy((Cols_Size / 2) - (43 / 2), 1);
    printf("%c%c%c %c%c%c %c%c%c%c%c %c%c%c   %c%c%c %c%c%c   %c   %c %c%c%c %c%c%c", 
            219, 223, 223, 220, 223, 219, 219, 223, 220, 223, 219, 219, 223, 223, 219,
            223, 219, 219, 223, 223, 219, 219, 219, 223, 223, 219, 223, 223);
    gotoxy((Cols_Size / 2) - (43 / 2), 2);
    printf("%c%c%c %c%c%c %c %c %c %c%c%c   %c%c%c %c%c    %c%c%c %c %c%c  %c%c%c", 
            219, 220, 219, 219, 223, 219, 219, 223, 219, 219, 219, 220, 219, 220, 219, 
            219, 223, 219, 220, 220, 219, 219, 223, 219, 219, 220);
    gotoxy(((Cols_Size / 2) - (((Columns * 3) + 4)) / 2), 4);
    printf("%c", 201);
    for (int Upper = 0; Upper < Columns * 3; Upper++) {
        printf("%c", 205);
    }
    printf("%c%c%c", 205, 205, 187);
    for (int i = 0; i < Rows; i++) {
        gotoxy(((Cols_Size / 2) - (((Columns * 3) + 4)) / 2), i + 5);
        printf("%c ", 186);
        for (int j = 0; j < Columns; j++) {
            if (Matrix[i][j])
                Print_Matrix[i][j] = 254;
            else
                Print_Matrix[i][j] = ' ';
            printf("[%c]", Print_Matrix[i][j]);
        }
        printf(" %c", 186);
        gotoxy(((Cols_Size / 2) - (((Columns * 3) + 4)) / 2), Rows + 5);
    }
    printf("%c", 200);
    for (int Lower = 0; Lower < Columns * 3; Lower++) {
        printf("%c", 205);
    }
    printf("%c%c%c", 205, 205, 188);
    gotoxy((Cols_Size / 2) - (40 / 2), Rows + 8);
}

void Loading() {
    system("cls");
    disableCursor();
    gotoxy((Cols_Size / 2) - (16 / 2), (Rows_Size / 2) - 1);
    printf("L o a d i n g . . .");
    gotoxy((Cols_Size / 2) - (45 / 2), Rows_Size / 2);
    printf("%c%c", 201, 205);
    for (int Upper = 0; Upper < 43; Upper++) {
        printf("%c", 205);
    }
    printf("%c%c", 205, 187);
    gotoxy((Cols_Size / 2) - (45 / 2), (Rows_Size / 2) + 1);
    printf("%c ", 186);
    for (int i = 0; i < 43; i++) {
        gotoxy(((Cols_Size / 2) - (40 / 2)) + i, (Rows_Size / 2) + 1);
        {
            printf(" ");
        }
        printf(" %c", 186);
        gotoxy((Cols_Size / 2) - (45 / 2), (Rows_Size / 2) + 2);
    }
    printf("%c%c", 200, 205);

    for (int Lower = 0; Lower < 43; Lower++) {
        printf("%c", 205);
    }
    printf("%c%c", 205, 188);
    DisableCursor();
    for (int i = 0; i < 43; i++) {
        gotoxy(((Cols_Size / 2) - (40 / 2)) + i, (Rows_Size / 2) + 1);
        {
            printf("%c", 219);
            Sleep(33);
        }
        gotoxy((Cols_Size / 2) - (45 / 2), (Rows_Size / 2) + 2);
    }
    EnableCursor();
    gotoxy((Cols_Size / 2) - (3 / 2), (Rows_Size / 2) - 6);
    printf("  %c%c  ", 219, 219);
    gotoxy((Cols_Size / 2) - (3 / 2), (Rows_Size / 2) - 5);
    printf("    %c%c", 219, 219);
    gotoxy((Cols_Size / 2) - (3 / 2), (Rows_Size / 2) - 4);
    printf("%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219);
    gotoxy((Cols_Size / 2) - (16 / 2), (Rows_Size / 2) - 1);
    printf("  C O M P L E T E   ");
    gotoxy((Cols_Size / 2) - (38 / 2), (Rows_Size / 2) + 4);
    system("pause");
}

void gotoxy(int x, int y) {
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

void DisableCursor() {
    printf("\e[?25l");
}

void EnableCursor() {
    printf("\e[?25h");
}