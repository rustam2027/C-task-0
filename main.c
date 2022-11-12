#include <stdio.h>
#include <stdlib.h>

void null_check(void* pointer){
    if (pointer == NULL){
        printf("WARNING: OUT OF MEMORY!");
        exit(0);
    }
}


// Создаем структуру строка
typedef struct{
    char* data;
    size_t len;
    size_t cap;
} MyString;

// Создаем стандартные функции
void init_empty_string(MyString* String){
    String->data = (char *) malloc(sizeof(char) * 2);
    null_check(String->data);
    String->data[0] = 0;
    String->len = 1;
    String->cap = 2;
}


void realloc_string(MyString* String){
    String->data = (char *) realloc(String->data, String->cap * 2 * sizeof(char));
    null_check(String->data);
    String->cap = String->cap * 2;
}


void add_to_string(MyString* String, char thing){
    if (String->cap >= String->len){
        String->data[String->len - 1] = thing;
        String->len += 1;
    }
    if (String->cap < String->len){
        realloc_string(String);
    }
    String->data[String->len] = 0;
    String->len++;
}


void scan_string(MyString* string){
    char s;
    scanf("%c", &s);
    string->len = 0;
    while (s != '\n'){
        string->data[string->len] = s;
        string->len ++;
        if (string->len  == string->cap){
            realloc_string(string);
        }
        scanf("%c", &s);
    }
    if (string->cap == string->len){
        realloc_string(string);
    }
    string->data[string->len] = 0;
    string->len ++;
}


void free_string(MyString* String){
    free((String->data));
    String->data = NULL;
}

// создаем структуру массив строк
typedef struct{
    MyString* data;
    size_t len;
    size_t cap;
} MyArray;

//создаем стандартные функции
void init_empty_array(MyArray* arr){
    arr->data = (MyString *) malloc(sizeof(MyArray) * 2);
    null_check(arr->data);
    arr->len = 0;
    arr->cap = 2;
}


void realloc_array(MyArray* arr){
    arr->data = (MyString *) realloc(arr->data, arr->cap * 2);
    null_check(arr->data);
    arr->cap *= 2;
}


void add_to_array(MyArray* arr, MyString string){ // вызывает segmentation fault
    if (arr->len == arr->cap){
        realloc_array(arr);
    }
    arr->data[arr->len] = string;
    arr->len += 1;
}


void free_array(MyArray* arr){
    size_t i = 0;
    for (i = 0; i < arr->len; i ++){
        free_string(&arr->data[i]);
    }
    free(arr->data);
}


int main(){
    MyString example;
    MyArray ex_arr;

    init_empty_array(&ex_arr);
    init_empty_string(&example);

    scan_string(&example);
    add_to_string(&example, 'D');
    //add_to_array(&ex_arr, example); 

    scan_string(&example);
    add_to_string(&example, 'D');
    //add_to_array(&ex_arr, example); 

    size_t i = 0;
    for (i = 0; i < ex_arr.len; i ++){
        printf("%s ", ex_arr.data[i].data);
    }
    free_string(&example);
    free_array(&ex_arr);
    return 0;
}