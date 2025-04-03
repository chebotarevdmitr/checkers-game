#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <SFML/Graphics.hpp>
#include <array>

class GameBoard {
public:
    GameBoard();

    // Методы для отрисовки и взаимодействия с игровым полем
    void draw(sf::RenderWindow& window);
    bool isPieceAt(int row, int col); // Проверка наличия шашки на клетке
    bool movePiece(int fromRow, int fromCol, int toRow, int toCol); // Перемещение шашки
    int getCellSize() const; // Получение размера клетки
    int getPieceAt(int row, int col); // Получение типа шашки на клетке
    void setHighlightedPiece(int row, int col); // Выделение шашки

    // Проверка обязательных ходов
    bool hasMandatoryCapture(int player);
    bool canCaptureFrom(int row, int col);

    // Перечисление типов шашек
    enum PieceType {
        EMPTY = 0,
        WHITE_PIECE = 1,
        BLACK_PIECE = 2,
        WHITE_KING = 3,
        BLACK_KING = 4
    };

    // Превращение шашки в дамку
    void promoteToKing(int row, int col);

private:
    // Методы для отрисовки
    void drawCells(sf::RenderWindow& window);
    void drawPieces(sf::RenderWindow& window);

    // Размер клетки
    static constexpr int cellSize = 100;

    // Цвета клеток
    sf::Color lightColor;
    sf::Color darkColor;

    // Состояние игрового поля
    std::array<std::array<int, 8>, 8> boardState;

    // Координаты выделенной шашки
    sf::Vector2i highlightedPiece;

    // Вспомогательные методы
    bool isValidPosition(int row, int col);
    bool canMoveTo(int fromRow, int fromCol, int toRow, int toCol); // Проверка возможности перемещения
    bool performCapture(int fromRow, int fromCol, int toRow, int toCol); // Выполнение "съедания"
};

#endif // GAMEBOARD_HPP