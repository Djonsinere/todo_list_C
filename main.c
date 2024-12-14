#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int complite_task(char* todo_array[], int index) {
    index -= 1;
    if (todo_array[index] == NULL) {
        printf("Задача с индексом %d не существует.\n", index);
        return -1;
    }

    char buffer[256]; // Временный буфер для строки
    snprintf(buffer, sizeof(buffer), "\033[9m%s\033[0m ✓", todo_array[index]);

    free(todo_array[index]);

    todo_array[index] = strdup(buffer);

    return 0;
}

int add_task(char* todo_array[], char* text, int chetch){
    if (chetch < MAX){
        todo_array[chetch] = strdup(text); // Дублирование строки
        printf("Добавлена задача: %s\n", text);
        chetch++;
    } else {
        printf("Ошибка: список задач переполнен.\n");
    }
    return chetch;
}

int delete_task(char* todo_array[], int index, int chetch){
    free(todo_array[index - 1]);
    todo_array[index-1] = todo_array[index];
    for (int i = index; i < chetch; i ++){
        todo_array[i] = todo_array[i + 1];
    }

    return(chetch -= 1);
}

void print_array(char* todo_array[], int todo_array_size){
    for (int i = 0; i < todo_array_size; i++){
        if (todo_array[i] != NULL) {
            printf("%d: %s\n", i+1, todo_array[i]);
        }
    }
}

int main(void){
    char* todo_array[MAX] = {0}; // Массив указателей на строки
    int chetch = 0;
    char task[4]; // "add", "del", "com"
    int index;
    char text[100];
    int current_loop = 1;

    while (current_loop){
        print_array(todo_array, chetch);
        printf("todo_list:> ");
        scanf("%3s", task);
        if (strcmp(task, "add") == 0) {
            getchar(); // Очистка буффера
            fgets(text, sizeof(text), stdin);
            text[strcspn(text, "\n")] = '\0'; // Удаление символа новой строки
            chetch = add_task(todo_array, text, chetch);
        } else if (strcmp(task, "del") == 0) {
            scanf("%d", &index);
            delete_task(todo_array, index, chetch);
        } else if (strcmp(task, "com") == 0) {
            scanf("%d", &index);
            complite_task(todo_array, index);
        }  else {
            printf("Неизвестная команда.\n");
        }
    }

    // Освобождение памяти
    for (int i = 0; i < chetch; i++) {
        free(todo_array[i]);
    }
    return 0;
}