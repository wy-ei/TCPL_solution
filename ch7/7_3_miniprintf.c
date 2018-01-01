#include <stdio.h>
#include <stdarg.h>

void miniprintf(char* fmt, ...) {
    va_list ap;
    char* p, *sval;
    int ival;
    double dval;
    char cval;

    va_start(ap, fmt);
    for(p = fmt; *p; p++) {
        if(*p != '%') {
            putchar(*p);
            continue;
        }
        switch(*++p) {
        case 'd':
        case 'i':
            ival = va_arg(ap, int);
            printf("%d", ival);
            break;
        case 'x':
        case 'X':
            ival = va_arg(ap, int);
            printf("%x", ival);
            break;
        case 'o':
            ival = va_arg(ap, int);
            printf("%o", ival);
            break;
        case 'u':
            ival = va_arg(ap, int);
            printf("%u", ival);
            break;
        case 'c':
            cval = va_arg(ap, int);
            printf("%c", cval);
            break;
        case 'f':
            dval = va_arg(ap, double);
            printf("%f", dval);
            break;
        case 'e':
        case 'E':
            dval = va_arg(ap, double);
            printf("%e", dval);
            break;
        case 'g':
        case 'G':
            dval = va_arg(ap, double);
            printf("%g", dval);
            break;

        case 's':
            for(sval = va_arg(ap, char*); *sval; sval++) {
                putchar(*sval);
            }
            break;
        case 'p':
            printf("%p", va_arg(ap, int*));
            break;
        default:
            putchar(*p);
            break;
        }
    }
    va_end(ap);
}
int main() {
    char* s = "I love programming!";
    int a = 100;
    char c = 'X';
    miniprintf("%d , %s , %c , %p\n", a, s, c, &a);
    return 0;
}

