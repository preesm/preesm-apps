#ifndef SLICEDEC_H
#define SLICEDEC_H
#include <stdint.h>
#include <pthread.h>
#include <stdatomic.h>

#include "ovdefs.h"
#include "ctudec.h"
#include "dec_structures.h"

struct EntryThread;

enum StateSliceThread {
    IDLE = 0,
    ACTIVE,
    DECODING_FINISHED
};

typedef int (*DecodeFunc)(OVSliceDec *sldec, OVCTUDec *const ctudec, const OVPS *const prms, uint16_t entry_idx);

struct SliceThread
{
    OVSliceDec *owner;
    struct EntryThread *tdec;
    
    struct MainThread* main_thread;
    
    OVNALUnit* slice_nalu;

    int nb_threads;
    uint8_t active_state;

    /* Information on current task */
    int nb_entry_th;
    int nb_entries;

    DecodeFunc decode_entry;

    atomic_uint first_job;
    atomic_uint last_entry_idx;

    /* Slice decoder thread to be used later if
     * multiple slices
     */
    pthread_t thread;
    pthread_mutex_t gnrl_mtx;
    pthread_cond_t gnrl_cnd;
};

struct CCLines
{
    uint8_t *qt_depth_map_x;
    uint8_t *log2_cu_w_map_x;
    uint8_t *cu_mode_x;
    /* TODO we could do the same for rows and allocate a
     * complete row instead of reset columns y buffers 
     * at each new line
     */
};

/* Structure used to retrieve above modes information for modes
 * derivation
 * FIXME realloc on picture width changes
 */
struct DRVLines
{
    /* Used for intra Most Probable Mode changes
     * Init value is set to PLANAR
     */
    uint8_t *intra_luma_x;

    /* Bit Field information on above reconstructed PU
     * Used for Intra reference construction
     * LSB correspond to first above PU
     */
    uint32_t *progress_map;

    /* Inter lines for Motion Vector Prediction */
    struct InterLines
    {
        /* Motion vectors of above line */
        OVMV *mv0;
        OVMV *mv1;

        /* Bit fields of above line */
        uint32_t *dir0;
        uint32_t *dir1;

        /* Bit fields for affine motion */
        uint32_t *affine;

        struct AffineInfo *aff_info;

    } inter_lines;

    struct DBFLines
    {
        /* QP Information for thresholds */
        int8_t *qp_x_map;
        int8_t *qp_x_map_cb;
        int8_t *qp_x_map_cr;

        /* Maps information */
        uint64_t *small_map;

        uint64_t *dbf_bs2_hor;
        uint64_t *dbf_bs2_hor_c;

        uint64_t *dbf_bs1_hor;
        uint64_t *dbf_bs1_hor_cb;
        uint64_t *dbf_bs1_hor_cr;

        uint64_t *dbf_affine;

        /* CU is large */
        uint64_t *large_map_c;
    } dbf_lines;

    /*FIXME used */
    void *inter_data;
};


typedef struct OVSliceDec
{
   uint8_t slice_type;

   OVPS *active_params;
   /* Lins for CABAC context derivation luma and chroma */
   struct CCLines cabac_lines[2];

   /* Lines used to retrieve local informations to be used 
    * by reconstructions such as MVs or intra modes
    */
   struct DRVLines drv_lines;

   /* Reference to current pic being decoded */
   OVPicture *pic;

   OVCTUDec **ctudec_list; 
   int nb_entry_th;

   struct SliceThread th_slice;

} OVSliceDec;

void slicedec_copy_params(OVSliceDec *sldec, struct OVPS* dec_params);

int slicedec_update_entry_decoders(OVSliceDec *sldec, const OVPS *const prms);

int slicedec_decode_rect_entries(OVSliceDec *sldec, const OVPS *const prms);

void slicedec_finish_decoding(OVSliceDec *sldec);
int
slicedec_decode_rect_entry(OVSliceDec *sldec, OVCTUDec *const ctudec, const OVPS *const prms,
                           uint16_t entry_idx);
#if 0
int slicedec_decode_rect_entry(OVSliceDec *sldec, const OVPS *const prms);
#endif
int slicedec_init_lines(OVSliceDec *const sldec, const OVPS *const ps);

int slicedec_init(OVSliceDec *sldec, int nb_entry_th);
void slicedec_uninit(OVSliceDec **sldec_p);
#endif
