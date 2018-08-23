#include <stdio.h>
#include <stdlib.h>

int get_k(int A[], int n, int maxsum_one);


int get_k (int A[], int n, int maxsum_one) {
    int total, this_k, i;
    total = 0;
    this_k = 1;
    
    for (i = 0; i < n; i++) {
        total += A[i];
        if (total > maxsum_one) {
            total = A[i];
            this_k++;
        }
    }
    return this_k;
}




int main(int argc, char **argv)
{
    int *A, *B, n, k, lo, hi, mid, current_k, i, j, total;
    
    FILE *fp;
    fp = fopen(argv[1], "r");
    
    fscanf(fp,"%d ",&n);
    fscanf(fp,"%d ",&k);


    A = malloc(n*sizeof(int));
    
    
    for (i = 0; i < n; i++) {
        fscanf(fp,"%d ", &A[i]);
    }
    
    fclose(fp);

    
    lo = -1;
    hi = 0;
    
    for (i = 0; i < n; i++) {
        if (A[i] > lo)
            lo = A[i];
    }
    
    for (i = 0; i < n; i++)
        hi += A[i];
    
    
    
    while (lo < hi) {
        mid = lo + (hi-lo)/2;
        current_k = get_k(A, n, mid);
        if (current_k <= k)
            hi = mid;
        else
            lo = mid+1;
    }

    
    B = malloc(k*sizeof(int));
    
    j = k-2;
    total = 0;
    
    for (i = n-1; i >= 0; i--) {
        total += A[i];
        
        if (total > lo) {
            B[j] = i;
            j--;
            total = A[i];
        }
    }
    
    i = 0;
    
    while (j >= 0) {
        B[i] = i;
        j--;
        i++;
    }
    
    j = 0;
    
    for (i = 0; i < n; i++) {
        if (i == B[j]) {
            printf("%d | ", A[i]);
            j++;
        }
        else
            printf("%d ", A[i]);
    }
     

    printf("\n");
    
    free(A);
    free(B);
    
    return 0;
    
}
