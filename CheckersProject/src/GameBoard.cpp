#include "../include/GameBoard.hpp" // Подключаем заголовочный файл класса GameBoard
#include <iostream> // Для вывода отладочных сообщений

// Конструктор класса GameBoard
GameBoard::GameBoard() : highlightedPiece{-1, -1} {
    lightColor = sf::Color(240, 217, 181); // Светлый цвет клеток
    darkColor = sf::Color(181, 136, 99);   // Темный цвет клеток

    // Инициализация состояния игрового поля
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
}

// Метод для отрисовки игрового поля
void GameBoard::draw(sf::RenderWindow& window) {
    drawCells(window);
    drawPieces(window);

    // Выделение выбранной шашки
    if (highlightedPiece.x != -1 && highlightedPiece.y != -1) {
        sf::RectangleShape highlight(sf::Vector2f(cellSize, cellSize));
        highlight.setFillColor(sf::Color::Transparent);
        highlight.setOutlineThickness(4);
        highlight.setOutlineColor(sf::Color::Yellow);
        highlight.setPosition(highlightedPiece.y * cellSize, highlightedPiece.x * cellSize);
        window.draw(highlight);

        std::cout << "Drawing highlight at (" << highlightedPiece.x << ", " << highlightedPiece.y << ")\n";
    }
}

// Метод для отрисовки клеток игрового поля
void GameBoard::drawCells(sf::RenderWindow& window) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize)); // Создаем прямоугольник для клетки
            cell.setPosition(col * cellSize, row * cellSize); // Устанавливаем позицию клетки

            // Задаем цвет клетки в зависимости от её координат
            if ((row + col) % 2 == 0) {
                cell.setFillColor(lightColor); // Светлый цвет
            } else {
                cell.setFillColor(darkColor); // Темный цвет
            }

            window.draw(cell); // Отрисовываем клетку
        }
    }
}

// Метод для отрисовки шашек
void GameBoard::drawPieces(sf::RenderWindow& window) {
    sf::Color whitePieceColor(255, 255, 255); // Цвет белых шашек
    sf::Color blackPieceColor(0, 0, 0);      // Цвет чёрных шашек

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (boardState[row][col] == 1) { // Если на клетке белая шашка
                sf::CircleShape piece(45); // Создаем круг радиусом 45
                piece.setFillColor(whitePieceColor); // Задаем цвет
                piece.setPosition(col * cellSize + 5, row * cellSize + 5); // Устанавливаем позицию
                window.draw(piece); // Отрисовываем шашку
            } else if (boardState[row][col] == 2) { // Если на клетке чёрная шашка
                sf::CircleShape piece(45); // Создаем круг радиусом 45
                piece.setFillColor(blackPieceColor); // Задаем цвет
                piece.setPosition(col * cellSize + 5, row * cellSize + 5); // Устанавливаем позицию
                window.draw(piece); // Отрисовываем шашку
            }
        }
    }
}

// Метод для проверки наличия шашки на клетке
bool GameBoard::isPieceAt(int row, int col) {
    return boardState[row][col] != 0; // Возвращаем true, если на клетке есть шашка
}

// Метод для перемещения шашки
bool GameBoard::movePiece(int fromRow, int fromCol, int toRow, int toCol) {
    // Выводим отладочные сообщения о попытке перемещения
    std::cout << "Trying to move from (" << fromRow << ", " << fromCol
              << ") to (" << toRow << ", " << toCol << ")\n";

    // Проверяем, что ход допустим (например, только по диагонали)
    if (abs(fromRow - toRow) == 1 && abs(fromCol - toCol) == 1) {
        std::cout << "Move is valid.\n";
        boardState[toRow][toCol] = boardState[fromRow][fromCol]; // Перемещаем шашку
        boardState[fromRow][fromCol] = 0; // Очищаем начальную клетку
        return true; // Ход успешен
    }

    std::cout << "Move is invalid.\n";
    return false; // Ход недопустим
}

// Метод для получения размера клетки
int GameBoard::getCellSize() const {
    return cellSize; // Возвращаем размер одной клетки
}

// Метод для установки координат выделенной шашки
void GameBoard::setHighlightedPiece(int row, int col) {
    highlightedPiece = {row, col}; // Устанавливаем координаты выделенной шашки
}