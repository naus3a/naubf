# naubf
## or: NotActuallyUsingBrainFuck

For various reasons, recently I found myself writing less C++ than usual. Don't get me wrong: I'm coding a lot, in multiple languages and on different platforms, but I still miss my C++.
So today I found myself with a free hour near dinner time and I started wondering what kind of nerdy fun could fit in this hour.
Turns out that it was the perfect time frame for writing a *brainfuck* interpreter.

`naubf` is 
* *templated* because you can choose the `type` for the cells in tape
* *extendable* because you get virtual function
* *circular* because the tape is circular (i.e. if you move the pointer beyound the last cell, you find yourself on the first one)
* just a toy, because it was written to kill time while waiting for a gorgeous *aglio olio e peperoncino*
