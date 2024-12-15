#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

#define TEMP_FILE "temp.txt" // Временный файл

void complite_task(const char *filename, int index) {
    FILE *input = fopen(filename, "r");
    if (input == NULL) {
        perror("Ошибка при открытии файла");
        return;
    }

    FILE *temp = fopen(TEMP_FILE, "w");
    if (temp == NULL) {
        perror("Ошибка при создании временного файла");
        fclose(input);
        return;
    }

    char line[256];
    int current_line = 0;

    while (fgets(line, sizeof(line), input)) {
        line[strcspn(line, "\n")] = '\0';
        if (current_line == index) {
            // Добавляем зачёркивание
            fprintf(temp, "\033[9m%s\033[0m ✓\n", line);
        } else {
            fprintf(temp, "%s\n", line);
        }
        current_line++;
    }

    fclose(input);
    fclose(temp);
    remove(filename);
    rename(TEMP_FILE, filename);
}

int add_task(const char* filename, char* text, int chetch){               // добавлена запись в файл
    char * message = text;
     filename = "data.txt";
    FILE *fp = fopen(filename, "a");
    if(fp)
    {
        // записываем строку
        fputs(message, fp);
        fclose(fp);
    }
}

void delete_task(const char *filename, int index) {
    FILE *input = fopen(filename, "r");
    if (input == NULL) {
        perror("Ошибка при открытии файла");
        return;
    }

    FILE *temp = fopen(TEMP_FILE, "w");
    if (temp == NULL) {
        perror("Ошибка при создании временного файла");
        fclose(input);
        return;
    }

    char line[256];
    int current_line = 0;

    while (fgets(line, sizeof(line), input)) {
        if (current_line != index) {
            fprintf(temp, "%s", line); 
        }
        current_line++;
    }

    fclose(input);
    fclose(temp);
    remove(filename);
    rename(TEMP_FILE, filename);
}

void print_array(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Список задач пуст или файл не найден.\n");
        return;
    }

    char line[256];
    int index = 0;

    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0'; // Убираем перевод строки
        printf("%d. %s\n", index + 1, line);
        index++;
    }

    fclose(fp);
}

int main(void) {
    int chetch = 0;
    char task[4]; // "add", "del", "com"
    int index;
    char text[100];
    const char *filename = "data.txt";

    while (1) {
        print_array(filename);
        printf("todo_list:> ");
        scanf("%3s", task);

        if (strcmp(task, "add") == 0) {
            getchar(); // Очистка буфера
            fgets(text, sizeof(text), stdin);
            chetch = add_task(filename, text, chetch);
        } else if (strcmp(task, "del") == 0) {
            scanf("%d", &index);
            delete_task(filename, index-1);
        } else if (strcmp(task, "com") == 0) {
            scanf("%d", &index);
            complite_task(filename, index-1);
        } else {
            printf("Неизвестная команда.\n");
        }
    }

    return 0;
}