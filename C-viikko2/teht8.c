/* 
 * File:   teht8.c
 * Author: tanelvir
 *
 * Created on 24 September 2012, 13:54
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
typedef struct term {
    int deg;
    int coeff;
    struct term* next;
    struct term* previous;
} termNode;

termNode* makeTerm(int deg, int coeff) {
    termNode* uusi = malloc(sizeof (termNode*));
    if (uusi == NULL) {
        return NULL;
    }
    uusi->coeff = coeff;
    uusi->deg = deg;
    return uusi;
}

termNode* addPolynomials(termNode* P1, termNode* P2) {
    termNode* summa;
    if (P1->deg == P2->deg) {
        summa = makeTerm(P1->deg, P1->coeff + P2->coeff);
        return summa;
    } else if (P1->deg > P2->deg) {
        P1->next = P2;
        P2->previous = P1;
        return P1;
    } else {
        P1->previous = P2;
        P2->next = P1;
        return P2;
    }
}

termNode* readPolynomial(char* fname) {
    FILE *fptr = fname;
    int ch;
    int bol = 0;
    int deg;
    int coeff;

    while ((ch = getc(ftpr)) != EOF) {
        if (ch != '\n' && ch != '') {
            if (bol = 0) {
                bol = 1;
                deg = ch;
            } else {
                bol = 0;
                coeff = ch;
            }
            termNode* uusi = makeTerm(deg, coeff);
        }


    }
}

void printPolynomial(termNode* P) {
    termNode* p = P;
    while (p != NULL) {
        printf("%dX'%d\n", p->coeff, p->deg);
        p = p->next;
    }
    printf("\n");
}

termNode* mulPolynomials(termNode* P1, termNode* P2) {
    termNode* uusi;
    uusi->deg = P1->deg+P2->deg;
    uusi->coeff = P1->coeff*P1->coeff;
    return uusi;
}

termNode* addModPolynomials(int n, termNode* P1, termNode* P2) {
    termNode* startti = P2;
    while (P1 != NULL) {
        P2 = startti;
        while (P2 != NULL) {
            if (P1->deg==P2->deg) {
                P1 = makeTerm(P1->deg, P1->coeff+P2->coeff);
                free(P2->coeff);
                free(P2->deg);
                free(P2);
            }
            P2 = P2->next;
        }
        P1 = P1->next;
    }
}

termNode* mulModPolynimials(int n, termNode* P1, termNode* P2) {
    
}

int main(int argc, char** argv) {

    termNode* summa1;
    termNode* summa2;

    termNode* testi = makeTerm(5, 7);
    termNode* testi2 = makeTerm(5, 7);
    termNode* testi3 = makeTerm(2, 6);
    termNode* testi4 = makeTerm(7, 8);
    summa1 = addPolynomials(testi, testi2);
    summa2 = addPolynomials(testi3, testi4);
    printPolynomial(summa1);
    printPolynomial(summa2);
}

