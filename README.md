
# BEAD 12 Project - Bead Game

## Introduction

The BEAD 12 project is a console-based bead game implemented in C++. The game features a board where two players, Green and Red, can place their beads and perform moves according to specific rules. The project demonstrates basic principles of game development, including board management, user interaction, and game logic. This document provides a comprehensive overview of the project's features, functionality, and underlying computer intelligence.

## Features

- **Console-based Interface**: The game runs in a console window with text-based graphics.
- **Board Initialization**: The game board is initialized based on a configuration file or user input.
- **Player Interaction**: Players can place beads, move them, and remove them through mouse clicks.
- **Game Logic**: Implements game rules for valid moves, jumps, and win conditions.
- **Score Display**: Keeps track of and displays player scores.
- **Game State Saving**: The game saves its state after every move, allowing players to resume the game from the last saved state.
- **Load Game Feature**: Players can load a previously saved game to continue playing from where they left off.

## Console Settings

For optimal display and interaction with the game, configure your console with the following settings:
- **Font**: Raster
- **Font Size**: 8x8
- **Console Width**: 120 columns
- **Console Height**: 80 rows

These settings ensure that the game board and interface elements are properly rendered and visible.

## Getting Started

### Prerequisites

- A C++ compiler (e.g., g++, MSVC)
- Windows operating system for using the `Windows.h` library
- Basic understanding of C++ and console programming

### Building the Project

1. **Clone the Repository**
   ```bash
   git clone <repository-url>
   ```
2. **Compile the Code**
   ```bash
   g++ -o bead12 bead12.cpp
   ```
   Ensure that your environment supports the Windows-specific libraries used in the code.

### Running the Game

1. **Execute the Program**
   ```bash
   bead12
   ```
2. **Follow the Prompts**: Input player names, select positions, and interact with the game using the mouse.

## Code Structure

### Main Components

- **Board Initialization**
  - `init()` and `initComp()` functions load the board configuration and initialize player details.
  
- **Board Rendering**
  - Functions such as `Board()`, `Printdata()`, `printBeads()`, and `RemoveBead()` handle drawing and updating the board.

- **Game Logic**
  - Functions like `selectPosition()`, `isValidSource()`, `isValidDestination()`, and various jump validation functions ensure that moves adhere to the game rules.

- **User Interaction**
  - `getRowColbyLeftClick()` captures mouse clicks to determine bead placement and movement.

### Key Functions

- `SetClr(int tcl, int bcl)`: Sets the color for console text.
- `gotoRowCol(int rpos, int cpos)`: Moves the console cursor to a specific position.
- `Circle(int h, int k, float radius, char sym, int clr)`: Draws a circle on the console.
- `bead(int h, int k, int clr)`: Draws a bead at a specified location.
- `updadteBoard(char** Board, Position source, Position destination)`: Updates the board state based on player moves.
- `TurnAndScoreMessage(string Names[], int turn, int Boxdim, int count[])`: Displays the current turn and score.

## Computer Intelligence

### Game Logic

The game incorporates several logical checks to ensure valid moves and actions. This includes:

- **Movement Validity**: Functions like `isValidSource()` and `isValidDestination()` check whether a move is permissible based on the current state of the board and the turn of the player.
- **Jump Validity**: Functions such as `isVerticalJump()` and `isHorizontalJump()` determine if a bead can jump over another bead according to the rules.
- **Win Condition**: The `WinMessage()` function announces the winner when a player achieves the game’s winning condition.

### Decision Making

The computer version of the game uses a rule-based algorithm to manage game decisions. Here's a brief overview of how it works:

1. **Move Validation**: The algorithm first verifies the validity of the source and destination positions using the `isValidSource()` and `isValidDestination()` functions. It checks if the move is allowed according to the game rules.
2. **Jump Checking**: The algorithm evaluates possible jumps using `isVerticalJump()` and `isHorizontalJump()`. It ensures that jumps are valid and comply with game regulations.
3. **Game State Update**: Upon confirming a valid move or jump, the game state is updated using `updadteBoard()`. The board reflects the new positions of the beads.
4. **Winning Condition**: After each move or jump, the algorithm checks if any player has met the winning conditions using `WinMessage()`.

The decision-making process is entirely rule-based, relying on predefined conditions to validate and execute moves. This ensures that all player actions adhere to the game's rules and that the game progresses correctly.

## Game State Management

- **Saving Game State**: The game automatically saves its state after every move. This includes the positions of all beads, current player turn, and scores. The saved state allows players to resume the game from where they left off in case of interruption or if they wish to continue later.
- **Loading Game State**: Players can load a previously saved game by selecting the load option from the menu. This feature ensures that players can pick up right where they left off without losing progress.

## Usage

1. **Start the Game**: Run the executable and follow the prompts to start a new game or load an existing game from a file.
2. **Interact with the Board**: Click on the board to place and move beads. The game will handle the rendering and updating of the board state.
3. **Check Scores**: The current score and turn information will be displayed on the console.

## Troubleshooting

- **Console Not Displaying Properly**: Ensure you are running the game in a compatible Windows environment with support for console color attributes.
- **Compilation Errors**: Verify that all required libraries and headers are available and that the code is compiled with the appropriate settings for Windows.

## Future Enhancements

- **Graphical User Interface (GUI)**: Implementing a GUI for a more user-friendly experience.
- **Enhanced AI**: Adding computer-controlled opponents with advanced decision-making algorithms.
- **Multiplayer Support**: Expanding to support online multiplayer functionality.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments

- **Libraries**: Utilizes the Windows API for console manipulation.
- **Inspiration**: Inspired by classic board games and console-based applications.

