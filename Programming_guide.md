# Preface

Ever wanted to program in a programming language that's more of a pain in the @ss than brainf\*ck?<br>
Ever wanted to experience near-infinite levels of frustation?<br>
If so, welcome to scoop

Note: before beginning, please check the <a href=guidelines.md>programming style document</a>

# Scoop - The programming language with just one variable

The idea behind this project was `hey, what if there was a programming language that used an 8bit unsigned integer as the ONLY variable?`

Meet `a`, the only variable (It's named `a` because I didn't want to name it Jimmy), whose values *must* be within the range of 0-255.

# Assigning values

The thing is, a programming language that does nothing... well... kinda sucks. So, to make it ~~suck even more~~ better, we can assign values to `a`


Let's see some instructions: (Note that 'number' does not mean literally the word *number*, it's just an integer)

- `add number`: Adds number to `a`, (C/C++ equivalent: a += number;) (Ex: `add 15`) <br>
- `substract number`: Substracts number from `a`, (C/C++ equivalent: a -= number;) (Ex: `substract 3`)<br>
- `min`: Sets `a` to 0<br>
- `max`: Sets `a` to 255<br>
- `set number/char`: Sets `a` to the number or to the ASCII value of the char (Ex: `set 120`)<br>
- `input`: Will wait for user input and will set `a` to its value. Note that it must be either an ASCII character or a 0-255 integer <br>
- `random`: Sets `a` to a random value between 0 and 255

Ok, so this seems pretty easy, for now, but, hey, how the heck do we output these values?

# Output

There are ~~a whole~~ **3 instructions** to get output in scoop: <br>
- `show`: prints the value of `a` in the form of a number. (Literally just cout's `a`) (Ex: `set 120 show` (Will print `120` in the console))<br>
- `print`: prints the ASCII character of `a`. (Literally just `cout << (char)a;`) (`set a print` (Will print `a` in the console))<br>
- `printline`: does the same as `print` *but* also prints a newline<br>

But making programs that only print something are pretty boring, don't you think?

What if I want to ask scoop to check conditions?

# Conditionals

In scoop we have the simple conditional, `if`.

The thing is, its working mechanisms are **very** different from the one a normal programmer is accustomed to.

First of all, the syntax is:<br>
	- `if condition instructions endif`
<br>
where `condition` may be:
	<br>- `>= number`: checks if `a` is greater or equal to `number`
	<br>- `== number`: checks if `a` is equal to `number`
	<br>- `<= number`: checks if `a` is less or equal to `number`
	<br>- `< number`: checks if `a` is less than `number`
	<br>- `> number`: checks if `a` is greater than `number`
	<br>- `!= number`: checks if `a` is differente from `number`
<br> So far, so good, but here's the first thorn in the butt:
<br> There's no `else` nor `else if`. It's not that difficult to put nested if's...or not.
<br><br> First rule of nested `if`s in scoop: only one `endif` is written in the whole block
<br> It can be better seen with an example:
<br>
```
	if >= 3
		if <= 7
		show
	endif
```
<br> Failing to do so will result in `Error: command not recognized`

# Loops

Ok, we've seen the conditionals, now we'll see the loops.
There's only one: `while`
<br>
Its syntax is: `while condition instructions endwhile` <br>
As with `if`, there's only one `endwhile` needed <br>
And the conditions are the same as with `if` <br>
Example:
```
	while <= 128
		show
	endwhile
```
<br>There's no `break` equivalent, so you must be very careful
# Tricks

A loop that always runs: `while >= 0`, as `a` will return to `0` if assined `256`
