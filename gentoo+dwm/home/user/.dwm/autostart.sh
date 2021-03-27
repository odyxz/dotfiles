#!/bin/bash

#feh --bg-scale ~/Pictures/148577-most-popular-hacking-wallpaper-1920x1080-hd-for-mobile.jpg

#feh --bg-scale ~/Pictures/timothy-l-brock-UQiBY1yu8U0-unsplash.jpg

#feh --bg-scale ~/Pictures/pink-hair-anime-girl-standing-in-balcony-12.jpg

#feh --bg-scale ~/Pictures/f6GoS5A.jpg

#feh --bg-scale ~/Pictures/pexels-kaboompics-com-5969.jpg

#feh --bg-scale ~/Pictures/pexels-koolshooters-6494420.jpg 

xrandr --output eDP1 --mode 1366x768 --pos 1920x312 --rotate normal --output HDMI1 --off --output VGA1 --primary --mode 1920x1080 --pos 0x0 --rotate normal --output VIRTUAL1 --off

feh --bg-scale ~/Pictures/nadiya-ploschenko-9aAfHebHQPo-unsplash.jpg 

dwmstatus 2>&1 >/dev/null &
#let loop=0
#while true; do
#	xsetroot -name " $(date '+%b %d %a') | $(date '+%H:%M') "
#	let loop=$loop+1
#	sleep 30
#done

xset s 120
xss-lock slock
