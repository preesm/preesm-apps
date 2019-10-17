#!/bin/bash -u

#apt install git cmake make gcc g++ build-essential libsdl2-* xvfb openjdk-8-jdk maven wget p7zip-full ffmpeg

function preesm_jdk_version() {
  local result=
  local java_cmd
  if [[ -n $(type -p java) ]]
  then
    java_cmd=java
  elif [[ (-n "$JAVA_HOME") && (-x "$JAVA_HOME/bin/javac") ]]
  then
    java_cmd="$JAVA_HOME/bin/javac"
  fi
  local IFS=$'\n'
  # remove \r for Cygwin
  local lines=$("$java_cmd" -Xms32M -Xmx32M -version 2>&1 | tr '\r' '\n')
  if [[ -z $java_cmd ]]
  then
    result=no_java
  else
    for line in $lines; do
      if [[ (-z $result) && ($line = *"version \""*) ]]
      then
        local ver=$(echo $line | sed -e 's/.*version "\(.*\)"\(.*\)/\1/; 1q')
        # on macOS, sed doesn't support '?'
        if [[ $ver = "1."* ]]
        then
          result=$(echo $ver | sed -e 's/1\.\([0-9]*\)\(.*\)/\1/; 1q')
        else
          result=$(echo $ver | sed -e 's/\([0-9]*\)\(.*\)/\1/; 1q')
        fi
      fi
    done
  fi
  echo "$result"
}

function preesm_check_java_version {
	v="$(preesm_jdk_version)"
	if [ $v -lt 8 ]; then
		cat << "EOF"

Eclipse requires Java 8 or higher. On debian like systems (as root) :
   $ apt-get install openjdk-8-jdk openjdk-8-source
   $ JVM=`update-java-alternatives -l | grep 1.8 | cut -d" " -f 1 | head -n 1` 
   $ update-java-alternatives -s $JVM
On other Linux distributions, Windows and MacOSX systems, please
visit http://www.oracle.com/technetwork/java/javase/downloads/index.html

EOF
		exit 1
	fi
}

function preesm_check_system() {
  preesm_check_java_version

  which git &> /dev/null
  [ $? != 0 ] && echo -e "Error: requires git to fetch Preesm and CLI\nOn Ubuntu: sudo apt install git" && exit 1

  which mvn &> /dev/null
  [ $? != 0 ] && echo -e "Error: requires maven to build Preesm\nOn Ubuntu: sudo apt install maven" && exit 1

  which Xvfb &> /dev/null
  [ $? != 0 ] && echo -e "Error: requires Xvfb to run graphical apps\nOn Ubuntu: sudo apt install xvfb" && exit 1

  which cmake &> /dev/null
  [ $? != 0 ] && echo -e "Error: requires CMake to build apps\nOn Ubuntu: sudo apt install cmake" && exit 1
  which gcc &> /dev/null
  [ $? != 0 ] && echo -e "Error: requires GCC to build apps\nOn Ubuntu: sudo apt install gcc build-essential" && exit 1
  which g++ &> /dev/null
  [ $? != 0 ] && echo -e "Error: requires G++ to build Spider apps\nOn Ubuntu: sudo apt install g++ build-essential" && exit 1

  which wget &> /dev/null
  [ $? != 0 ] && echo -e "Error: requires wget to fetch apps data\nOn Ubuntu: sudo apt install wget" && exit 1
  which 7z &> /dev/null
  [ $? != 0 ] && echo -e "Error: requires p7zip-full to fetch apps data\nOn Ubuntu: sudo apt install p7zip-full" && exit 1

  which ffmpeg &> /dev/null
  [ $? != 0 ] && echo -e "Error: requires ffmpeg to convert app data\nOn Ubuntu: sudo apt install ffmpeg" && exit 1


  ldconfig -p | grep libSDL2_ttf  &> /dev/null
  [ $? != 0 ] && echo -e "Error: requires lib SDL2 ttf as apps dependencies\nOn Ubuntu: sudo apt install libsdl2-*" && exit 1
  ldconfig -p | grep libSDL2_image  &> /dev/null
  [ $? != 0 ] && echo -e "Error: requires lib SDL2 image as apps dependencies\nOn Ubuntu: sudo apt install libsdl2-*" && exit 1
  
  return 0
}


function preesm_find_free_display_number {
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


function preesm_start_xvfb() {
  PREESM_XDN=$(preesm_find_free_display_number)
  export DISPLAY=:${PREESM_XDN}.0
  /usr/bin/Xvfb :${PREESM_XDN} -ac -screen 0 1280x1024x16&
  export PREESM_XVFBPID=$!
  echo " -- Start Xvfb on $PREESM_XDN (Pid = $PREESM_XVFBPID)"
}

function preesm_kill_xvfb() {
  echo " -- Kill Xvfb (Pid = $PREESM_XVFBPID)"
  kill -2 $PREESM_XVFBPID
}
