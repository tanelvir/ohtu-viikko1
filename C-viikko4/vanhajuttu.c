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
    termNode* p1 = P1;
    termNode* p2 = P2;
    termNode* temp;
    termNode* returning;

    if (p1->deg == p2->deg) {
        temp = makeTerm(p1->deg, (p1->coeff + p2->coeff));
        returning = temp;
        p1 = p1->next;
        p2 = p2->next;
    } else if (p1->deg > p2->deg) {

        temp = makeTerm(p1->deg, p1->coeff);
        returning = temp;
        p1 = p1->next;
    } else {
        temp = makeTerm(p2->deg, p2->coeff);
        returning = temp;
        p2 = p2->next;
    }

    while (p1 != NULL && p2 != NULL) {
        if (p1->deg == p2->deg) {
            termNode* new;
            new = makeTerm(p1->deg, p2->coeff + p1->coeff);
            temp->next = new;
            temp->next->previous = temp;
            temp = temp->next;
            p1 = p1->next;
            p2 = p2->next;
        } else if (p1->deg > p2->deg) {
            termNode* new;

            new = makeTerm(p2->deg, p2->coeff);
            temp->next = new;
            temp->next->previous = temp;
            temp = temp->next;
            p2 = p2->next;
        }
    }
    while (p1 == NULL && p2 != NULL) {
        termNode* new;
        new = makeTerm(p2->deg, p2->coeff);
        temp->next = new;
        temp->next->previous = temp;
        temp = temp->next;
        p2 = p2->next;
    }
    while (p1 != NULL && p2 == NULL) {
        termNode* new;

        new = makeTerm(p2->deg, p2->coeff);
        temp->next = new;
        temp->next->previous = temp;
        temp = temp->next;
        p2 = p2->next;
    }
    while (p1 != NULL && p2 == NULL) {
        termNode* new;
        new = makeTerm(p1->deg, p1->coeff);
        temp->next = new;
        temp->next->previous = temp;
        temp = temp->next;
        p1 = p1->next;
    }

    return returning;

}

void freePolynom(termNode* polynomi) {

    while (polynomi->next != NULL) {
        termNode* apu = polynomi->next;
        free(polynomi);
        polynomi = apu;
    }
}

termNode* mulPolynomials(termNode* P1, termNode* P2) {

    termNode* eka = P1;
    termNode* toka = P2;
    termNode* uus;
    termNode* uusosoitin;
    termNode* tokanAlku = toka;

    uus = makeTerm(eka->deg + toka->deg, eka->coeff * toka->coeff);
    uusosoitin = uus;
    toka = toka->next;
    while (eka != NULL && toka != NULL) {
        termNode* apu;
        apu = makeTerm(eka->deg + toka->deg, eka->coeff * toka->coeff);
        termNode* vanha;
        vanha = uus;
        uus = addPolynomials(uus, apu);
        free(apu);
        freePolynom(vanha);
        toka = toka->next;
        if (toka == NULL) {
            toka = tokanAlku;
            eka = eka->next;
        }
    }
    return uus;
}

termNode* readPolynomial(char* fname) {

    FILE *ftpr;
    ftpr = fopen(fname, "r");
    int bol = 0;
    int deg;
    int coeff;
    int kerroin;
    int termi;
    while (fscanf(ftpr, "%d %d", &kerroin, &termi) == 2) {
        printf("%d %d\n", kerroin, termi);
        makeTerm(kerroin, termi);

    }

    fclose(ftpr);
}

void printPolynomial(termNode* P) {
    termNode* p = P;
    while (p != NULL) {
        printf("%dX^%d\n", p->coeff, p->deg);
        p = p->next;
    }
    printf("\n");
}

termNode* addModPolynomials(int n, termNode* P1, termNode* P2) {
    termNode* uusi = addPolynomials(P1, P2);
    termNode* uusialku = uusi;
    while (uusi != NULL) {
        uusi->coeff = uusi->coeff % n;
        if (uusi->coeff == 0) {
            if (uusi->next != NULL) {
                uusi->next->previous = uusi->previous;
                uusi->previous->next = uusi->next;
            } else
                uusi->previous->next = NULL;
        }
        uusi = uusi->next;
    }
    return uusialku;

}

termNode* mulModPolynimials(int n, termNode* P1, termNode* P2) {
    termNode* uusi = mulPolynomials(P1, P2);
    termNode* uusialku = uusi;
    while (uusi != NULL) {
        uusi->coeff = uusi->coeff % n;

        if (uusi->coeff == 0) {
            if (uusi->next != NULL) {
                uusi->next->previous = uusi->previous;
                uusi->previous->next = uusi->next;
            } else
                uusi->previous->next = NULL;
        }
        uusi = uusi->next;
    }
    return uusialku;

}

int main(int argc, char** argv) {


    termNode* testi = makeTerm(6, 5);
    termNode* testi2 = makeTerm(6, 6);
    termNode* testi3 = makeTerm(3, 8);
    termNode* testi4 = makeTerm(2, 8);
    termNode* summa1 = addPolynomials(testi, testi2);
    termNode* summa5 = addPolynomials(summa1, testi3);
    termNode* kerto1 = mulPolynomials(summa1, testi3);

    //    printPolynomial(testi);
    //    printPolynomial(testi2);
    printPolynomial(testi3);
    printPolynomial(summa1);
    //    printPolynomial(summa5);
    printPolynomial(kerto1);
    termNode* summa2 = addPolynomials(testi3, testi4);

    termNode* printattava = addModPolynomials(5, summa1, summa2);
    printPolynomial(printattava);
    //    
    //    readPolynomial("luvut.txt");
    //
    //    termNode* newone = mulModPolynimials(5, summa1, summa2);
    //    printPolynomial(newone);
} 