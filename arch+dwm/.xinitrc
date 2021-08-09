dbus-update-activation-environment --systemd DBUS_SESSION_BUS_ADDRESS DISPLAY XAUTHORITY # для работы ссылок в flatpak приложениях
#setxkbmap -layout us,ru -option grp:win_space_toggle
setxkbmap -layout us,ru -option grp:caps_toggle,grp_led:scroll
exec dwm
