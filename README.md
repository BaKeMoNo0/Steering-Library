# Steering-Library
The objective of this lab project is to create a small “steering library” on Unreal.

# Project Status
This project is currently in development. Some behaviors may not yet be fully implemented or functional.
Future updates will include refinements, optimizations, and additional features.

# Overview
This project is a small steering library implemented in Unreal Engine. It provides various AI movement behaviors inspired by Craig Reynolds' steering behaviors.
The objective is to visualize and simulate autonomous agents moving in a dynamic environment.
⚠️ This project is still in development, and not all behaviors are fully implemented yet.

# Features
The library aims to include the following behaviors (Work in Progress 🚧):

## Basic Behaviors:
  - ✅ Seek: The agent moves toward a fixed target.
  - ✅ Flee: The agent moves away from a fixed target.
  - ✅ Pursuit: The agent predicts and intercepts a moving target.  (Might be changed)
  - ❌ Evade: The agent predicts and avoids a pursuer. (Not yet implemented)
  - ❌ Arrival: The agent moves toward a fixed target and decelerates to stop smoothly. (Not yet implemented)

## Combined Behaviors:
  - ❌ Circuit: The agent follows a looping path continuously. (Not yet implemented)
  - ❌ One way: The agent follows a path to a specific endpoint and stops. (Not yet implemented)
  - ❌ Two ways: The agent moves to an endpoint, then reverses direction back to the start, repeating the process indefinitely. (Not yet implemented)

# Steps
  - Clone the repository: https://github.com/BaKeMoNo0/Steering-Library.git
  - Open Unreal Engine and navigate to the cloned project folder.
  - Open the .uproject file and allow Unreal Engine to rebuild necessary files if prompted.
  - Compile and launch the project.

# Usage
  Launch the project in Unreal Engine.
  Press Play to observe the behaviors in action.
  Control the character using:  
    - **Z, Q, S, D** keys to move.  
    - **Mouse movement** to control the camera direction.  
    - **Middle mouse button** to zoom in and out.  
  Change the AI behavior by pressing:  
   - **'&' or '1'** for **Seek** behavior.  
   - **'é' or '2'** for **Flee** behavior.  
   - **'\"' or '3'** for **Pursuit** behavior.
