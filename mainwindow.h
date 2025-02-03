#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gameboard.h"  // Include game board component

/**
 * @class MainWindow
 * @brief Main application window housing the Minesweeper game board.
 * 
 * Handles high-level game flow including win/lose states and game restarts.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT  // Required for Qt signals/slots

public:
    /**
     * @brief Constructs the main application window
     * @param parent Parent widget (nullptr for top-level window)
     */
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    /**
     * @brief Handles game termination (win or lose)
     * @param won True if player won, false if lost
     */
    void handleGameOver(bool won);

    /**
     * @brief Restarts the game with fresh mine placements
     */
    void restartGame();

private:
    GameBoard *gameBoard;  ///< Central game board widget
};

#endif // MAINWINDOW_H