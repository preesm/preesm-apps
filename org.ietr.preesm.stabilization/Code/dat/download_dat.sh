#!/bin/bash

function log() {
	echo "$(date +%X) $1"
}

## download ffmpeg
log "Download FFMPEG"
curl -o ffmpeg.zip https://ffmpeg.zeranoe.com/builds/win64/static/ffmpeg-20190709-5a481b1-win64-static.zip
unzip ffmpeg.zip
mv ffmpeg*/ ffmpeg

## Download videos
log "Download Videos"
curl -o JaguarAndCroco720x404-375f.mp4 http://i.imgur.com/WMqwno7.mp4
curl -o GivingScholarlyFallowdeer_1280x720-415f.webm https://fat.gfycat.com/GivingScholarlyFallowdeer.webm

## Transcode it to YUV (a part only) 
./ffmpeg/bin/ffmpeg -i JaguarAndCroco720x404-375f.mp4 -vf scale=360:202 -c:v rawvideo -pix_fmt yuv420p JaguarAndCroco360x202-375f.yuv
### to vizualize ./ffmpeg/bin/ffplay -i JaguarAndCroco360x202-375f.yuv -video_size 360:202
./ffmpeg/bin/ffmpeg -i GivingScholarlyFallowdeer_1280x720-415f.webm -c:v rawvideo -pix_fmt yuv420p GivingScholarlyFallowdeer_1280x720-415f.yuv
### to vizualize ./ffmpeg/bin/ffplay -i GivingScholarlyFallowdeer_1280x720-415f.yuv -video_size 1280:720

## dowload font
curl -o DejaVuSans.ttf https://preesm.github.io/assets/downloads/DejaVuSans.ttf

pause

