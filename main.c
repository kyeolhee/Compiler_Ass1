#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct _Type {
    // DataType = 0 is int, DataType = 1 is float;
    int DataType;
    int i_num;
    float f_num;
    // warning = true is int+float , warning = false is only int or float
    bool warning;
}Type;

Type num;
int time = 0;
char str[100];
enum { Null, NUMBER, PLUS, STAR, LP, RP, END } token;

Type expression();
Type term();
Type factor();
void get_token();
void error(int i);

void main() {
    Type result;
    str[99] = { 0 };
    char ch;
printf("Input : ");
    for (int i = 0; i < 100; i++) {
        ch = getchar();

        str[i] = ch;
        if (ch == '\n')
            break;
    }
    get_token();
    result = expression();
    if (token != END)
        error(3);
    else
        if (result.DataType == 0)
            printf("Result : %d\n", result.i_num);
        else {
            printf("Result : %f\n", result.f_num);
            if (result.warning == true)
                printf("Warning : It is a mixture of int and float.\n");
        }
}

Type expression() {
    Type result;
    Type term_result;
    result = term();
    while (token == PLUS) {
        get_token();
        term_result = term();
        if (result.DataType == 0) {
            if (term_result.DataType == 0)
                result.i_num += term_result.i_num;
else {
                result.DataType == 1;
                result.f_num = result.i_num;
                result.f_num += term_result.f_num;
                result.warning = true;
            }
        }
        else {
            if (term_result.DataType == 0) {
                result.f_num += term_result.i_num;
                result.warning = true;
            }
            else
                result.f_num += term_result.f_num;
        }
    }
    return (result);
}

Type term() {
    Type result;
    Type factor_result;
    result = factor();
    while (token == STAR) {
        get_token();
        factor_result = factor();
        if (result.DataType == 0) {
            if (factor_result.DataType == 0)
                result.i_num *= factor_result.i_num;
            else {
                result.DataType = 1;
                result.f_num = result.i_num;
                result.f_num *= factor_result.f_num;
                result.warning = true;
            }   
        }
        else {
            if (factor_result.DataType == 0) {
                result.f_num *= factor_result.i_num;
                result.warning = true;
            }
            else
                result.f_num *= factor_result.f_num;
        }
    }
    return (result);
}

Type factor() {
    Type result;
    if (token == NUMBER) {
        result = num;
        get_token();
    }
    else if (token == LP) {
        get_token();
        result = expression();
        if (token == RP)
            get_token();
        else
            error(2);
    }
    else
        error(1);
    return (result);
}
void get_token() {
    char ch = str[time];
    int Decimal = 0; // Decimal Point
    if (ch >= '0' && ch <= '9') {
        num.DataType = 0;
        num.i_num = ch - '0';
        num.f_num = 0;
        token = NUMBER;
        time++;

        while (1) {
            ch = str[time];
            // if input number is '.' -> DataType = float
            if (ch == '.') {
                if (num.DataType == 0) {
                    num.DataType = 1;
                    num.f_num = num.i_num;
                    Decimal = 1;
                }
                ch = str[time + 1];
                if (ch < '0' || ch > '9') {
                    error(4);
                }
            }
            else if (ch >= '0' && ch <= '9') {
                if (num.DataType == 0)
                    num.i_num = num.i_num * 10 + (ch - '0');
                else {
                    num.f_num = num.f_num + (ch - '0') * pow(0.1, Decimal);
                    Decimal++;
                }
            }
            else {
                break;
            }
            time++;
        }
    }
    else {
        switch (ch) {
        case '+': token = PLUS; break;
        case '*': token = STAR; break;
        case '(': token = LP; break;
        case ')': token = RP; break;
        case '\n': token = END; break;
        default: token = Null; break;
        }
        time++;
    }
}

void error(int i) {
    switch (i) {
    case 1: printf("Error : number or '(' expected\n"); break;
    case 2: printf("Error : ')' expected\n"); break;
    case 3: printf("Error : EOF expected\n"); break;
    case 4: printf("Error : number expected\n"); break;
    }
    exit(1);
}
