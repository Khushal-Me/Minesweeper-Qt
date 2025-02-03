#ifndef TILE_H
#define TILE_H

#include <QPushButton>

/**
 * @class Tile
 * @brief Represents an individual tile in the Minesweeper game board
 * 
 * Handles mine storage, adjacent mine counts, and mouse click interactions.
 * Inherits from QPushButton for clickable widget functionality.
 */
class Tile : public QPushButton {
    Q_OBJECT  // Required for Qt signal/slot mechanism

public:
    /**
     * @brief Constructs a tile widget
     * @param parent Parent widget for memory management
     */
    explicit Tile(QWidget *parent = nullptr);

    /**
     * @brief Sets mine status of the tile
     * @param isMine True to place a mine, false to remove
     */
    void setMine(bool isMine);

    /**
     * @brief Checks mine presence
     * @return True if tile contains mine, false otherwise
     */
    bool hasMine() const;

    /**
     * @brief Sets number of adjacent mines
     * @param count Number of mines in neighboring tiles (0-8)
     */
    void setAdjacentMines(int count);

    /**
     * @brief Gets adjacent mine count
     * @return Number of mines in neighboring tiles
     */
    int getAdjacentMines() const;

    /**
     * @brief Resets tile to initial state
     * - Removes mine
     * - Clears adjacent count
     * - Resets visual state and interactivity
     */
    void reset();

protected:
    /**
     * @brief Handles mouse click events
     * @param e Mouse event object
     * 
     * Overrides QPushButton behavior to detect right-clicks.
     * Emits rightClicked() signal for right mouse button presses.
     */
    void mousePressEvent(QMouseEvent *e) override;

signals:
    /**
     * @brief Signal emitted when tile receives right-click
     */
    void rightClicked();

private:
    bool mine;          ///< Mine presence flag
    int adjacentMines;  ///< Count of mines in adjacent tiles
};

#endif // TILE_H