#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <SFML/Graphics.hpp>
#include <array>

class GameBoard {
public:
    // Конструктор класса
    GameBoard();

    // Методы для отрисовки и взаимодействия с игровым полем
    void draw(sf::RenderWindow& window); // Отрисовка игрового поля
    bool isPieceAt(int row, int col);    // Проверка наличия шашки на клетке
    bool movePiece(int fromRow, int fromCol, int toRow, int toCol); // Перемещение шашки
    int getCellSize() const;             // Получение размера клетки
    int getPieceAt(int row, int col);    // Получение типа шашки на клетке
    void setHighlightedPiece(int row, int col); // Установка координат выделенной шашки

private:
    static constexpr int cellSize = 100; // Размер одной клетки
    sf::Color lightColor;               // Светлый цвет клеток
    sf::Color darkColor;                // Темный цвет клеток
    std::array<std::array<int, 8>, 8> boardState; // Состояние игрового поля
    sf::Vector2i highlightedPiece;      // Координаты выделенной шашки

    // Вспомогательные методы
    bool isValidPosition(int row, int col); // Проверка корректности позиции
    bool canMoveTo(int fromRow, int fromCol, int toRow, int toCol); // Проверка возможности перемещения
    bool performCapture(int fromRow, int fromCol, int toRow, int toCol); // Выполнение "съедания"
    bool performMultipleCaptures(int fromRow, int fromCol, int toRow, int toCol); // Множественное "съедание"
    void promoteToKing(int row, int col); // Превращение шашки в дамку

    // Методы для отрисовки
    void drawCells(sf::RenderWindow& window); // Отрисовка клеток
    void drawPieces(sf::RenderWindow& window); // Отрисовка шашек

    // Перечисление типов шашек
    enum PieceType {
        EMPTY = 0,         // Пустая клетка
        WHITE_PIECE = 1,   // Белая шашка
        BLACK_PIECE = 2,   // Чёрная шашка
        WHITE_KING = 3,    // Белая дамка
        BLACK_KING = 4     // Чёрная дамка
    };
};

#endif // GAMEBOARD_HPP