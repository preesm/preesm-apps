
#include "attache_file_dmx.h"

static int
init_openvvc_hdl(OVVCHdl *const ovvc_hdl, const char *output_file_name, int nb_frame_th, int nb_entry_th)
{
    OVVCDec **vvcdec = &ovvc_hdl->dec;
    OVVCDmx **vvcdmx = &ovvc_hdl->dmx;
    int ret;

    int display_output = !!strcmp(output_file_name, "/dev/null");

    ret = ovdec_init(vvcdec, display_output, nb_frame_th, nb_entry_th);

    if (ret < 0) goto faildec;

    ov_log(vvcdec, OVLOG_TRACE, "Decoder init.\n");

    ret = ovdmx_init(vvcdmx);

    if (ret < 0) goto faildmx;

    ov_log(vvcdmx, OVLOG_TRACE, "Demuxer init.\n");

    return 0;

faildec:
    ov_log(NULL, OVLOG_ERROR, "Decoder failed at init.\n");
    return ret;

faildmx:
    ov_log(NULL, OVLOG_ERROR, "Demuxer failed at init.\n");
    ovdec_close(*vvcdec);
    return ret;
}
static int
close_openvvc_hdl(OVVCHdl *const ovvc_hdl)
{
    OVVCDec *vvcdec = ovvc_hdl->dec;
    OVVCDmx *vvcdmx = ovvc_hdl->dmx;
    OVIO* io = ovvc_hdl->io;
    int ret;

    if (io != NULL) {
        io->close(io);
    }

    ret = ovdec_close(vvcdec);

    if (ret < 0) goto faildecclose;

    ret = ovdmx_close(vvcdmx);

    if (ret < 0) goto faildmxclose;

    return 0;

faildecclose:
    /* Do not check for dmx failure  since it might override
       return value to a correct one in either success or
       failure we already raised an error*/
    ov_log(NULL, OVLOG_ERROR, "Decoder failed at cloture.\n");
    ovdmx_close(vvcdmx);

faildmxclose:
    return ret;
}
static int
dmx_attach_file(OVVCHdl *const vvc_hdl, const char *const input_file_name)
{
    int ret;
    OVFileIO *file_io = ovio_new_fileio(input_file_name,"rb");

    if (file_io == NULL) {
        perror(input_file_name);
       vvc_hdl->io = NULL;
       return -1;
    }

    vvc_hdl->io = (OVIO*) file_io;

    ret = ovdmx_attach_stream(vvc_hdl->dmx, (OVIO*) vvc_hdl->io);

    return ret;
}
//*******************************************************************************************************************************
//********************************************************************************************************************************
void attach(  OVVCHdl *ovvc_hdl){
	int ret=0;
	  ret = init_openvvc_hdl(ovvc_hdl, "/dev/null", 1, 1);

//************recuperer le nom de fichier input**************
	int compt=0;
    FILE * fil;
    /* ouverture du fichier */
    if ((fil = fopen("input.txt", "r")) == NULL)
        perror("Erreur à l'ouverture du fichier");
    else {
        /* parcours du fichier */
        while(fgetc(fil) != EOF)
            compt ++; /* incrémentation du compteur */
    }
   // printf("Le nombre de caractères du fichier est de : %d\n", compt);
    /* fermeture du fichier */
    fclose(fil);
    char b[compt];
    FILE* fic = NULL;
    fic = fopen("input.txt", "rt");
    if (fic != NULL) {
        fgets( b, compt, fic ) ;

        fclose(fic);
    }

//*************************************************************************

ret = dmx_attach_file(ovvc_hdl, b);

}
