#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QGridLayout>
#include <vector>
#include "tile.h"

/**
 * @class GameBoard
 * @brief Manages Minesweeper game logic and board layout
 * 
 * Handles mine placement, tile interactions, win/lose conditions,
 * and coordinates between tiles and game state.
 */
class GameBoard : public QWidget {
    Q_OBJECT  // Enable Qt signal/slot system

public:
    /**
     * @brief Constructs game board with specified parent
     * @param parent Parent widget for memory management
     */
    explicit GameBoard(QWidget *parent = nullptr);

    /**
     * @brief Resets game to initial state with new mine placements
     */
    void resetGame();

signals:
    /// @brief Emitted when player reveals all safe tiles
    void gameWon();
    
    /// @brief Emitted when player hits a mine
    void gameLost();

private slots:
    /**
     * @brief Handles left-click events from tiles
     * - Reveals tile content
     * - Triggers win/lose checks
     */
    void handleTileClick();
    
    /**
     * @brief Handles right-click events from tiles
     * - Cycles through flag markers (🚩/?/none)
     */
    void handleTileRightClick();

private:
    // Game configuration constants (Expert-level Minesweeper)
    static const int BOARD_WIDTH = 30;   ///< Number of columns
    static const int BOARD_HEIGHT = 16;  ///< Number of rows
    static const int NUM_MINES = 99;     ///< Total mines

    QGridLayout *gridLayout;             ///< Layout manager for tiles
    std::vector<std::vector<Tile*>> tiles; ///< 2D array of tile pointers

    /**
     * @brief Initializes board structure and tile widgets
     */
    void initializeBoard();
    
    /**
     * @brief Randomly places mines across the board
     */
    void placeMines();
    
    /**
     * @brief Calculates adjacent mine counts for all tiles
     */
    void calculateAdjacentMines();
    
    /**
     * @brief Recursively reveals tiles starting from specified position
     * @param row Vertical position (0-based)
     * @param col Horizontal position (0-based)
     */
    void revealTile(int row, int col);
    
    /**
     * @brief Reveals all mine locations (on game loss)
     */
    void revealAllMines();
    
    /**
     * @brief Validates board coordinates
     * @param row Vertical position to check
     * @param col Horizontal position to check
     * @return True if position is within board boundaries
     */
    bool isValidPosition(int row, int col) const;
    
    /**
     * @brief Checks if all non-mine tiles have been revealed
     */
    void checkWinCondition();
};

#endif // GAMEBOARD_H