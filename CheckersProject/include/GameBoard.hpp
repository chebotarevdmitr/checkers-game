#ifndef GAMEBOARD_HPP // Защита от повторного включения заголовочного файла
#define GAMEBOARD_HPP

#include <SFML/Graphics.hpp> // Подключаем библиотеку SFML для работы с графикой
#include <array> // Для использования массивов фиксированного размера

// Класс, представляющий игровое поле
class GameBoard {
public:
    // Конструктор класса
    GameBoard();

    // Метод для отрисовки игрового поля
    void draw(sf::RenderWindow& window);

    // Метод для проверки наличия шашки на клетке
    bool isPieceAt(int row, int col);

    // Метод для перемещения шашки
    bool movePiece(int fromRow, int fromCol, int toRow, int toCol);

    // Метод для получения размера клетки
    int getCellSize() const;

    // Метод для получения шашки на заданной клетке
    int getPieceAt(int row, int col);

    // Метод для установки координат выделенной шашки
    void setHighlightedPiece(int row, int col);

    // Метод для проверки наличия обязательных ходов
    bool hasMandatoryCapture(int player);

    // Метод для проверки возможности "съедания" из заданной позиции
    bool canCaptureFrom(int row, int col);

private:
    // Метод для отрисовки клеток игрового поля
    void drawCells(sf::RenderWindow& window);

    // Метод для отрисовки шашек
    void drawPieces(sf::RenderWindow& window);

    // Размер одной клетки (в пикселях)
    static constexpr int cellSize = 100;

    // Цвета клеток
    sf::Color lightColor; // Светлый цвет
    sf::Color darkColor;  // Темный цвет

    // Массив для хранения состояния игрового поля
    std::array<std::array<int, 8>, 8> boardState;

    // Переменная для хранения координат выделенной шашки
    sf::Vector2i highlightedPiece; // {-1, -1} означает, что шашка не выделена

    // Вспомогательный метод для проверки корректности координат
    bool isValidPosition(int row, int col);
};

#endif // GAMEBOARD_HPP