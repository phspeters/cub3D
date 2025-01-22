<h1 align="center">
	🎲 cub3D
</h1>

## 💡 About the project

This project is inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to make a dynamic view inside a maze, in which you’ll have to find your way.

## 📝 Requirements

**Mandatory Part:**

- Display different wall textures (the choice is yours) that vary depending on which side the wall is facing (North, South, East, West).
- Your program must be able to set the floor and ceiling colors to two different ones.
- Your program must take as a first argument a scene description file with the .cub extension:
  	- The map must be composed of only 6 possible characters: 0 for an empty space, 1 for a wall, and N,S,E or W for the player’s start position and spawning orientation.
    - The map must be closed/surrounded by walls, if not the program must return an error.
	- Except for the map content, each type of element can be separated by one or more empty line(s).
	- Except for the map content which always has to be the last, each type of element can be set in any order in the file.
	- Except for the map, each type of information from an element can be separated by one or more space(s).
	- The map must be parsed as it looks in the file. Spaces are a valid part of the map and are up to you to handle. You must be able to parse any kind of map, as long as it respects the rules of the map.
	- Each element (except the map) firsts information is the type identifier (composed by one or two character(s)), followed by all specific informations for each object in a strict orde
	- If any misconfiguration of any kind is encountered in the file, the program must exit properly and return "Error\n" followed by an explicit error message of your choice.
- The program displays the image in a window and respects the following rules:
	- The left and right arrow keys of the keyboard must allow you to look left and right in the maze.
	- The W, A, S, and D keys must allow you to move the point of view through the maze.
	- Pressing ESC must close the window and quit the program cleanly.
	- Clicking on the red cross on the window’s frame must close the window and quit the program cleanly.

**Bonus Part:**

- Wall collisions.
- A minimap system.
- Doors which can open and close.
- Animated sprite.
- Rotate the point of view with the mouse.

## 📋 Testing

To compile, navigate to the project directory and run:

```shell
$ make 
```

Then, execute the program with the path of the map chosen as your second argument:

```shell
$ ./cub3D maps/valid/subject.cub
```

## 🕹️ Playing

- The left and right arrow keys of the keyboard allow you to look left and right in the maze.
- The W, A, S, and D keys allow you to move the point of view through the maze.
- The SPACEBAR and Left Mouse Button perform actions (Interect with ghosts and doors)
- Right Mouse Button toggles mouse camera movement
- The M key toggles the minimap
- Pressing ESC close the window and quit the program.
