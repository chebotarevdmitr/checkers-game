#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <SFML/Graphics.hpp>

// Класс для представления игрового поля
class GameBoard {
public:
    // Конструктор
    GameBoard();

    // Метод для отрисовки игрового поля
    void draw(sf::RenderWindow& window);

    // Проверка, есть ли шашка на клетке
    bool isPieceAt(int row, int col);

    // Перемещение шашки
    bool movePiece(int fromRow, int fromCol, int toRow, int toCol);

    // Получение размера клетки
    int getCellSize() const;

private:
    // Размер одной клетки
    const int cellSize = 100;

    // Цвета клеток
    sf::Color lightColor;
    sf::Color darkColor;

    // Двумерный массив для хранения состояния поля
    int boardState[8][8];

    // Метод для отрисовки клеток
    void drawCells(sf::RenderWindow& window);

    // Метод для отрисовки шашек
    void drawPieces(sf::RenderWindow& window);
};

#endif // GAMEBOARD_HPP