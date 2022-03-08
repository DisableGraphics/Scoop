# Scoop

The programming language with just one variable

# Compiling

Just `make` in the project directory

# Programming in scoop
see <a href=Programming_guide.md>The programming guide for details</a>

# The programs

In the build/ directory there are 3 programs:
- `scoop-interpreter`: Launches a scoop "shell" and lets the user introduce commands. More or less the same as executing `python` without any arguments
- `scoop-file-interpreter`: Runs a file
- `string-to-scoop`: Since it's a pain in the @ss to write manually the whole `set value print` to write a string, I made a little program to help. The problem is that it ends up obfuscating the string far too much, but otherwise highly recommended
