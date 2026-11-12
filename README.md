C-snake
=======
A terminal Snake adaptation. It is not currently supported by all terminals; it was created to run in a *Windows* environment under a *Visual Studio* terminal or *CMD*.

Legend
------
```
+------------------+
|                  |
|                  |
|    ()            |
|                  |
|    [][][]        |
|                  |
|                  |
|                  |
|                  |
+------------------+
Score: 0
```

- ```|``` ```--``` ```+``` - Walls
- ```[]``` - One segment of the snake
- ```()``` - Apple 

Controls
--------
The game is not timer based. The user can control the movement of the snake by pressing the **WASD** buttons.
- **W** - Move up
- **A** - Move left
- **S** - Move down
- **D** - Move right

The program automatically takes a step in the given direction after the key-press.

In case of miss-input
---------------------
If the user presses a different key than the program interprets it as a mistake, in that case it will take a step in the latest valid direction punishing the user.
The same will happen if the given direction is the opposite of the current direction of the snake.
For example, if the snake is going right, by pressing the **A** key and ordering it to move left, the snake will move right again.

If the input is not an *ASCII* character, it will count as multiple steps.
