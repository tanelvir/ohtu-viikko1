/* 
 * File:   main.c
 * Author: taneli
 *
 * Created on 29. syyskuuta 2012, 13:32
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * 
 */

typedef struct dxy {
    int d;
    int x;
    int y;
} dxy;

typedef struct term {
    int deg;
    int coeff;
    struct term* next;
    struct term* previous;
} termNode;

typedef struct terms {
    termNode* first;
    termNode* second;
    
} terms;

terms* makeDiv(termNode* S, termNode* Q) {
    terms* temp = malloc(sizeof(terms));
    temp->first = S;
    temp->second = Q;
    return temp;
}

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

dxy* Extended_Euclid(int a, int b) {
    dxy* tama;
    if (a < 0 || b < 0) {
        return tama;
    }
    if (b == 0) {
        tama->d = a;
        tama->x = 1;
        tama->y = 0;
        return tama;
    } else {
        dxy* temp;
        temp = Extended_Euclid(b, a % b);
        tama->d = temp->d;
        tama->x = temp->y;
        tama->y = temp->x - (floor(a / b)*(temp->y));
        return tama;
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


terms* divPolynomials(termNode* P, termNode* Q, int p) {
    termNode* R = P;
    termNode* S;
    int q;
    terms* remainder;
    
    int i = (R->deg - Q->deg);
    
    for (;i >= 0; i--) {
        
        if (R->deg == (Q->deg+i)) {
            dxy* e = Extended_Euclid(R->coeff,p);
            q = (R->coeff * abs(e->x));
            termNode* X = makeTerm(i, -q);
            R = addPolynomials(R,mulPolynomials(X,Q));
        }
        S = addPolynomials(S, makeTerm(i, q));
    }
    remainder = makeDiv(S,R);
    return remainder;
    
}

void printPolynomial(termNode* P) {
    termNode* p = P;
    while (p != NULL) {
        printf("%dX^%d\n", p->coeff, p->deg);
        p = p->next;
    }
    printf("\n");
}

termNode* polGCD(termNode* P, termNode* Q, int p) {
    
}

termNode* genPolynomials(int n, int p) {
    
}

int main(int argc, char** argv) {
    termNode* a1 = makeTerm(6, 2);
    termNode* a2 = makeTerm(5, 2);
    termNode* a3 = makeTerm(3, 1);
    termNode* a4 = makeTerm(2, 1);
    termNode* a5 = makeTerm(1, 2);
    termNode* a6 = makeTerm(0, 2);

    a1->next = a2;
    a2->next = a3;
    a3->next = a4;
    a4->next = a5;
    a5->next = a6;

    a2->previous = a1;
    a3->previous = a2;
    a4->previous = a3;
    a5->previous = a4;
    a6->previous = a5;

    termNode* b1 = makeTerm(4, 1);
    termNode* b2 = makeTerm(3, 1);
    termNode* b3 = makeTerm(2, 2);
    termNode* b4 = makeTerm(1, 1);
    termNode* b5 = makeTerm(0, 2);

    b1->next = b2;
    b2->next = b3;
    b3->next = b4;
    b4->next = b5;

    b2->previous = b1;
    b3->previous = b2;
    b4->previous = b3;
    b5->previous = b4;
    
    terms * returnable;
    
     returnable = divPolynomials(a1, b1, 3);
    //dxy printable;
    //printable = Extended_Euclid(19, 31);
     printPolynomial(returnable->first);
     printPolynomial(returnable->second);
}