#include "gameboard.h"
#include <QMessageBox>
#include <random>
#include <algorithm>
#include <chrono>

//--------------------------------------------------------------
// Constructor & Initialization
//--------------------------------------------------------------

/**
 * @brief Constructs the game board and initializes core components
 * @param parent Parent widget for memory management
 */
GameBoard::GameBoard(QWidget *parent) : QWidget(parent) {
    // Configure grid layout with minimal spacing between tiles
    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(1);
    setLayout(gridLayout);
    
    initializeBoard();  // Create tile grid
    resetGame();        // Start initial game session
}

/**
 * @brief Creates and arranges tile widgets in grid layout
 */
void GameBoard::initializeBoard() {
    tiles.resize(BOARD_HEIGHT);
    for (int row = 0; row < BOARD_HEIGHT; ++row) {
        tiles[row].resize(BOARD_WIDTH);
        for (int col = 0; col < BOARD_WIDTH; ++col) {
            // Create new tile and add to layout
            Tile* tile = new Tile(this);
            tiles[row][col] = tile;
            gridLayout->addWidget(tile, row, col);
            
            // Connect tile signals to board handlers
            connect(tile, &Tile::clicked, this, &GameBoard::handleTileClick);
            connect(tile, &Tile::rightClicked, this, &GameBoard::handleTileRightClick);
        }
    }
}

//--------------------------------------------------------------
// Game Logic & State Management
//--------------------------------------------------------------

/**
 * @brief Resets game to initial state with new mine configuration
 */
void GameBoard::resetGame() {
    // Reset all tiles to default state
    for (auto& row : tiles) {
        for (auto& tile : row) {
            tile->reset();
        }
    }
    placeMines();              // Randomize mine positions
    calculateAdjacentMines();  // Update adjacent mine counts
}

/**
 * @brief Randomly distributes mines across the board
 */
void GameBoard::placeMines() {
    std::vector<std::pair<int, int>> positions;
    // Generate all possible coordinate pairs
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            positions.emplace_back(i, j);
        }
    }
    
    // Shuffle coordinates using time-based seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(positions.begin(), positions.end(), std::default_random_engine(seed));
    
    // Assign mines to first NUM_MINES positions
    for (int i = 0; i < NUM_MINES; ++i) {
        int row = positions[i].first;
        int col = positions[i].second;
        tiles[row][col]->setMine(true);
    }
}

/**
 * @brief Calculates adjacent mine counts for all non-mine tiles
 */
void GameBoard::calculateAdjacentMines() {
    for (int row = 0; row < BOARD_HEIGHT; ++row) {
        for (int col = 0; col < BOARD_WIDTH; ++col) {
            if (!tiles[row][col]->hasMine()) {
                int count = 0;
                // Check all 8 neighboring positions
                for (int i = -1; i <= 1; ++i) {
                    for (int j = -1; j <= 1; ++j) {
                        if (i == 0 && j == 0) continue; // Skip current tile
                        int newRow = row + i;
                        int newCol = col + j;
                        if (isValidPosition(newRow, newCol) && tiles[newRow][newCol]->hasMine()) {
                            count++;
                        }
                    }
                }
                tiles[row][col]->setAdjacentMines(count);
            }
        }
    }
}

//--------------------------------------------------------------
// Tile Interaction Handlers
//--------------------------------------------------------------

/**
 * @brief Handles left-click events on tiles
 * - Reveals tile contents
 * - Triggers win/lose conditions
 */
void GameBoard::handleTileClick() {
    Tile* tile = qobject_cast<Tile*>(sender());
    if (!tile) return;
    
    // Find clicked tile's position
    int row = -1, col = -1;
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            if (tiles[i][j] == tile) {
                row = i;
                col = j;
                break;
            }
        }
        if (row != -1) break;
    }
    
    if (tile->hasMine()) {
        revealAllMines();  // Expose all mines on loss
        emit gameLost();
    } else {
        revealTile(row, col);  // Recursive reveal
        checkWinCondition();
    }
}

/**
 * @brief Handles right-click events for marking tiles
 * - Cycles through flag states: 🚩 → ? → none
 */
void GameBoard::handleTileRightClick() {
    Tile* tile = qobject_cast<Tile*>(sender());
    if (!tile) return;
    
    if (tile->text().isEmpty()) {
        tile->setText("🚩");  // Flag as suspected mine
    } else if (tile->text() == "🚩") {
        tile->setText("?");   // Mark as uncertain
    } else {
        tile->setText("");    // Clear markings
    }
}

//--------------------------------------------------------------
// Game Mechanics
//--------------------------------------------------------------

/**
 * @brief Recursively reveals tiles from specified position
 * @param row Vertical coordinate (0-based)
 * @param col Horizontal coordinate (0-based)
 */
void GameBoard::revealTile(int row, int col) {
    if (!isValidPosition(row, col)) return;
    
    Tile* tile = tiles[row][col];
    // Skip already revealed or marked tiles
    if (!tile->isEnabled() || !tile->text().isEmpty()) return;
    
    tile->setEnabled(false);  // Mark as revealed
    
    if (tile->getAdjacentMines() > 0) {
        // Show adjacent mine count
        tile->setText(QString::number(tile->getAdjacentMines()));
    } else {
        // Recursively reveal adjacent tiles
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                revealTile(row + i, col + j);
            }
        }
    }
}

/**
 * @brief Reveals all mine locations (triggered on loss)
 */
void GameBoard::revealAllMines() {
    for (int row = 0; row < BOARD_HEIGHT; ++row) {
        for (int col = 0; col < BOARD_WIDTH; ++col) {
            if (tiles[row][col]->hasMine()) {
                tiles[row][col]->setText("💣");
                tiles[row][col]->setEnabled(false);
            }
        }
    }
}

/**
 * @brief Validates grid coordinates
 * @param row Vertical position to check
 * @param col Horizontal position to check
 * @return True if position is within board boundaries
 */
bool GameBoard::isValidPosition(int row, int col) const {
    return row >= 0 && row < BOARD_HEIGHT && col >= 0 && col < BOARD_WIDTH;
}

/**
 * @brief Checks if all non-mine tiles have been revealed
 */
void GameBoard::checkWinCondition() {
    for (const auto& row : tiles) {
        for (const auto& tile : row) {
            // If any safe tile remains hidden, game continues
            if (!tile->hasMine() && tile->isEnabled()) {
                return;
            }
        }
    }
    emit gameWon();  // All safe tiles revealed
}