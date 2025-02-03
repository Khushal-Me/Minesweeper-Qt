#include "tile.h"
#include <QMouseEvent>

/**
 * @brief Constructs a Tile with default properties
 * @param parent Parent widget for Qt's ownership system
 */
Tile::Tile(QWidget *parent) : QPushButton(parent), mine(false), adjacentMines(0) {
    setFixedSize(30, 30);  // Uniform tile size for grid consistency
    reset();  // Initialize to default state
}

/**
 * @brief Sets whether this tile contains a mine
 * @param isMine True to mark as mine, false to clear
 */
void Tile::setMine(bool isMine) {
    mine = isMine;
}

/**
 * @brief Checks if tile contains a mine
 * @return True if mine is present, false otherwise
 */
bool Tile::hasMine() const {
    return mine;
}

/**
 * @brief Sets the count of adjacent mines
 * @param count Number of mines in neighboring tiles (0-8)
 */
void Tile::setAdjacentMines(int count) {
    adjacentMines = count;
}

/**
 * @brief Gets the adjacent mine count
 * @return Number of mines in neighboring tiles
 */
int Tile::getAdjacentMines() const {
    return adjacentMines;
}

/**
 * @brief Resets tile to initial playable state
 * - Removes mine
 * - Clears adjacent count
 * - Resets visual appearance
 */
void Tile::reset() {
    mine = false;
    adjacentMines = 0;
    setText("");         // Clear any displayed text/emoji
    setEnabled(true);    // Make tile interactive again
    setStyleSheet("");   // Remove any custom styling
}

/**
 * @brief Handles mouse click events
 * @param e Mouse event object containing click details
 * 
 * - Right clicks: emit rightClicked() signal
 * - Left clicks: default QPushButton handling
 */
void Tile::mousePressEvent(QMouseEvent *e) {
    if (e->button() == Qt::RightButton) {
        emit rightClicked();  // Notify board of right-click action
    } else {
        // Handle left-click normally (triggers clicked() signal)
        QPushButton::mousePressEvent(e);
    }
}