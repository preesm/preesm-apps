#include "scale.h"

void applyScale(int size, int scale, IN unsigned char *in, OUT uint8_t *out){
    int i;
    for(i=0;i<size;i++){
        out[i]=in[i]*scale;
    }
}
