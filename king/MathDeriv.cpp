#include "MathDeriv.h"
#include "MathConstant.h"

#include <math.h>

#define   MAXROUNDS      20
#define   SQRT_HALF      (1.0/M_SQRT2)
#define   TWO            (M_SQRT2 * M_SQRT2)

double dfunction(double (* func)(double), double x, double h, double & err)
   {
   double a[MAXROUNDS][MAXROUNDS];

   // Initial crude estimate
   double result = a[0][0] = ((*func)(x+h) - (*func)(x-h)) / (2.0 * h);

   // Initial guess of error is large
   err = 1e30;

   // At each round, update Neville tableau with smaller stepsize and higher
   // order extrapolation ...
   for (int i = 1; i < MAXROUNDS; i++)
      {
      // Decrease h
      h *= SQRT_HALF;

      // Re-evaluate function
      a[0][i] = ((*func)(x+h) - (*func)(x-h)) / (2.0 * h);

      // Calculate extrapolations of various orders ...
      double factor = TWO, error;

      for (int j = 1; j <= i; j++)
         {
         a[j][i] = (a[j-1][i] * factor - a[j-1][i-1])/(factor - 1.0);

         factor *= TWO;

         error = max(fabs(a[j][i] - a[j-1][i]), fabs(a[j][i] - a[j-1][i-1]));

         // Did we improve solution?
         if (error < err)
            {
            err = error;
            result = a[j][i];
            }
         }

      // Stop if solution is deteriorating ...
      if (fabs(a[i][i] - a[i-1][i-1]) >= 2.0 * err)
         break;
      }

   return result;
   }

double dfunction(double (* func)(double), double x, double h)
   {
   double err;

   return dfunction(func, x, h, err);
   }
