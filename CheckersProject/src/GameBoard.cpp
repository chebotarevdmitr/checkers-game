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
                    boardState[row][col] = WHITE_PIECE;
                } else if (row > 4) { // Чёрные шашки
                    boardState[row][col] = BLACK_PIECE;
                } else {
                    boardState[row][col] = EMPTY; // Пустая клетка
                }
            } else {
                boardState[row][col] = EMPTY; // Пустая клетка
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
    sf::Color kingColor(255, 215, 0);        // Цвет дамок (золотой)

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

// Метод для проверки наличия шашки на клетке
bool GameBoard::isPieceAt(int row, int col) {
    return boardState[row][col] != EMPTY; // Возвращаем true, если на клетке есть шашка
}

// Метод для перемещения шашки
bool GameBoard::movePiece(int fromRow, int fromCol, int toRow, int toCol) {
    int piece = boardState[fromRow][fromCol];

    // Проверяем, является ли шашка дамкой
    bool isKing = (piece == WHITE_KING || piece == BLACK_KING);

    // Вычисляем направление движения
    int rowDir = (toRow - fromRow > 0) ? 1 : -1;
    int colDir = (toCol - fromCol > 0) ? 1 : -1;

    // Для дамок разрешено движение на любое количество клеток
    if (isKing) {
        int steps = std::max(abs(toRow - fromRow), abs(toCol - fromCol));
        for (int step = 1; step < steps; ++step) {
            int midRow = fromRow + step * rowDir;
            int midCol = fromCol + step * colDir;

            // Если на пути есть шашка, ход недопустим
            if (boardState[midRow][midCol] != EMPTY) {
                return false;
            }
        }
    } else {
        // Для обычных шашек разрешены только ходы на одну клетку
        if (abs(fromRow - toRow) != 1 || abs(fromCol - toCol) != 1) {
            return false;
        }
    }

    // Перемещаем шашку
    boardState[toRow][toCol] = piece;
    boardState[fromRow][fromCol] = EMPTY;

    // Проверяем, нужно ли превратить шашку в дамку
    promoteToKing(toRow, toCol);

    return true;
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

                    if (isValidPosition(toRow, toCol) && boardState[toRow][toCol] == EMPTY &&
                        boardState[midRow][midCol] != EMPTY && boardState[midRow][midCol] != player) {
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

        if (isValidPosition(toRow, toCol) && boardState[toRow][toCol] == EMPTY &&
            boardState[midRow][midCol] != EMPTY && boardState[midRow][midCol] != player) {
            return true; // Возможен "съедание" из этой позиции
        }
    }
    return false; // Невозможно "съедание" из этой позиции
}

// Вспомогательный метод для проверки корректности координат
bool GameBoard::isValidPosition(int row, int col) {
    return row >= 0 && row < 8 && col >= 0 && col < 8; // Координаты должны быть в пределах поля
}

// Метод для превращения шашки в дамку
void GameBoard::promoteToKing(int row, int col) {
    int piece = boardState[row][col];
    if (piece == WHITE_PIECE && row == 7) {
        boardState[row][col] = WHITE_KING; // Белая шашка становится дамкой
    } else if (piece == BLACK_PIECE && row == 0) {
        boardState[row][col] = BLACK_KING; // Чёрная шашка становится дамкой
    }
}