# Preface
To be honest, you can put everything in a single line and tell the source reader to begin a ~~pretty long, if you ask me~~ horizontal journey, but it's not practical
<br>
<br>
This guide will follow the recommended programming style for scoop, but you are perfectly allowed to create your custom style without any issue

# Indentation

Just a single tab (Or 4 spaces) when opening blocks is fine
<br> Example:<br>
```
if >= 0
    if <= 3
    show
endif
```

# Printing messages in the screen

Ok, this is a bit more difficult. I recommend this structure per line: `set value print`,
because not doing so will end up making lines far too large.
Example:<br>
`set h print` <br>
`set e print` <br>
`set l print print` <br>
`set o print`<br>
Note how `l` has been printed in the screen two times, being assigned just one. Another `set l` would be redundant.

<br>Redundant instructions will be considered bad practice
