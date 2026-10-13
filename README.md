# cdpd
## Change directory previous directory

cdpd is a simple shell utility  that changes directory to the previous one.<br>
It differs from "cd -" in one key aspect, it works between shells.<br>
You can work in a directory, open a new shell, and immediately<br>
start working in the same directory.<br>


## Compiling and installing

In order to compile it, simply type<br>
```console
make
```

In order to place files into appropriate folders and such, type<br>
```console
sudo make install
```
(If you are planning on running "sudo make install", you can skip the first step)

You then have to add the following line into your .bashrc or .zshrc or whatever<br>
```shell
source /usr/share/cdpd/cdpd.sh
```

## Usage
cdpd includes two binaries:<br>
```console
prevwd
```
And<br>
```console
here [path]
```

It also includes the command:<br>
```console
cdpd
```
Of the three, only here and cdpd is actually supposed to be used.<br>
"here" marks the PWD or \[path] as the latest directory<br>
"cdpd" is the main command that changes directory<br>
It is actually just an alias<br>
```shell
alias cdpd='cd $(prevwd)'
```

## Disclaimer
This could all be done with just shell scripts.<br>
But i wanted to write some C
