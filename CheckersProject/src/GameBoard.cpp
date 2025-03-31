#include "../include/GameBoard.hpp"
#include <iostream>
// Конструктор
GameBoard::GameBoard() {
    lightColor = sf::Color(240, 217, 181); // Светлый цвет
    darkColor = sf::Color(181, 136, 99);  // Темный цвет

    // Инициализация состояния поля
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if ((row + col) % 2 != 0) { // Только на тёмных клетках
                if (row < 3) { // Белые шашки
                    boardState[row][col] = 1;
                } else if (row > 4) { // Чёрные шашки
                    boardState[row][col] = 2;
                } else {
                    boardState[row][col] = 0; // Пустая клетка
                }
            } else {
                boardState[row][col] = 0; // Пустая клетка
            }
        }
    }

    // Отладочный вывод массива boardState
    std::cout << "Initial board state:\n";
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            std::cout << boardState[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

// Метод для отрисовки игрового поля
void GameBoard::draw(sf::RenderWindow& window) {
    drawCells(window);
    drawPieces(window);
}

// Метод для отрисовки клеток
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

// Метод для отрисовки шашек
void GameBoard::drawPieces(sf::RenderWindow& window) {
    sf::Color whitePieceColor(255, 255, 255); // Белые шашки
    sf::Color blackPieceColor(0, 0, 0);      // Чёрные шашки

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (boardState[row][col] == 1) { // Белая шашка
                sf::CircleShape piece(45); // Радиус шашки
                piece.setFillColor(whitePieceColor);
                piece.setPosition(col * cellSize + 5, row * cellSize + 5); // Смещение для центрирования
                window.draw(piece);
            } else if (boardState[row][col] == 2) { // Чёрная шашка
                sf::CircleShape piece(45); // Радиус шашки
                piece.setFillColor(blackPieceColor);
                piece.setPosition(col * cellSize + 5, row * cellSize + 5); // Смещение для центрирования
                window.draw(piece);
            }
        }
    }
}

// Проверка, есть ли шашка на клетке
bool GameBoard::isPieceAt(int row, int col) {
    return boardState[row][col] != 0;
}

// Перемещение шашки
bool GameBoard::movePiece(int fromRow, int fromCol, int toRow, int toCol) {
    // Проверяем, что ход допустим (например, только по диагонали)
    if (abs(fromRow - toRow) == 1 && abs(fromCol - toCol) == 1) {
        // Обновляем состояние поля
        boardState[toRow][toCol] = boardState[fromRow][fromCol];
        boardState[fromRow][fromCol] = 0;
        return true; // Ход успешен
    }
    return false; // Ход недопустим
}

// Получение размера клетки
int GameBoard::getCellSize() const {
    return cellSize;
}