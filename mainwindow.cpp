#include "mainwindow.h"
#include <QMessageBox>
#include <QVBoxLayout>

/**
 * @brief Constructs the main window and initializes game components.
 * @param parent Parent widget (nullptr for top-level window)
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Window configuration
    setWindowTitle("Minesweeper");
    
    // Create and configure game board
    gameBoard = new GameBoard(this);
    setCentralWidget(gameBoard);  // Set as central widget
    
    // Connect game outcome signals to handler
    connect(gameBoard, &GameBoard::gameWon, this, [this]() { handleGameOver(true); });
    connect(gameBoard, &GameBoard::gameLost, this, [this]() { handleGameOver(false); });
    
    // Set initial window dimensions
    resize(800, 600);  // Width x Height in pixels
}

/**
 * @brief Handles game termination scenarios (win/lose)
 * @param won True if player won, false if lost
 */
void MainWindow::handleGameOver(bool won) {
    QMessageBox msgBox;
    msgBox.setWindowTitle(won ? "Congratulations!" : "Game Over");
    msgBox.setText(won ? "You won! Would you like to play again?" 
                      : "You hit a mine! Would you like to try again?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    
    // Show dialog and handle response
    if (msgBox.exec() == QMessageBox::Yes) {
        restartGame();
    } else {
        close();  // Exit application
    }
}

/**
 * @brief Restarts the game by resetting the game board
 */
void MainWindow::restartGame() {
    gameBoard->resetGame();  // Delegate reset to game board
}