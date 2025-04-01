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
    drawCells(window); // Отрисовываем клетки
    drawPieces(window); // Отрисовываем шашки

    // Выделение выбранной шашки
    if (highlightedPiece.x != -1 && highlightedPiece.y != -1) {
        sf::RectangleShape highlight(sf::Vector2f(cellSize, cellSize));
        highlight.setFillColor(sf::Color::Transparent); // Прозрачный фон
        highlight.setOutlineThickness(4); // Толщина контура
        highlight.setOutlineColor(sf::Color::Yellow); // Жёлтый цвет контура
        highlight.setPosition(highlightedPiece.y * cellSize, highlightedPiece.x * cellSize); // Позиция выделения
        window.draw(highlight); // Отрисовываем выделение
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
    // Проверяем, что ход допустим (например, только по диагонали)
    if (abs(fromRow - toRow) == 1 && abs(fromCol - toCol) == 1) {
        // Обычный ход
        boardState[toRow][toCol] = boardState[fromRow][fromCol]; // Перемещаем шашку
        boardState[fromRow][fromCol] = 0; // Очищаем начальную клетку
        return true; // Ход успешен
    } else if (abs(fromRow - toRow) == 2 && abs(fromCol - toCol) == 2) {
        // "Съедание" шашки противника
        int midRow = (fromRow + toRow) / 2;
        int midCol = (fromCol + toCol) / 2;

        if (boardState[midRow][midCol] != 0 && 
            boardState[midRow][midCol] != boardState[fromRow][fromCol]) {
            // Удаляем шашку противника
            boardState[midRow][midCol] = 0;

            // Перемещаем шашку
            boardState[toRow][toCol] = boardState[fromRow][fromCol];
            boardState[fromRow][fromCol] = 0;

            return true; // Ход успешен
        }
    }

    return false; // Ход недопустим
}

// Метод для получения размера клетки
int GameBoard::getCellSize() const {
    return cellSize; // Возвращаем размер одной клетки
}

// Метод для получения шашки на заданной клетке
int GameBoard::getPieceAt(int row, int col) {
    return boardState[row][col]; // Возвращаем значение из массива boardState
}

// Метод для установки координат выделенной шашки
void GameBoard::setHighlightedPiece(int row, int col) {
    highlightedPiece = {row, col}; // Устанавливаем координаты выделенной шашки
}

// Метод для проверки наличия обязательных ходов
bool GameBoard::hasMandatoryCapture(int player) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (boardState[row][col] == player) {
                // Проверяем все возможные направления для "съедания"
                int directions[4][2] = {{-2, -2}, {-2, 2}, {2, -2}, {2, 2}};
                for (auto& dir : directions) {
                    int toRow = row + dir[0];
                    int toCol = col + dir[1];
                    int midRow = row + dir[0] / 2;
                    int midCol = col + dir[1] / 2;

                    if (isValidPosition(toRow, toCol) && boardState[toRow][toCol] == 0 &&
                        boardState[midRow][midCol] != 0 && boardState[midRow][midCol] != player) {
                        return true; // Обязательный ход найден
                    }
                }
            }
        }
    }
    return false; // Обязательных ходов нет
}

// Метод для проверки возможности "съедания" из заданной позиции
bool GameBoard::canCaptureFrom(int row, int col) {
    int player = boardState[row][col];
    int directions[4][2] = {{-2, -2}, {-2, 2}, {2, -2}, {2, 2}};

    for (auto& dir : directions) {
        int toRow = row + dir[0];
        int toCol = col + dir[1];
        int midRow = row + dir[0] / 2;
        int midCol = col + dir[1] / 2;

        if (isValidPosition(toRow, toCol) && boardState[toRow][toCol] == 0 &&
            boardState[midRow][midCol] != 0 && boardState[midRow][midCol] != player) {
            return true; // Возможен "съедание" из этой позиции
        }
    }
    return false; // Невозможно "съедание" из этой позиции
}

// Вспомогательный метод для проверки корректности координат
bool GameBoard::isValidPosition(int row, int col) {
    return row >= 0 && row < 8 && col >= 0 && col < 8; // Координаты должны быть в пределах поля
}