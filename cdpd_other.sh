alias cdpd='builtin cd $(prevwd)'

cd() {
    builtin cd "$@" || return
    printf "%s" "$PWD" > ~/.prevwd
}
