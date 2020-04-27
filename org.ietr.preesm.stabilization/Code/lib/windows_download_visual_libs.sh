#!/bin/bash

function log() {
	echo "$(date +%X) $1"
}


## pthread
log "Download pthread."
rm -rf pthread-2.10.0
curl -o pthread-2.10.0.zip https://preesm.github.io/assets/downloads/pthread-2.10.0.zip
unzip pthread-2.10.0.zip
rm pthread-2.10.0.zip

## SDL2
log "Download SDL2 for visual"
rm -rf SDL2-2.0.9
curl -o SDL2-devel-2.0.9-VC.zip https://www.libsdl.org/release/SDL2-devel-2.0.9-VC.zip
unzip SDL2-devel-2.0.9-VC.zip
cp SDL2-2.0.9/lib/x86/* SDL2-2.0.9/lib/
rm SDL2-devel-2.0.9-VC.zip 

## SDL2-ttf
rm -rf SDL2_ttf-2.0.15
curl -o SDL2_ttf-devel-2.0.15-VC.zip https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.15-VC.zip
unzip SDL2_ttf-devel-2.0.15-VC.zip
cp SDL2_ttf-2.0.15/lib/x86/* SDL2_ttf-2.0.15/lib/
rm SDL2_ttf-devel-2.0.15-VC.zip
