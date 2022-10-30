#include <stdio.h>
#include <stdlib.h>

// a) Structure polynôme
typedef struct Monome
{
    int coef;
    int exp;
} Monome;

typedef struct Polynome
{
    Monome info;
    struct Polynome *suiv;
} Poly, *Polynome;

void afficherPoly(Polynome p)
{
    Polynome poly = p;
    while (poly != NULL)
    {
        printf("%dx^%d", poly->info.coef, poly->info.exp);
        if (poly->suiv != NULL)
        {
            printf(" + ");
        }
        poly = poly->suiv;
    }
}

// b) rajoute un monôme
void addMonome(Polynome *p, int coef, int exp)
{
    Polynome poly = (Polynome)malloc(sizeof(Poly));
    poly->info.coef = coef;
    poly->info.exp = exp;
    poly->suiv = *p == NULL ? NULL : *p;
    *p = poly;
    poly = NULL;
}

// c) destruction d'un polynôme
void destroyPlynome(Polynome *p)
{
    Polynome destroy;
    while (*p != NULL)
    {
        destroy = *p;
        *p = (*p)->suiv;
        destroy->suiv = NULL;
        free(destroy);
    }
    printf("\nsuccessful destroy\n");
}

// d) addition de deux polynome
void insert(Polynome *poly, int coef, int exp)
{
    Polynome n = (Polynome)malloc(sizeof(Poly));
    n->info.coef = coef;
    n->info.exp = exp;
    n->suiv = NULL;
    Polynome p = *poly;
    if (*poly == NULL)
    {
        *poly = n;
    }
    else
    {
        while (p->suiv != NULL)
        {
            p = p->suiv;
        }
        p->suiv = n;
    }
}

void insertPoly(Polynome *poly, Polynome data)
{
    Polynome p = data;
    while (p != NULL)
    {
        insert(poly, p->info.coef, p->info.exp);
        p = p->suiv;
    }
}

Polynome sumPolynome(Polynome p1, Polynome p2)
{
    Polynome poly1 = p1, poly2 = p2, resultat = NULL;
    while (poly1 != NULL || poly2 != NULL)
    {
        if (poly1 == NULL)
        {
            insertPoly(&resultat, poly2);
            break;
        }
        else if (poly2 == NULL)
        {
            insertPoly(&resultat, poly1);
            break;
        }
        else
        {
            if (poly1->info.exp > poly2->info.exp)
            {
                insert(&resultat, poly1->info.coef, poly1->info.exp);
                poly1 = poly1->suiv;
            }
            else if (poly1->info.exp < poly2->info.exp)
            {
                insert(&resultat, poly2->info.coef, poly2->info.exp);
                poly2 = poly2->suiv;
            }
            else
            {
                insert(&resultat, poly2->info.coef + poly1->info.coef, poly2->info.exp);
                poly1 = poly1->suiv;
                poly2 = poly2->suiv;
            }
        }
    }
    return resultat;
}

// multiplication d'un polynôme par un monôme
Polynome multiplicationPolyMono(Polynome poly, Monome mono)
{
    Polynome result = NULL, p = poly;
    while (p != NULL)
    {
        insert(&result, p->info.coef * mono.coef, p->info.exp + mono.exp);
        p = p->suiv;
    }
    return result;
}

int main(void)
{
    Polynome p = NULL, p2 = NULL;
    addMonome(&p, 5, 0);
    addMonome(&p, 4, 2);
    addMonome(&p, -7, 3);
    addMonome(&p2, 5, 0);
    addMonome(&p2, 5, 3);
    addMonome(&p2, 5, 7);

    printf("\n");
    afficherPoly(p);
    printf("\n");
    afficherPoly(p2);
    printf("\n");

    Polynome r = sumPolynome(p, p2);

    printf("= \n");
    afficherPoly(r);

    Monome mono;
    mono.coef = 2;
    mono.exp = 1;

    Polynome m = multiplicationPolyMono(r, mono);
    printf("\n mult = ");
    afficherPoly(m);

    destroyPlynome(&p);
    destroyPlynome(&p2);
    destroyPlynome(&r);
    destroyPlynome(&m);

    return 0;
}