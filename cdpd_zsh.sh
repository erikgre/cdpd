alias cdpd='cd $(prevwd)'

autoload -U add-zsh-hook

write_prevwd() {
    printf "$PWD" > ~/.prevwd
}

add-zsh-hook chpwd write_prevwd

