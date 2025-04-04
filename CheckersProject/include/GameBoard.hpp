#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <SFML/Graphics.hpp>
#include <array>

class GameBoard {
public:
    // Конструктор класса
    // Инициализирует игровое поле, цвета клеток и начальное состояние игры.
    GameBoard();

    // Отрисовка игрового поля
    // Вызывает методы для отрисовки клеток и шашек, а также выделение выбранной шашки.
    void draw(sf::RenderWindow& window);

    // Проверка наличия шашки на клетке
    // Возвращает true, если на указанной клетке есть шашка (не пустая).
    bool isPieceAt(int row, int col);

    // Перемещение шашки
    // Проверяет возможность хода и выполняет перемещение шашки или "съедание".
    bool movePiece(int fromRow, int fromCol, int toRow, int toCol);

    // Получение размера клетки
    // Возвращает размер одной клетки игрового поля (в пикселях).
    int getCellSize() const;

    // Получение типа шашки на клетке
    // Возвращает тип шашки (пустая, белая, чёрная, дамка и т.д.) по координатам клетки.
    int getPieceAt(int row, int col);

    // Установка координат выделенной шашки
    // Сохраняет координаты шашки, которую выбрал игрок.
    void setHighlightedPiece(int row, int col);

    // Переключение игрока
    // Меняет текущего игрока после выполнения хода.
    void switchPlayer();

private:
    static constexpr int cellSize = 100; // Размер одной клетки (в пикселях)
    sf::Color lightColor;               // Цвет светлых клеток
    sf::Color darkColor;                // Цвет тёмных клеток
    std::array<std::array<int, 8>, 8> boardState; // Состояние игрового поля (8x8 массив)

    sf::Vector2i highlightedPiece;      // Координаты выделенной шашки (-1, -1, если ничего не выделено)
    int currentPlayer;                  // Текущий игрок (1 — белые, 2 — чёрные)

    // Вспомогательные методы

    // Проверка корректности позиции
    // Возвращает true, если координаты находятся в пределах игрового поля (0–7).
    bool isValidPosition(int row, int col);

    // Проверка возможности перемещения
    // Возвращает true, если шашка может переместиться на указанную клетку.
    bool canMoveTo(int fromRow, int fromCol, int toRow, int toCol);

    // Выполнение "съедания"
    // Удаляет шашку противника и перемещает текущую шашку на новую позицию.
    bool performCapture(int fromRow, int fromCol, int toRow, int toCol);

    // Множественное "съедание"
    // Рекурсивно выполняет все возможные шаги для "съедания" нескольких шашек.
    bool performMultipleCaptures(int fromRow, int fromCol, int toRow, int toCol);

    // Превращение шашки в дамку
    // Если шашка достигает последней строки противника, она становится дамкой.
    void promoteToKing(int row, int col);

    // Проверка обязательного "съедания"
    // Возвращает true, если у текущей шашки есть возможность "съесть" шашку противника.
    bool mustCapture(int row, int col);

    // Методы для отрисовки

    // Отрисовка клеток
    // Заполняет игровое поле светлыми и тёмными клетками.
    void drawCells(sf::RenderWindow& window);

    // Отрисовка шашек
    // Отрисовывает шашки на игровом поле с учётом их типа (белые, чёрные, дамки).
    void drawPieces(sf::RenderWindow& window);

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