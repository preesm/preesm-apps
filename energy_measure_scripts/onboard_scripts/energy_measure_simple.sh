#!/bin/bash
# desc : This script measure the power consumption of a program.
# arg1 :program name

BINARY=$1

SCRIPT_DIR=$(cd $(dirname ${0}) && pwd)


# init virtual framebuffer for running X applications
function find_free_display_number {
  USEDXDISPLAYS=`find /tmp -maxdepth 1 -type f -name ".X*-lock" | rev | cut -d"/" -f 1 | colrm 1 5 | rev | colrm 1 2`
  for i in {99..1}
  do
    FREE=YES
    for usedd in $USEDXDISPLAYS; do
      if [ "$usedd" == "$i" ]; then
        FREE=NO
        break
      fi
    done
    if [ "$FREE" == "YES" ]; then
      echo $i
      return
    fi
  done
}

command -v EnergyRecorder > /dev/null || {
  echo "install recorder"
  TMPDIR=$(mktemp -d)
  (cd ${TMPDIR} && git clone https://github.com/preesm/EnergyRecorder.git && cd EnergyRecorder && make && sudo make install)
  rm -rf ${TMPDIR}
}

XDN=$(find_free_display_number)
echo ""
echo "Virtual framebuffer: DISPLAY=${XDN}"
export DISPLAY=:${XDN}.0
/usr/bin/Xvfb :${XDN} -ac -screen 0 1280x1024x16 &
XVFBPID=$!
echo ""

# clean previous run
rm -rf ${SCRIPT_DIR}/Results/
mkdir -p ${SCRIPT_DIR}/Results/
echo "result dir : ${SCRIPT_DIR}/Results/"

start_ts=$(date '+%s%N')
# run energy recorder async. and keep PID 
# need sudo to access lower nice priority
sudo nice -n -20 /usr/local/bin/EnergyRecorder ${SCRIPT_DIR}/Results &
# run program
# need sudo to access lower nice priority
sudo nice -n -19 ${BINARY}
end_ts=$(date '+%s%N')
total_ts=$((end_ts - start_ts))

echo ${total_ts} > ${SCRIPT_DIR}/Results/time_ns.csv

#kill energy monitor when binary is finished
# need sudo to kill program run as sudo ...
sudo killall EnergyRecorder

#finally kill virtual framebuffer
kill -2 ${XVFBPID}


