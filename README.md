# Blackjack OpenGL Project

## 🎮 Overview
Step into the world of Blackjack with this C++ simulation powered by OpenGL! This was a project for a Computer Graphics course, and was made in a relatively short amount of time.

## ✨ Features
- Complete Blackjack game logic, with additional double down and surrender actions
- OpenGL graphics
- Player and dealer hands visualized in real-time
- Dynamic deck management with shuffling and dealing
- Easy-to-extend architecture for additional features

## 🛠 Dependencies
- C++17 or higher
- OpenGL (for rendering)
- GLEW or an equivalent library for texture management
- Standard C++ libraries

## 🚀 Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/username/BlackjackSimulator.git
   ```
2. Open the project in Visual Studio (Windows) or your preferred C++ IDE.
3. Ensure OpenGL and related libraries are properly linked.
4. Build and run the project.

## 🎮 Usage
- Launch the executable to start the game.
- Control the player via keyboard inputs (see controls below) or GUI prompts.
- Dealer actions are automated following standard Blackjack rules.

## 📂 File Structure
- `PlayingCards.h` - Defines `Card` and `Deck` classes with drawing and deck management methods
- `Sprites.h` - Defines `Sprite`, `Chip`, and `Button` classes with drawing and collision methods
- `Source.cpp` - Program entry point and game loop.
- `Chips/` - Contains all chip assets
- `Cards/` - Contains all card assets
- `Misc/` - Contains miscellaneous assets

## 🎨 Acknowledgements
- OpenGL for graphics rendering
- Card & chip textures sourced from public domain assets (Author: Screaming Brain Studios, opengameart.org)
