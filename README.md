# First Part of the Project

## Steering-Library
The objective of this lab project is to create a small “steering library” on Unreal.

## Project Status
This part of the project is finished.

## Overview
This project is a small steering library implemented in Unreal Engine. It provides various AI movement behaviors inspired by Craig Reynolds' steering behaviors.
The objective is to visualize and simulate autonomous agents moving in a dynamic environment.

## Features
The library include the following behaviors:

### Basic Behaviors:
  - ✅ Seek: The agent moves toward a fixed target.
  - ✅ Flee: The agent moves away from a fixed target.
  - ✅ Pursuit: The agent predicts and intercepts a moving target.
  - ✅ Evade: The agent predicts and avoids a pursuer.
  - ✅ Arrival: The agent moves toward a fixed target and decelerates to stop smoothly.

### Combined Behaviors:
  - ✅ Circuit: The agent follows a looping path continuously.
  - ✅ One way: The agent follows a path to a specific endpoint and stops.
  - ✅ Two ways: The agent moves to an endpoint, then reverses direction back to the start, repeating the process indefinitely.

## Usage
  Launch the project in Unreal Engine.
  Select the Lab1 level
  Control the character using:  
    - **Z, Q, S, D** keys to move.  
    - **Mouse movement** to control the camera direction.  
    - **Middle mouse button** to zoom in and out.  
  Change the AI behavior by pressing:  
   - **'&' or '1'** for **Seek** behavior.  
   - **'é' or '2'** for **Flee** behavior.  
   - **'\"' or '3'** for **Pursuit** behavior.
   - **'\'' or '4'** for **Evade** behavior.
   - **'(' or '5'** for **Arrival** behavior.
   - **'-' or '6'** for **Circuit** behavior.
   - **'è' or '7'** for **OneWay** behavior.
   - **'_' or '8'** for **TwoWay** behavior.

# Second Part of the Project

## Pathfinding
The objective of this lab project is to program both a simple planning and a path finding algorithms and make them work together.

## Project Status
This part project is currently in development. Some features may not yet be fully implemented or functional.
Future updates will include refinements, optimizations, and additional features.

## Overview
The game simulate a small city seen from above. The city contains chickens and a farm. The NPC, as well as the player, are the farmers in the city. 
They collaborate to get all the chickens to the farm as quickly as possible while following the available paths and must avoid collisions with other chickens and farmers.
There must be at least one farms in the city and there can be many chickens, that are placed randomly on the map at the beginning of the game. Once the game starts, the NPC and the
player know where the chickens and the farms are, as they can see the whole map from above. They can carry one chicken at a time to the farm. 
They can also see what each other is doing, but they cannot communicate to coordinate their actions.

## Features
the game include :
  - ✅ Pathfinding : Dijkstra algorithm.

## Usage
  Launch the project in Unreal Engine.
  Select the Lab2 level
  Control the character using:  
    - **Z, Q, S, D** keys to move.

## Steps
### 1 - Clone the repository
  - https://github.com/BaKeMoNo0/Steering-Library.git

### 2 - Generate Visual Studio project files
  - Navigate to the project folder.
  - Right-click on the .uproject file and select "Generate Visual Studio project files".

### 3 Open VS Code.
  - Right-click on the .sln file and select "Open With" -> VsCode or an other IDE
  - Compile and run the project
