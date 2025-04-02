#include "../include/GameBoard.hpp"
#include <iostream>

GameBoard::GameBoard() : highlightedPiece{-1, -1} {
    lightColor = sf::Color(240, 217, 181);
    darkColor = sf::Color(181, 136, 99);

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if ((row + col) % 2 != 0) {
                if (row < 3) {
                    boardState[row][col] = WHITE_PIECE;
                } else if (row > 4) {
                    boardState[row][col] = BLACK_PIECE;
                } else {
                    boardState[row][col] = EMPTY;
                }
            } else {
                boardState[row][col] = EMPTY;
            }
        }
    }
}

void GameBoard::draw(sf::RenderWindow& window) {
    drawCells(window);
    drawPieces(window);

    if (highlightedPiece.x != -1 && highlightedPiece.y != -1) {
        sf::RectangleShape highlight(sf::Vector2f(cellSize, cellSize));
        highlight.setFillColor(sf::Color::Transparent);
        highlight.setOutlineThickness(4);
        highlight.setOutlineColor(sf::Color::Yellow);
        highlight.setPosition(highlightedPiece.y * cellSize, highlightedPiece.x * cellSize);
        window.draw(highlight);
    }
}

void GameBoard::drawCells(sf::RenderWindow& window) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(col * cellSize, row * cellSize);

            if ((row + col) % 2 == 0) {
                cell.setFillColor(lightColor);
            } else {
                cell.setFillColor(darkColor);
            }

            window.draw(cell);
        }
    }
}

void GameBoard::drawPieces(sf::RenderWindow& window) {
    sf::Color whitePieceColor(255, 255, 255);
    sf::Color blackPieceColor(0, 0, 0);
    sf::Color kingColor(255, 215, 0);

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (boardState[row][col] == WHITE_PIECE || boardState[row][col] == BLACK_PIECE) {
                sf::CircleShape piece(45);
                piece.setFillColor(boardState[row][col] == WHITE_PIECE ? whitePieceColor : blackPieceColor);
                piece.setPosition(col * cellSize + 5, row * cellSize + 5);
                window.draw(piece);
            } else if (boardState[row][col] == WHITE_KING || boardState[row][col] == BLACK_KING) {
                sf::CircleShape piece(45);
                piece.setFillColor(kingColor);
                piece.setPosition(col * cellSize + 5, row * cellSize + 5);
                window.draw(piece);
            }
        }
    }
}

bool GameBoard::isPieceAt(int row, int col) {
    return boardState[row][col] != EMPTY;
}

bool GameBoard::movePiece(int fromRow, int fromCol, int toRow, int toCol) {
    int piece = boardState[fromRow][fromCol];
    bool isKing = (piece == WHITE_KING || piece == BLACK_KING);

    int rowDir = (toRow - fromRow > 0) ? 1 : -1;
    int colDir = (toCol - fromCol > 0) ? 1 : -1;

    if (isKing) {
        int steps = std::max(abs(toRow - fromRow), abs(toCol - fromCol));
        for (int step = 1; step < steps; ++step) {
            int midRow = fromRow + step * rowDir;
            int midCol = fromCol + step * colDir;

            if (boardState[midRow][midCol] != EMPTY) {
                return false;
            }
        }
    } else {
        if (abs(fromRow - toRow) != 1 || abs(fromCol - toCol) != 1) {
            return false;
        }
    }

    if (abs(fromRow - toRow) == 2 && abs(fromCol - toCol) == 2) {
        int midRow = (fromRow + toRow) / 2;
        int midCol = (fromCol + toCol) / 2;

        if (boardState[midRow][midCol] == EMPTY || boardState[midRow][midCol] == piece) {
            return false;
        }

        boardState[midRow][midCol] = EMPTY;
    }

    boardState[toRow][toCol] = piece;
    boardState[fromRow][fromCol] = EMPTY;

    promoteToKing(toRow, toCol);

    return true;
}

int GameBoard::getCellSize() const {
    return cellSize;
}

int GameBoard::getPieceAt(int row, int col) {
    return boardState[row][col];
}

void GameBoard::setHighlightedPiece(int row, int col) {
    highlightedPiece = {row, col};
}

bool GameBoard::hasMandatoryCapture(int player) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (boardState[row][col] == player) {
                int directions[4][2] = {{-2, -2}, {-2, 2}, {2, -2}, {2, 2}};
                for (auto& dir : directions) {
                    int toRow = row + dir[0];
                    int toCol = col + dir[1];
                    int midRow = row + dir[0] / 2;
                    int midCol = col + dir[1] / 2;

                    if (isValidPosition(toRow, toCol) && boardState[toRow][toCol] == EMPTY &&
                        boardState[midRow][midCol] != EMPTY && boardState[midRow][midCol] != player) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool GameBoard::canCaptureFrom(int row, int col) {
    int player = boardState[row][col];
    int directions[4][2] = {{-2, -2}, {-2, 2}, {2, -2}, {2, 2}};

    for (auto& dir : directions) {
        int toRow = row + dir[0];
        int toCol = col + dir[1];
        int midRow = row + dir[0] / 2;
        int midCol = col + dir[1] / 2;

        if (isValidPosition(toRow, toCol) && boardState[toRow][toCol] == EMPTY &&
            boardState[midRow][midCol] != EMPTY && boardState[midRow][midCol] != player) {
            return true;
        }
    }
    return false;
}

bool GameBoard::isValidPosition(int row, int col) {
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}

void GameBoard::promoteToKing(int row, int col) {
    int piece = boardState[row][col];
    if (piece == WHITE_PIECE && row == 7) {
        boardState[row][col] = WHITE_KING;
    } else if (piece == BLACK_PIECE && row == 0) {
        boardState[row][col] = BLACK_KING;
    }
}