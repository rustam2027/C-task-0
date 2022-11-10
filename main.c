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
    String->len = 0;
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

}


void scan_string(MyString* string){
    char s = 'A';
    int i = 0;
    while (s != '0'){
        scanf("%c", &s);
        string->data[i] = s;
        if (i + 1 == string->cap){
            realloc_string(string);
        }
        i ++;
    }
}


void free_string(MyString* String){
    free((String->data));
    String->data = NULL;
}


int main(){
    MyString example;
    init_empty_string(&example);
    scan_string(&example);
    int i = 0;
    printf("%s", example.data);
    free_string(&example);
    return 0;
}