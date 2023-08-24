# Project Description 📝
Chess247 is an implementation of chess made using C++ showcasing object-oriented principles and various design patterns. Created as The final project for the Spring 2023 offering of CS247.

## How to run the app ⚙️

In the root directory of the project, run the makefile:

```
make
```

Then, run the created executable named `chess`:

```
./chess
```

This will open a text-based display in the command line as well as a graphical display in a new window.


## Game Commands ⚙️

the following commands are for starting, ending and playing a game.

To start a new game, where `<white-player>` and `<black-player>` can be either `human` or `computer[1-4]`.
```
game <white-player> <black-player>
```

To make the current player resign.
```
resign
```

To make a move, where `<start-position>` is the location of the piece to move and `<end-position>` is the destination. Invalid moves prompt the user to re-enter a move. `<start-position>` and `<end-position>` should be in the form of board coordinates (i.e. e4, f6, etc).

```
move <start-position> <end-position>
```

To change the theme of the graphical board.
```
changeboard
```

To change the theme of the pieces.
```
changepieces
```

To randomly set the theme of the pieces and board.
```
random
```

## Setup Commands ⚙️
The following commands are for setup mode, which allow the user to freely modify the starting board. These commands, with the exception of the first, can only be run while in setup mode.

To enter setup mode. Note: setup mode cannot be entered once a game has begun. 
```
setup
```

To insert a piece `<piece-type>` at location `<board-position>`.
```
+ <piece-type> <board-position>
```

To remove the piece located at `<board-position>`.
```
– <board-position>
```

To set `<colour>` as the current player, where `<colour>` is either black or white.
```
= <colour>
```

To exit setup mode. 
```
done
```




