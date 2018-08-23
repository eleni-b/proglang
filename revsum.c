#include <stdio.h>
#include <stdlib.h> 
#include <math.h>


int main(int argc, char **argv)
{
    int M = atoi(argv[1]);
    int c1, c2, i, power, N;
    
    int x[100000];
    int y[100000];
 
    
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
    
    

    if ( modified && ((x[i]-c1-x[power-i]) == 0)) {
        printf("0\n");
        return 0;
    }
    
    
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
    

    
    for (i = power; i >= 0; i--) {
        printf("%d",y[i]);
    }
    
    printf("\n");
    
    
    return 0;

}
