#ifndef SIMPLE_BIQUAD
#define SIMPLE_BIQUAD

#include <stddef.h>
#include <stdint.h>

#ifdef USE_DOUBLE
typedef double bq_type;
#else
typedef float bq_type;
#endif

struct bq_struct {
    bq_type coefs[5];
    bq_type delay_line[4];
    int8_t w0;
};

int bq_df1_init(struct bq_struct* bq_inst, bq_type coefs[5]);
void bq_df1_process(struct bq_struct* bq_inst, bq_type* input, bq_type* output, size_t input_len);


#endif
