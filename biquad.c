#include "biquad.h"


int bq_df1_init(struct bq_struct* bq_inst, bq_type coefs[5])
{
    bq_inst->w0 = 0;

    for (size_t i = 0; i < 4; i++) {
        bq_inst->delay_line[i] = 0;
    }

    for (size_t i = 0; i < 3; i++) {
        bq_inst->coefs[i] = coefs[i];
    }
    // invert coefficients on the a coefficients, so the output can be written as
    // y[i] = b0*x[i] + b1*x[i-1] + b2*x[i-2] + a1*y[i-1] + a2*y[i-2]
    bq_inst->coefs[3] = -coefs[3];
    bq_inst->coefs[4] = -coefs[4];
    return 0;
}
void bq_df1_process(struct bq_struct* bq_inst, bq_type* input, bq_type* output, size_t input_len)
{

    int8_t w1, w2, w3;

    for (size_t i = 0; i < input_len; i++) {
        // init the delay line indexes
        w1 = bq_inst->w0 ^ 1; // toggle w1 between 0 and 1. it must be 1 when w0 is 0 and visa versa
        w2 = bq_inst->w0 + 2;
        w3 = w1 + 2;

        // calculate biquad
        output[i] = (input[i] * bq_inst->coefs[0]) + (bq_inst->delay_line[bq_inst->w0] * bq_inst->coefs[1]) + (bq_inst->delay_line[w1] * bq_inst->coefs[2]) + (bq_inst->delay_line[w2] * bq_inst->coefs[3]) + (bq_inst->delay_line[w3] * bq_inst->coefs[4]);

        // update delay line
        bq_inst->w0 = bq_inst->w0 ^ 1; // toggle w0 between 0 and 1
        w2 = bq_inst->w0 + 2;
        bq_inst->delay_line[bq_inst->w0] = input[i];
        bq_inst->delay_line[w2] = output[i];
    }
}
