#include <stdio.h>
#include <stdlib.h>


typedef struct{
    char* data;
    size_t len;
    size_t cap;
} MyString;


void init_empty_string(MyString* String){
    String->data = (char *) malloc(sizeof(char) * 2);
    if (String->data == NULL){
        printf("WARNING: OUT OF MEMORY");
        exit(0);
    }
    String->data[0] = 0;
    String->len = 1;
    String->cap = 2;
}


void realloc_string(MyString* String){
    String->data = (char *) realloc(String->data, String->cap * 2 * sizeof(char));
    if (String->data == NULL){
        printf("WARNING: OUT OF MEMORY");
        exit(0);
    }
    String->cap = String->cap * 2;
}


void add_to_string(MyString* String, char thing){
    if (String->cap >= String->len){
        String->data[String->len - 1] = thing;
        String->len += 1;
    }
    printf("%d, %d\n", String->cap, String->len);
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
    while (s != '0'){
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


int main(){
    MyString example;
    init_empty_string(&example);
    scan_string(&example);
    add_to_string(&example, 'D');
    size_t i = 0;
    for (i = 0; i < example.cap; i ++){
        printf("%d ", example.data[i]);
    }
    free_string(&example);
    return 0;
}