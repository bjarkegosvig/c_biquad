#include "biquad.h"

int bq_df1_init(struct bq_struct* bq_inst, const bq_type coefs[5])
{
    bq_inst->w0 = 0;

    for (size_t i = 0; i < 4; i++) {
        bq_inst->delay_line[i] = 0;
    }

    for (size_t i = 0; i < 3; i++) {
        bq_inst->coefs[i] = coefs[i];
    }
    // invert the sign on the a coefficients, so the output can be written as
    // y[i] = b0*x[i] + b1*x[i-1] + b2*x[i-2] + a1*y[i-1] + a2*y[i-2]
    bq_inst->coefs[3] = -coefs[3];
    bq_inst->coefs[4] = -coefs[4];
    return 0;
}


void bq_df1_process(struct bq_struct* const bq_inst, const bq_type* __restrict input, bq_type* __restrict output, size_t input_len)
{
    // init the delay line indexes
    int8_t w1 = bq_inst->w0 ^ 1; // toggle w1 between 0 and 1. it must be 1 when w0 is 0 and visa versa
    int8_t w2 = bq_inst->w0 + 2;
    int8_t w3 = w1 + 2;
    for (size_t i = 0; i < input_len; i++) {
        // calculate biquad
        output[i] = (input[i] * bq_inst->coefs[0]) + (bq_inst->delay_line[bq_inst->w0] * bq_inst->coefs[1]) + (bq_inst->delay_line[w1] * bq_inst->coefs[2]) + (bq_inst->delay_line[w2] * bq_inst->coefs[3]) + (bq_inst->delay_line[w3] * bq_inst->coefs[4]);

        // update delay line
        bq_inst->w0 = bq_inst->w0 ^ 1; // toggle w0 between 0 and 1
        w1 = w1 ^ 1;
        w2 = bq_inst->w0 + 2;
        w3 = w1 + 2;
        bq_inst->delay_line[bq_inst->w0] = input[i];
        bq_inst->delay_line[w2] = output[i];
    }
}


void bq_cascade_df1_init(struct bq_cas_struct* bq_inst, size_t num_of_biquads, bq_type* coefs, bq_type* delay_line)
{
    int32_t idx = 3;

    bq_inst->coefs = coefs;
    for (size_t i = 0; i < num_of_biquads; i++)
    {

        // invert the sign on the a coefficients, so the output can be written as
        // y[i] = b0*x[i] + b1*x[i-1] + b2*x[i-2] + a1*y[i-1] + a2*y[i-2]
        bq_inst->coefs[idx] = -bq_inst->coefs[idx]; 
        idx++;
        bq_inst->coefs[idx] = -bq_inst->coefs[idx];
        idx += 3;
    }

    bq_inst->delay_line = delay_line;
    for (size_t i = 0; i < num_of_biquads*4; i++)
    {
        bq_inst->delay_line[i] = 0;
    }
    
    bq_inst->stages = num_of_biquads;
    bq_inst->w0 = 0;
}

void bq_cascade_df1_process(struct bq_cas_struct* const bq_inst, const bq_type* __restrict input, bq_type* __restrict output, size_t input_len)
{
}
