#ifndef SED_H
#define SED_H

#include <stdlib.h>
/* 
   For spectra from 380nm to 780nm sampled at 10nm
*/

#define SED_LAMBDA_MIN 380
#define SED_LAMBDA_MAX 780
#define SED_LAMBDA_STEP 10

#define SED_SIZE (((SED_LAMBDA_MAX - SED_LAMBDA_MIN) / SED_LAMBDA_STEP) + 1)

extern float *sed_alloc(void);
extern void sed_copy(float *dst, float *src);
extern float *sed_dup(float *sed);
extern float sed_sum(float *sed);
extern void sed_multiply_by(float *e, float *f);
extern float *sed_blackbody(int temperature);

#endif  /* SED_H */
