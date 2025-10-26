# Search Algorithm Visual Pathfinder
This application allows you to time and visually represent DFS, BFS, AStar, and Dijkstra's algorithms in a 255x255 maximum sized grid. Mazes can be fully custom built with walls, a start, and an end location, or mazes can be loaded in from various templates as well. The program is completely user friendly which entails preventing the creation of unfindable paths, requiring start and stop points, and not being able to annoyingly paint over your desired points. Test cases are also provided that were used throughout the development of this project to provide quality ensurance.

![Early stages of the visualization engine](https://github.com/Tugston/Search-Algorithm-Visual-Pathfinder/blob/main/docs/images/InitialCommitState.png?raw=true)

## Development Process & Optimizations

**Tech Used:** C++ & SFML

I started out by splitting the application into three seperate projects. The core is obviously the Algorithms folder. Secondly is the visualization engine which implements a cell-grid system. Each cell is 23 bytes in size. The sfml rectangle pointer (8 bytes, only build available is 64bit), and the sfml vector2f (8 bytes, 2xfloats) take up the majority of the space. I utilized a total of 7 bytes myself for the cells positioning, ID, and state. There are also static variables for cell settings which of course go in the data segment and I am not really counting.

The grid is made up of a dynamic amount of cells (specified by command line arguments, but supports up to 255x255). The cells persist in a 1d array that is then mapped to 2D positions. Apart from the vector of cells, grid only contains 14 bytes for the dimensions, window size, and min window size. Honestly I could do away with the window size values, but the grid is really only meant to be a singleton (although its not defined as one, and so its no big deal I guess).

The application itself controls the branch between the algorithm project and this visualization engine. So far it contains the grid and handles all the input for the application. Still working on this as of 10/25/2025.

## Lessons Learned

**Under Construction**