#ifndef SIMPLE_BIQUAD
#define SIMPLE_BIQUAD

#include <stddef.h>
#include <stdint.h>

#ifdef USE_DOUBLE
typedef double bq_type;
#else
typedef float bq_type;
#endif

/**
 * @struct Instance structure for the Biquad filter
 */
struct bq_struct {
    bq_type coefs[5];  /**< points to the coefficient array. */ 
    bq_type delay_line[4]; /**< points to the delay line array. */
    int8_t w0; /**< The delay line index pointing to x[i-1] */
};

/**
* Initialize the direct form I biquad structure.
* @param bq_inst : biquad structure, which holds the coefficients and delay elements.
* @param coefs[5] a array of biquad coefficients on the form {b0, b1, b2, a1, a2}. 
*
* @note The coefficients must be of the form where it satisfies the form
 * y[i] = b0*x[i] + b1*x[i-1] + b2*x[i-2] - a1*y[i-1] - a2*y[i-2]
*/
int bq_df1_init(struct bq_struct* bq_inst, const bq_type coefs[5]);

/**
* Process a direct form I biquad.
* @param *bq_inst : biquad structure, which holds the coefficients and delay elements.
* @param *input : input data array.
* @param *output : pointer to output array
* @param input_len : size/length of the input array

* @note The biquad will process using the diract form I equation seen below.
* y[i] = b0*x[i] + b1*x[i-1] + b2*x[i-2] - a1*y[i-1] - a2*y[i-2]
*/
void bq_df1_process(struct bq_struct* const bq_inst, const bq_type* __restrict input, bq_type* __restrict output, size_t input_len);



#endif
