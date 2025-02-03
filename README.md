# Qt Minesweeper 💣

A classic Minesweeper implementation using the Qt framework. Compatible with Windows and macOS.

## 🛠 Prerequisites

### Required Software
- **Qt 5.15+** – [Download Qt](https://www.qt.io/download)
- **C++ Compiler**
  - Windows: MinGW/MSVC (included with the Qt installer)
  - macOS: Xcode Command Line Tools (`xcode-select --install`)

## 🚀 Building & Running

### 🖥 Windows

1. Clone the repository
   ```bash
   git clone https://github.com/Khushal-Me/Minesweeper-Qt.git
   ```

2. Generate Makefile
   ```bash
   ./minesweeper.exe
   ```

### 🍏 macOS

1. Clone the repository
   ```bash
   git clone https://github.com/Khushal-Me/Minesweeper-Qt.git
   cd minesweeper
   ```

2. Generate Makefile
   ```bash
   qmake minesweeper.pro
   ```

3. Build the project
   ```bash
   make
   ```

4. (Optional) Create an app bundle
   ```bash
   macdeployqt minesweeper.app
   ```

5. Run the game
   ```bash
   open minesweeper.app
   ```

## 🎮 Gameplay

- **Left-click**: Reveal tile
- **Right-click**: Cycle markers (🚩 → ? → clear)
- **Win Condition**: Clear all non-mine tiles
- **Lose Condition**: Click on any mine
