#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/**
 * Prints a pattern of numbers from 1 to n
 * n is a single integer and 1 <= n <= 1000
 * 
 * Input: 7
 *
 * Output:
 * 7 7 7 7 7 7 7 7 7 7 7 7 7
 * 7 6 6 6 6 6 6 6 6 6 6 6 7
 * 7 6 5 5 5 5 5 5 5 5 5 6 7
 * 7 6 5 4 4 4 4 4 4 4 5 6 7
 * 7 6 5 4 3 3 3 3 3 4 5 6 7
 * 7 6 5 4 3 2 2 2 3 4 5 6 7
 * 7 6 5 4 3 2 1 2 3 4 5 6 7
 * 7 6 5 4 3 2 2 2 3 4 5 6 7
 * 7 6 5 4 3 3 3 3 3 4 5 6 7
 * 7 6 5 4 4 4 4 4 4 4 5 6 7
 * 7 6 5 5 5 5 5 5 5 5 5 6 7
 * 7 6 6 6 6 6 6 6 6 6 6 6 7
 * 7 7 7 7 7 7 7 7 7 7 7 7 7
 *
 */
int main()
{
     int n;
     int i, j, k;
     int dec;
     int len;

     scanf("%d", &n);
     len = 2 * n - 1;

     for (i = 0; i < len; i++)
     {
          if (i <= (len / 2))
          {
               for (dec = 0; dec < i; dec++)
                    printf("%d ", n - dec);

               for (j = 0; j < (2 * (n - i) - 1); j++)
                    printf("%d ", n - dec);

               for (k = 1; k <= dec; k++)
                    printf("%d ", n - dec + k);
          }
          else
          {
               for (dec = 0; dec < (len - i - 1); dec++)
                    printf("%d ", n - dec);

               for (j = 0; j < (2 * (n - dec) - 1); j++)
                    printf("%d ", n - dec);

               for (k = 1; k <= dec; k++)
                    printf("%d ", n - dec + k);
          }
          
          printf("\n");
     }

     return (0);
}