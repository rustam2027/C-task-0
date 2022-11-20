#include <stdio.h>
#include <stdlib.h>


void null_check(void* pointer){
    if (!pointer){
        printf("WARNING: OUT OF MEMORY!");
        exit(0);
    }
}


typedef struct{
    char* data;
    size_t len;
    size_t cap;
} DynString;


typedef struct {
    DynString* data;
    size_t len;
    size_t cap;
} DynArrString;


void init_empty_string(DynString* ptr_string){
    ptr_string->cap = 1;
    ptr_string->len = 0;
    ptr_string->data = (char*) malloc(sizeof(char) * (ptr_string->cap + 1));
    null_check(ptr_string->data);
    ptr_string->data[0] = '\0';
}


void realloc_string(DynString* ptr_string){
    ptr_string->cap *= 2;
    ptr_string->data = (char*) realloc(ptr_string->data, sizeof(char) * (ptr_string->cap + 1));
    null_check(ptr_string->data);
}


void add_to_string(DynString* ptr_string, char c){
    if (ptr_string->cap < ptr_string->len + 1){
        realloc_string(ptr_string);
    }
    ptr_string->data[ptr_string->len] = c;
    ptr_string->len += 1;
    ptr_string->data[ptr_string->len] = '\0';
}


void delete_from_string(DynString* ptr_string, size_t index){
    size_t i = index + 1;
    for (; i < ptr_string->len; i++){
        ptr_string->data[i - 1] = ptr_string->data[i];
    }
    ptr_string->len -= 1;
    ptr_string->data[ptr_string->len] = 0;
}


void free_string(DynString* ptr_string){
    free(ptr_string->data);
    ptr_string->cap = 0;
    ptr_string->len = 0;
}


void init_empty_array(DynArrString* ptr_arr){
    ptr_arr->cap = 1;
    ptr_arr->len = 0;
    ptr_arr->data = (DynString*) malloc(sizeof(DynString) * ptr_arr->cap);
    null_check(ptr_arr->data);
}


void realloc_array(DynArrString* ptr_arr){
    ptr_arr->cap *= 2;
    ptr_arr->data = (DynString*) realloc(ptr_arr->data, sizeof(DynString) * ptr_arr->cap);
    null_check(ptr_arr->data);
}


void add_to_array(DynArrString* ptr_arr, DynString string){
    if (ptr_arr->cap < ptr_arr->len + 1){
        realloc_array(ptr_arr);
    }
    ptr_arr->data[ptr_arr->len] = string;
    ptr_arr->len += 1;
}


void delete_from_array(DynArrString* ptr_arr, size_t index){
    free_string(&ptr_arr->data[index]);
    size_t i = index + 1;
    for (; i < ptr_arr->len; i++){
        ptr_arr->data[i - 1] = ptr_arr->data[i];
    }
    ptr_arr->len -= 1;
    init_empty_string(&ptr_arr->data[ptr_arr->len]);
}


void free_array(DynArrString* ptr_arr){
    size_t i = 0;
    for (i = 0; i <= ptr_arr->len; i++){
        free_string(&ptr_arr->data[i]);
    }
    ptr_arr->cap = 0;
    ptr_arr->len = 0;
}


int from_char_to_int(DynString string, size_t l, size_t r){
    int return_number = 0;
    int dex  = 1;
    // size_t i = r - 1;
    int flag = 1;
    if (string.data[l] == '+'){
        l++;
    } else if (string.data[l] == '-'){
        flag = -1;
        l++;
    }
    for (; r >= l; r--){
        return_number += (int) (string.data[r] - '0') * dex;
        dex *= 10;
        if (r - 1 > r){
            break;
        }
    }

    return_number *= flag;

    return return_number;
}


DynString from_int_to_char(int number){
    DynString return_string;
    init_empty_string(&return_string);

    if (number < 0){
        add_to_string(&return_string, '-');
        number *= -1;
    }

    int back_number = number;
    int s = -1;
    while (number != 0){
        s += 1;
        number = number / 10;
    }

    number = back_number;

    int dex = 1;
    for (; s > 0; s--){
        dex *= 10;
    }

    while (dex != 0){
        add_to_string(&return_string, (char) (number / dex + '0'));
        number = number % dex;
        dex = dex /10;
    }

    return return_string;
}


int if_letter(char c){
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)){
        return 1;
    }
    return 0;
}


int if_numeric(char c){
    if (c - '0' >= 0 && c - '0' <= 9){
        return 1;
    }
    return 0;
}


int if_word(DynString string){
    for (size_t i = 0; i < string.len; i++){
        if (if_letter(string.data[i]) == 0){
            return 0;
        }
    } 
    return 1;
}


