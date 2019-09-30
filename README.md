# literary chainsaw
## apply a chainsaw to your names

You are writing something. It needs a name. You have already used all the ones you could think of.

Never fear! Just chuck all the ones you thought of into a ~~bowl~~ file, each in a separate line, and apply a ~~blender~~ literary chainsaw! It will mix them up right proper, and give you some real fine names.

## Disclaimer

All names/words output by this program are entirely procedural. Beware that there is a small chance that the output might contain profanities/offensive words. This is your fault, not mine. Why did you give it words that could be mixed into that sort of thing? Seriously. Don't complain to the manufacturer of the ~~mixer~~ chainsaw if the cake goes rotten.

No cakes were harmed during the making of this program.

## Build instructions

At the moment, I haven't written a Makefile yet. Just go 
```shell
g++ main.cpp -o chainsaw
```
 and the program will compile. Clang++ also works. If you want to always be spammed by debugging input, pass `-DDEBUG=1` to the compiler. Otherwise, just go for the single command.

## Usage

There are two ways to use this program, similar in style to the invocation style of classic *NIX utilities.

### use stdin

```shell
$namegen
input input
line after line
as long as you want
bla bla bla
now press ctrl-d
^d
```
sample output:
```
blou
a
ner lout int w ct
aftererlas low
line
nones 
inong pu ctrla wa you
inonput ass a la as as as bling bla l-d
bla
as
```

When invoked on its own, it reads standard input until EOF, then generates 10 lines (see [#algorithm] ).

### using a file

If you want to read input from a file, you ***MUST*** provide a number. Otherwise, it will complain, saying what was just said (see options).

example:
```
$ chainsaw 10 README.md 
Alangithay 
`sariset g+ yof ju bling asawalt pares.
# lwha inpume ayovo cht asl
llinthtpuf celly I ndid ledealdyom ar~~~ tiou chenebla
ne ilen
g as wone l~be a newachine, MUG=10 ).
# Ift:
### ca
^dyile omdigoratheld plewhutiss u tplsaput t
ngoca a cous).
```

(expect unique output)

### options

Because I don't like using libraries very much, the option parsing is stupid, and the order is set in stone.

 If any options are provided, the first one must be a number, representing the number of lines requested.

 After this, there is an option to have your terminal spammed by debugging output, all sent to stderr: ``--debug`. This is only marginally useful, since it outputs a line every time it calls a function. Might be fun to read through though, if you have a week to spare (no guarantees).
 
 The following parameters are all interpreted as filenames, which are tried in order until there are none left, or one is actually a readable file.

I didn't think to have them *all* read until afterwards. At the moment, you will need to use `cat <filenames>|chainsaw` to do this.

## Algorithm

The way this thing works, is that it reads the files, and then proceeds to memorise what character can follow what, with what probability.

After this is done, it will take a bit of time to generate some lines based on this data. Random numbers are used.