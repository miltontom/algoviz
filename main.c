#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>

#define BAR 219
#define LINE 179
#define SPACE ' '

int get_random(int, int);
void sort(int[], int);
int* copy(int[], int);
void visualize(int[], int, char);
int* generate_array(int, int);
void clear_screen();
void set_cursor_visibility(bool);

int g_numbers_len;

int main(void) {
    srand(time(NULL));

    int *numbers = generate_array(1, 15);

    set_cursor_visibility(false);

    for (int i = 0; i < g_numbers_len - 1; i++) {
        for (int j = 0; j < g_numbers_len - 1 - i; j++) {
            if (numbers[j] > numbers[j + 1]) {
                int temp = numbers[j + 1];
                numbers[j + 1] = numbers[j];
                numbers[j] = temp;

                visualize(numbers, g_numbers_len, LINE);
                Sleep(100);
                clear_screen();
            }
        }
    }

    visualize(numbers, g_numbers_len, LINE);
    free(numbers);
    set_cursor_visibility(true);

    return 0;
}

int get_random(int lower, int upper) {
    return (rand() % (upper - (lower - 1))) + lower;
}

int* generate_array(int lower, int upper) {
    g_numbers_len = (upper - lower) + 1;
    int *array = malloc(sizeof(int) * g_numbers_len);

    for (int i = 0; i < g_numbers_len; i++) {
        array[i] = get_random(lower, upper);
    }

    return array;
}

int* copy(int array[], int array_len) {
    int *new_array = malloc(sizeof(int) * array_len);
    
    for (int i = 0; i < array_len; i++) {
        new_array[i] = array[i];
    }

    return new_array;
}

void visualize(int array[], int array_len, char style) {
    int *b = copy(array, array_len);
    sort(b, array_len);   

    char canvas[array_len][array_len];

    for (int i = 0; i < array_len; i++) {
        for (int j = 0; j < array_len; j++) {
            if (array[j] >= b[array_len - 1 - i]) {
                canvas[i][j] = style;
                printf("%c", canvas[i][j]);
            } else {
                canvas[i][j] = SPACE;
                printf("%c", canvas[i][j]);
            }
        }
        printf("\n");
    }

    free(b);
}

void sort(int array[], int array_len) {
    for (int i = 0; i < array_len - 1; i++) {
        for (int j = 0; j < array_len - 1 - i; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j + 1];
                array[j + 1] = array[j];
                array[j] = temp;
            }
        }
    }
}

void clear_screen() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD topLeft = {0,0};

    if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
        abort();
    }

    DWORD length = csbi.dwSize.X * csbi.dwSize.Y;
    DWORD written;

    // fill the console buffer with 'space'
    FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

    // reset attributes of every character to default like bgcolor, fg etc.
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

    SetConsoleCursorPosition(hOut, topLeft);
}

void set_cursor_visibility(bool visible) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;

    if (visible) {
        info.bVisible = TRUE;
    } else {
        info.bVisible = FALSE;
    }

    SetConsoleCursorInfo(consoleHandle, &info);
}