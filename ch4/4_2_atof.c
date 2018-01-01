/*
 * 4-2. Extend atof to handle scientific notation of the form "123.45e-6"
 * where a floating-point number may be followed by e or E and an optionally signed exponent.
 *
 * wy-ei 2015.1.24
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

double _atof(char *str);

int main() {
    char *spi = "-3.1415926";
    char *sv = "3.0E8";

    double pi = _atof(spi);
    double v = _atof(sv);
    printf("%s : %f\n", spi, pi);
    printf("%s : %f\n", sv, v);

    return EXIT_SUCCESS;
}

double _atof(char *s) {
    int sign, i;
    double result, power;
    int exp;
    double expval;
    for(i = 0; isspace(s[i]); i++) //skip space
        ;

    sign = (s[i] == '-') ? -1 : 1; // get sign
    if(s[i] == '-' || s[i] == '+') {
        i++;
    }

    for(result = 0; isdigit(s[i]); i++) {
        result = result * 10.0 + s[i] - '0';
    }

    if(s[i] == '.') {
        i++;
        for(power = 1; isdigit(s[i]); i++) {
            result = result * 10.0 + s[i] - '0';
            power *= 10;
        }
    }
    if(s[i] == 'E' || s[i] == 'e') {
        i++;
        expval = (s[i] == '-') ? 0.1 : 10;
        if(s[i] == '+' || s[i] == '-') {
            i++;
        }
        for(exp = 0; isdigit(s[i]); i++) {
            exp = exp * 10 + s[i] - '0';
        }
    }

    result = sign * result / power;

    for(i = 0; i < exp; i++) {
        result *= expval;
    }

    return result;
}



