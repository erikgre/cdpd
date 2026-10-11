alias cdpd='cd $(prevwd)'

cd() {
    builtin cd "$@" || return
    printf "%s" "$PWD" > ~/.prevwd
}
