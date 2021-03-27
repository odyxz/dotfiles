# /etc/skel/.bashrc
#
# This file is sourced by all *interactive* bash shells on startup,
# including some apparently interactive shells such as scp and rcp
# that can't tolerate any output.  So make sure this doesn't display
# anything or bad things will happen !


# Test for an interactive shell.  There is no need to set anything
# past this point for scp and rcp, and it's important to refrain from
# outputting anything in those cases.
if [[ $- != *i* ]] ; then
	# Shell is non-interactive.  Be done now!
	return
fi

TERMINAL="alacritty"
EDITOR="nvim"
GUIEDITOR="emacs"

GOPATH=$HOME/go
PATH="$PATH:$HOME/.local/bin:$GOPATH/bin:$HOME/.emacs.d/bin"

# Put your fun stuff here.

[ -f ~/.fzf.bash ] && source ~/.fzf.bash

alias vi=nvim
alias vim=nvim

alias poweroff="loginctl poweroff"
alias reboot="loginctl reboot"
alias suspend="loginctl suspend"
source "$HOME/.cargo/env"

QT_XCB_GL_INTEGRATION=none
