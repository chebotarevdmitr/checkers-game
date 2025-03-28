#include "../include/GameBoard.hpp" // Adjusted include path to match the file location

// Конструктор
GameBoard::GameBoard() {
    lightColor = sf::Color(240, 217, 181); // Светлый цвет
    darkColor = sf::Color(181, 136, 99);  // Темный цвет
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
            if ((row + col) % 2 != 0) { // Только на тёмных клетках
                if (row < 3) { // Белые шашки
                    sf::CircleShape piece(45); // Радиус шашки
                    piece.setFillColor(whitePieceColor);
                    piece.setPosition(col * cellSize + 5, row * cellSize + 5); // Смещение для центрирования
                    window.draw(piece);
                } else if (row > 4) { // Чёрные шашки
                    sf::CircleShape piece(45); // Радиус шашки
                    piece.setFillColor(blackPieceColor);
                    piece.setPosition(col * cellSize + 5, row * cellSize + 5); // Смещение для центрирования
                    window.draw(piece);
                }
            }
        }
    }
}