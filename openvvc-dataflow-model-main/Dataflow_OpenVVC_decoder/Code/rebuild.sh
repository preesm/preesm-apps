#!/bin/bash
LIB_H=( cabac_internal.h ctudec.h data_rcn_angular.h data_rcn_mip.h data_rcn_transform.h data_scan_lut.h dbf_utils.h dec_structures.h decinit.h drv_lines.h drv_utils.h drv.h mempool_internal.h mempool.h nvcl_private.h nvcl_structures.h nvcl_utils.h nvcl.h ovannexb.h ovdec_internal.h ovdec.h ovdefs.h ovdmx.h ovdpb.h overror.h ovframe.h ovio.h ovmem.h ovthreads.h ovunits.h ovutils.h post_proc.h rcn_alf.h rcn_fill_ref.h rcn_intra_angular.h rcn_intra_cclm.h rcn_intra_dc_planar.h rcn_intra_mip.h  rcn_mc.h rcn_sao.h rcn_structures.h rcn_transform.h rcn.h slicedec.h vcl_cabac.h vcl.h )
LIBPATH=/home/nhaggui/Documents/ovvc
PREESMPROJECT=/home/nhaggui/Téléchargements/preesm-3.20.0-linux.gtk.x86_64/workspace/Dataflow_OpenVVC_decoder
cd $LIBPATH/build
make
#return to previous folder
cd -
#copy the .h
for header in ${LIB_H[@]};
do
  cp $LIBPATH/libovvc/$header $PREESMPROJECT/Code/include/$header;
done
#copy .a
cp $LIBPATH/build/libovvc.a $PREESMPROJECT/Code/
