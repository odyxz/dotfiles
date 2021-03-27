# /etc/skel/.bash_profile

# This file is sourced by bash for login shells.  The following line
# runs your .bashrc and is recommended by the bash info pages.
if [[ -f ~/.bashrc ]] ; then
	. ~/.bashrc
fi
if [ -e /home/user/.nix-profile/etc/profile.d/nix.sh ]; then . /home/user/.nix-profile/etc/profile.d/nix.sh; fi # added by Nix installer

source "$HOME/.cargo/env"

# opam configuration
test -r /home/user/.opam/opam-init/init.sh && . /home/user/.opam/opam-init/init.sh > /dev/null 2> /dev/null || true

if [ -z "${DISPLAY}" ] && [ "${XDG_VTNR}" -eq 1 ]; then
  exec startx
fi

_JAVA_AWT_WM_NONREPARENTING=1
