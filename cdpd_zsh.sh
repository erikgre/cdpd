alias cdpd='cd $(prevwd)'

autoload -U add-zsh-hook

write_lastpwd() {
    printf '%s' "$PWD" > ~/.prevwd
}

add-zsh-hook chpwd write_lastpwd

