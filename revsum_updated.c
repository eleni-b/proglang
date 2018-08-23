#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

/* Metrame ta kratoumena apo tis dio meries tis prosthesis. Nomizo mexri ekei to kanoume kai oi 2, an katalava kala apo tin diki sou ilopoiisi. Oi sigriseis ginontai me vasi ta kratoumena. An c2 = 0, opou c2 einai to kratoumeno tis aristeris merias, tote simainei oti to athroisma ton 2 arithmon pou exetazoume einai mikrotero tou 10. Ara an eho c1 = 1, tote simainei oti afairo 1 kai diairo dia 2 gia na vro tous arithmous. Episis, gia tin amesos epomeni vathmida tha ishiei oti c1 = 0, afou to athroisma mikrotero tou 10 sinepagetai oti den metavivazetai kati stin epomeni vathmida. Tora, gia to c2 tha prepei na koitaxo ti shesi metaxi ton 2 arithmon gia na do ti ishiei. Diladi an einai isoi kai i dexia meria einai +1 logo tou c1=1, tote kai i aristeri tha dinei c2 = 0. To exigo me 2-3 paradeigmata, gia na deis ti xrisi tous. 
 
    Exetazo ton arithmo 5676+6765 = 12441.
 
    Xekinao me c1 = 0, c2 = 0. power = 4 (einai o arithmos ton psifion tou M -1). Kano ton exis elenho : an eho peritto arithmo psifion alla den eimai stin vathmida pou prostheto (power+1) psifia, tote these c2 = 1, c1 = 0. Diladi edo eho 5 psifia alla to athroisma einai mikrotero apo 9999+9999 (ara prokiptei apo tetrapsifious). Se auti tin periptosi, elenho an to proto psifio tou M einai iso me 1. An nai, eimai ok. Apothikeuo ola ta ipoloipa psifia tou M ston pinaka x[i]. Diladi x[3] = 2, x[2] = 4, x[1] = 4, x[0] = 1. (edo ta kana anapoda, den ehei kapoia ousiastiki diafora nomizo).
 
        Ara c2 = 1, c1 = 0. pou simainei oti eho athroisma megalitero tou 10. Koitao an einai idia ta x[3] kai x[1]. Edo den einai. Ara eho c2 = 0, afou simainei oti eho parei ena sta aristera apo tin proigoumeni (x[3] - pio aristeri) vathmida. c1 = 1 episis gia ton idio logo, afou eho megalitero tou 10 athroisma. Ipologizo y[3] = 5, y[0] = 6. (Zitao athroisma iso me 10+teleutaio_psifio)
    
        Epomeni epanalipsi me c1 = 1, c2 = 1. Eho pano apo 10, afou c2 = 1. Kai elenho 9+x[1] == x[2]. 
 
        Me auto ton tropo peripou ginetai. Apla vale kato 2-3 prostheseis, kai des pos paei me ta kratoumena kathe vathmidas. O elenhos an ta psifia (simetrika) einai isa ginetai gia na do an eho apo proigoumeni vathmida kati, kai pos mou epireazei ta epomena kratoumena kai to athroisma.

 
 
 
 
*/
int main(int argc, char **argv)
{
    int M = atoi(argv[1]);
    int c1, c2, i, power, N;
    
    int x[100000];
    int y[100000];
    
    //Mehri 8 psifia doulevei kala!
    
// Variables c1 and c2 stand for carry from right and left addition respectively
    
    i = 0;
    

    while (1) {
        if ((M / (int)pow(10,i)) == 0) {
            power = i-1;
            break;
        }
        
        i++;
    }
    
    int tmp;

    // oi parakato 2 diloseis xrisimevoun gia tipikous logous, gia na kratisoume to kathe psifio. epeidi den exo asxolithei me praxeis bit, an exeis vrei tropo me bits na pernoume to kathe psifio, antikatastise to kommata parakato.
    x[power+1] = 0;
    tmp = M;

    c1 = 0;
    c2 = 0;
    
    int modified;
    modified = 0;
    
    
    // We observed that 11,101,10001 etc are the only numbers that can be written ONLY as sum of 10+01. For any other such sum, for example 20+02, 30+03, 40+4 etc. there also exists an alternative way of expressing M. (22 = 11+11, 202=101+101, 33=21+12 ..)
    if (M == ((int)pow(10,power)+1)) {
        printf("%d\n",(int)pow(10,power));
        return 0;
    }
    
// edo apothikevo ta psifia. kratao ena ligotero an xreiastei, se periptosi pou exo tin sinthiki pou eipame me ta psifia. to exigo kai parakato.
    //     if ( ((2 * (int)pow(10,power) - 2) > M) && ((power+1)%2 != 0) ) {

    if ( ((2 * (int)pow(10,power) - 2) >= M)  ) {
        if ( (M/ (int)pow(10,power)) != 1) {
                printf("0\n");
                return 0;
        }
        c2 = 1;
        c1 = 0;
        tmp = tmp - (int)pow(10,power);
        power--;
        modified = 1;
        for (i = power; i >= 0; i--) {
            x[i] = tmp / (int)pow(10,i);
            tmp = tmp - x[i]*(int)pow(10,i);
        }
    }
    else {
        for (i = power; i >= 0; i--) {
            x[i] = tmp / (int)pow(10,i);
            tmp = tmp - x[i]*(int)pow(10,i);
        }

    }
    

    i = power;
    
    
// modified : eho arithmo M mikrotero apo to antistoiho 9999+9999, alla arithmo psifion >5 (i tou antistoihou power+1)
// An loipon eho modified == true, kai den eho 1 sto proto psifio, profanos eho lathos. Ara exodos apo to programma.
    if ( modified && ((x[i]-c1-x[power-i]) == 0)) {
        printf("0\n");
        return 0;
    }
    
    // FIXED: to c1 prostithetai, den afaireitai. Giati sto athroisma emfanizetai os mia epipleon monada, ara to pragmatiko einai meion ena.
    
    while (i>= (power/2)) {
        if ( ((x[i] + c1 - x[power-i]) != 1) && ((x[i] + c1 - x[power-i]) != 10) && ((x[i] + c1 - x[power-i]) != 11) && ((x[i] + c1 - x[power-i]) != 0)) {
            printf("0\n");
            return 0;
        }
        
        
        if ( (c1 == 1) && (c2 == 0) ) {
            if ( x[i] == x[power-i] )
                c2 = 1;
            else
                c2 = 0;
            c1 = 0;
            if ( (x[i] - 1)%2 == 0) {
                y[i] = (x[i]-1)/2;
                y[power-i] = y[i];
            }
            else {
                y[i] = x[i]/2;
                y[power-i] = y[i]-1;
            }
        }
        else if ( (c1 == 0) && (c2 == 0)) {
            if (x[i] == x[power-i])
                c2 = 0;
            else
                c2 = 1;
            c1 = 0;
            if (x[power-i] % 2 == 0) {
                y[power-i] = x[power-i]/2;
                y[i] = y[power-i];
            }
            else {
                y[i] = (x[power-i]+1)/2;
                y[power-i] = y[i]-1;
            }
        }
        else if ( (c1 == 1) && (c2 == 1)) {
            if (x[i] == x[power-i])
                c2 = 1;
            else
                c2 = 0;
            c1 = 1;
            if ( (9 + x[i]) % 2 == 0) {
                y[i] = (9 + x[i])/2;
                y[power-i] = y[i];
            }
            else {
                y[i] = (10 + x[i])/2;
                y[power-i] = y[i] -1;
            }
        }
        else {
            if (x[i] == x[power-i])
                c2 = 0;
            else
                c2 = 1;
            if (x[power-i] == 9)
                c1 = 0;
            else
                c1 = 1;
            if ( (c1*10+x[power-i])%2 == 0) {
                y[i] = (c1*10+x[i])/2;
                y[power-i] = y[i];
            }
            else {
                y[i] = (c1*10+x[i]+1)/2;
                y[power-i] = y[i]-1;
            }
        }
        
        i--;
    }
    

    
// Epeidi to parapano loop siblironei zevgi, an eiha artio arithmo mou ehei meinei 1. To simplirono.
  //  if ((y[power/2] == 0) && ((((power+1)%2 == 0) && modified) || (!modified && ((power+1)%2 != 0)))) {
/*
    if ((y[power/2] == 0) && (x[power/2] != 0)) {
        if (x[power/2]%2 != 0) {
            printf("0\n");
            return 0;
        }
        else
            y[power/2] = x[power/2]/2;
    }
 */

    
/*
    c1 = 0;
    

// Telikos elenhos, an tairiazoun ta psifia. An den tairiazoun 0 kai exodos.
    for (i = power; i > power/2; i--) {
        if ( (y[i] + y[power-i]) > 10 ) {
            if ( (y[i] + y[power-i]+c1)%10 != x[power-i]) {
                printf("0\n");
                return 0;
            }
        }
        else {
            if ( (y[i] + y[power-i]) != x[power-i]) {
                printf("0\n");
                return 0;
            }
        }
        c1 = 1;
    }
*/
    
    for (i = power; i >= 0; i--) {
        printf("%d",y[i]);
    }
    
    printf("\n");
    
    
    return 0;

}