int check_if_palindrome(DynString string){
    size_t i = 0;
    if (if_word(string) == 0){
        return 0;
    }
    for (;i < string.len/2; i ++){
        if (string.data[i] != string.data[string.len - i - 1]){
            return 0;
        }
    }
    if (string.len > 1){
        return 1;
    } else {
        return 0;
    }
}


int check_if_number(DynString string){
    size_t i = 0;
    if (string.data[0] == '+' || string.data[0] == '-'){
        i = 1;
        if (string.len < 2){
            return 0;
        }
    }
    for (; i < string.len; i++){
        if (if_numeric(string.data[i]) == 0){
            return 0;
        }
    }
    if (string.len < 10 && string.len >= 1){
        return 1;
    } else {
        return 0;
    }
}


int main(int argc, const char** argv){
    DynString example;
    DynString inter_example;
    DynArrString ex_arr;

    init_empty_string(&example);
    init_empty_string(&inter_example);
    init_empty_array(&ex_arr);

    FILE* file = fopen(argv[1], "r");
    char c;
    if (file == NULL){
        printf("ERROR: wrong input file name\n");
        exit(0);
    }
    c = fgetc(file);
    while (c != EOF){
        if (c == '\n' || c == ' ' || c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/'){
            if (example.len != 0){
                add_to_array(&ex_arr, example);

                init_empty_string(&example);
            }
            if (c == '+' || c == '-'){
                init_empty_string(&inter_example);

                add_to_string(&inter_example, c);

                c = fgetc(file);

                if (if_letter(c) == 1 || if_numeric(c) == 1){
                    example = inter_example;

                    add_to_string(&example, c);

                } else {
                    add_to_array(&ex_arr, inter_example);

                    add_to_string(&example, c);

                    add_to_array(&ex_arr, example);

                    init_empty_string(&example);
                }
            } else {
                add_to_string(&example, c);

                add_to_array(&ex_arr, example);

                init_empty_string(&example);
            }
        } else if (c == 13) {

        } else {
            add_to_string(&example, c);
        }
        c = fgetc(file);
    }

    for (size_t i = 0; i < ex_arr.len; i++){
        for (size_t j = 0; j < ex_arr.data[i].len; j++){
            printf("%d ", ex_arr.data[i].data[j]);
        }
        printf("\n");
    }

    fclose(file);
    
    if (example.len != 0){
        add_to_array(&ex_arr, example);
    }

    size_t i = 0;
    int changes = 1;
    while (changes){
        changes = 0;
        for (i = 0; i < ex_arr.len; i ++){
            if (check_if_palindrome(ex_arr.data[i]) == 1){
                changes = 1;
                DynString palindrome;
                init_empty_string(&palindrome);

                add_to_string(&palindrome, 'P');
                add_to_string(&palindrome, 'A');
                add_to_string(&palindrome, 'L');
                add_to_string(&palindrome, 'I');
                add_to_string(&palindrome, 'N');
                add_to_string(&palindrome, 'D');
                add_to_string(&palindrome, 'R');
                add_to_string(&palindrome, 'O');
                add_to_string(&palindrome, 'M');

                ex_arr.data[i] = palindrome;
                init_empty_string(&palindrome);
            }

            if (ex_arr.data[i].data[0] == '('){
                size_t iter = i;
                int Flag = 0;
                for (; iter < ex_arr.len; iter++){
                    if (if_word(ex_arr.data[iter]) == 1){
                        Flag += 1;
                    }
                    if (ex_arr.data[iter].data[0] == ')' && Flag <= 1){
                        delete_from_array(&ex_arr, iter);
                        delete_from_array(&ex_arr, i);
                        changes = 1;
                        break;
                    }
                }
            }

            if (i == 0){
                if (ex_arr.data[i].data[0] == ' '){
                    delete_from_array(&ex_arr, i);
                    changes = 1;
                } else if (ex_arr.data[i].data[0] == '\n'){
                    delete_from_array(&ex_arr, i);
                    changes = 1;
                }
            }
            else if (ex_arr.data[i].data[0] == ' ' && ex_arr.data[i - 1].data[0] == ' '){
                    delete_from_array(&ex_arr, i);
                    changes = 1;
                } else if (i > 2 && ex_arr.data[i].data[0] == '\n' && ex_arr.data[i - 1].data[0] == '\n' && ex_arr.data[i - 2].data[0] == '\n'){
                    delete_from_array(&ex_arr, i);
                    changes = 1;
                }

            if (check_if_number(ex_arr.data[i]) == 1){
                int a = from_char_to_int(ex_arr.data[i], 0, ex_arr.data[i].len - 1);

                int operation = 0;
                size_t operation_index = 0;

                int find_b = 0;
                size_t b_index = 0;
                int b;

                for (size_t iter = i + 1; iter < ex_arr.len; iter++){
                    if (check_if_number(ex_arr.data[iter]) == 1){
                        b = from_char_to_int(ex_arr.data[iter], 0, ex_arr.data[iter].len - 1);
                        find_b = 1;
                        b_index = iter;
                        break;
                    } else if (ex_arr.data[iter].data[0] == '+'){
                        operation = 1;
                        operation_index = iter;
                    } else if (ex_arr.data[iter].data[0] == '-'){
                        operation = 2;
                        operation_index = iter;
                    } else if (ex_arr.data[iter].data[0] == '*'){
                        operation = 3;
                        operation_index = iter;
                    } else if (ex_arr.data[iter].data[0] == '/'){
                        operation = 4;
                        operation_index = iter;
                    } else if (ex_arr.data[iter].data[0] == ' '){
                    } else {
                        break;
                    }
                }

                if (operation != 0 && find_b == 1){
                    int number = 0;
                    int division_zero = 0;
                    if (operation == 1){
                        number = a + b;
                    } else if (operation == 2){
                        number = a - b;
                    } else if (operation == 3){
                        number = a * b;
                    } else if (operation == 4){
                        if (b != 0){
                            number = a / b;
                        } else {
                            division_zero = 1;
                        }
                    }

                    delete_from_array(&ex_arr, b_index);
                    delete_from_array(&ex_arr, operation_index);

                    free_string(&ex_arr.data[i]);

                    if (division_zero == 1){
                        DynString error;
                        init_empty_string(&error);

                        add_to_string(&error, 'E');
                        add_to_string(&error, 'R');
                        add_to_string(&error, 'R');
                        add_to_string(&error, 'O');
                        add_to_string(&error, 'R');

                        ex_arr.data[i] = error;

                        init_empty_string(&error);
                    } else {
                        ex_arr.data[i] = from_int_to_char(number);
                    }
                    changes = 1;
                }
            }

            if (i != 0 && ex_arr.data[i].len <= 10 && ex_arr.data[i].len > 2){
                if ((ex_arr.data[i].data[0] == '+' || ex_arr.data[i].data[0] == '-') \
                    && ex_arr.data[i].data[ex_arr.data[i].len - 2] == 't' && ex_arr.data[i].data[ex_arr.data[i].len - 1] == 'F'){
                    int fahrenheit =  from_char_to_int(ex_arr.data[i], 0, ex_arr.data[i].len - 3);

                    float celsius = (fahrenheit - 32) * 0.555;

                    int int_celsius = (int) (celsius * 10);
                    int frac_celsius = int_celsius % 10;

                    int_celsius = int_celsius / 10;

                    if (frac_celsius < 0){
                        frac_celsius *= -1;
                    }
                    
                    free_string(&ex_arr.data[i]);

                    init_empty_string(&ex_arr.data[i]);

                    ex_arr.data[i] = from_int_to_char(int_celsius);
                    add_to_string(&ex_arr.data[i], ',');
                    add_to_string(&ex_arr.data[i], frac_celsius + '0');
                    add_to_string(&ex_arr.data[i], 't');
                    add_to_string(&ex_arr.data[i], 'C');
                }
            }
        }
    }
    file = fopen(argv[2], "w");

    for (size_t i = 0; i < ex_arr.len; i++){
        for (size_t j = 0; j < ex_arr.data[i].len; j++){
            putc(ex_arr.data[i].data[j], file);
        }
    }
    fclose(file);

    // for (i = 0; i < ex_arr.len; i ++){
    //     printf("%s", ex_arr.data[i].data);
    // }
    // free_array(&ex_arr);
    return 0;
}


// int main(){
//     DynString example;
//     DynArrString example_arr;

//     init_empty_array(&example_arr);
//     init_empty_string(&example);

//     add_to_string(&example, '+');
//     add_to_string(&example, '1');
//     add_to_string(&example, '2');
//     add_to_string(&example, '3');

//     add_to_string(&example, '-');
//     add_to_string(&example, '1');
//     add_to_string(&example, '2');

//     add_to_string(&example, '2');

//     int num = from_char_to_int(example, 0, 3);
//     int num2 = from_char_to_int(example, 4, 6);
//     int num3 = from_char_to_int(example, 7, 7);

//     printf("%d %d %d\n", num, num2, num3);

//     free_array(&example_arr);
// }