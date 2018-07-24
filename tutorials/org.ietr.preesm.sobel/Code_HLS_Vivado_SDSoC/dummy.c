#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "dummy.h"

int flag = 0;

void dummy(int id, IN unsigned char *y, IN unsigned char *u, IN unsigned char *v) {
    if(flag==30){
	    FILE* fd_p_input = fopen("/mnt/first_frame_input.gry","wb");
	    printf("wrinting_image frame n:%d\n",flag);
	    if(fd_p_input == NULL){
	        printf("error opening file for input\n");
	        goto out_if;
	    }
	    size_t n_byte_written = fwrite(y,sizeof(unsigned char),352*290,fd_p_input );
	    printf("number of byte written %zu \n",n_byte_written);
	    fclose(fd_p_input);
	    out_if:
		printf("end of writing frame %d",flag);
	}
	flag++;
	//printf("Frame #%d\n", id);
}
