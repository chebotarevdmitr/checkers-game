#include "../include/GameBoard.hpp"

// Конструктор класса GameBoard
// Инициализирует игровое поле, цвета клеток и начальное состояние игры.
GameBoard::GameBoard() : highlightedPiece{-1, -1}, currentPlayer(1) {
    lightColor = sf::Color(240, 217, 181); // Светлый цвет клеток
    darkColor = sf::Color(181, 136, 99);   // Темный цвет клеток

    // Инициализация игрового поля (8x8 массив)
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if ((row + col) % 2 != 0) { // Только на тёмных клетках
                if (row < 3) { // Белые шашки в первых трёх рядах
                    boardState[row][col] = WHITE_PIECE;
                } else if (row > 4) { // Чёрные шашки в последних трёх рядах
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

// Отрисовка игрового поля
// Вызывает методы для отрисовки клеток и шашек, а также выделение выбранной шашки.
void GameBoard::draw(sf::RenderWindow& window) {
    drawCells(window); // Отрисовываем клетки
    drawPieces(window); // Отрисовываем шашки

    // Выделение выбранной шашки
    if (highlightedPiece.x != -1 && highlightedPiece.y != -1) {
        sf::RectangleShape highlight(sf::Vector2f(cellSize, cellSize));
        highlight.setFillColor(sf::Color::Transparent);
        highlight.setOutlineThickness(4);
        highlight.setOutlineColor(sf::Color::Yellow);
        highlight.setPosition(highlightedPiece.y * cellSize, highlightedPiece.x * cellSize);
        window.draw(highlight);
    }
}

// Отрисовка клеток
// Заполняет игровое поле светлыми и тёмными клетками.
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

// Отрисовка шашек
// Отрисовывает шашки на игровом поле с учётом их типа (белые, чёрные, дамки).
void GameBoard::drawPieces(sf::RenderWindow& window) {
    sf::Color whitePieceColor(255, 255, 255);          // Цвет белых шашек
    sf::Color blackPieceColor(0, 0, 0);               // Цвет чёрных шашек
    sf::Color whiteKingColor(255, 255, 153);          // Цвет белых дамок
    sf::Color blackKingColor(204, 204, 0);            // Цвет чёрных дамок

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            int piece = boardState[row][col];
            if (piece == WHITE_PIECE || piece == BLACK_PIECE) {
                sf::CircleShape pieceShape(45);
                pieceShape.setFillColor(piece == WHITE_PIECE ? whitePieceColor : blackPieceColor);
                pieceShape.setPosition(col * cellSize + 5, row * cellSize + 5);
                window.draw(pieceShape);
            } else if (piece == WHITE_KING || piece == BLACK_KING) {
                sf::CircleShape kingShape(45);
                kingShape.setFillColor(piece == WHITE_KING ? whiteKingColor : blackKingColor);
                kingShape.setPosition(col * cellSize + 5, row * cellSize + 5);
                window.draw(kingShape);
            }
        }
    }
}

// Проверка наличия шашки на клетке
// Возвращает true, если на указанной клетке есть шашка (не пустая).
bool GameBoard::isPieceAt(int row, int col) {
    return boardState[row][col] != EMPTY;
}

// Получение размера клетки
// Возвращает размер одной клетки игрового поля (в пикселях).
int GameBoard::getCellSize() const {
    return cellSize;
}

// Получение типа шашки на клетке
// Возвращает тип шашки (пустая, белая, чёрная, дамка и т.д.) по координатам клетки.
int GameBoard::getPieceAt(int row, int col) {
    return boardState[row][col];
}

// Установка координат выделенной шашки
// Сохраняет координаты шашки, которую выбрал игрок.
void GameBoard::setHighlightedPiece(int row, int col) {
    highlightedPiece = {row, col};
}

// Перемещение шашки
// Проверяет возможность хода и выполняет перемещение шашки или "съедание".
bool GameBoard::movePiece(int fromRow, int fromCol, int toRow, int toCol) {
    int piece = boardState[fromRow][fromCol];

    // Проверяем, что ходит правильный игрок
    if ((currentPlayer == 1 && (piece == BLACK_PIECE || piece == BLACK_KING)) ||
        (currentPlayer == 2 && (piece == WHITE_PIECE || piece == WHITE_KING))) {
        return false;
    }

    // Проверяем обязательный ход
    if (mustCapture(fromRow, fromCol)) {
        if (abs(fromRow - toRow) != 2 || abs(fromCol - toCol) != 2) {
            return false; // Обязательно нужно "съесть"
        }
    }

    // Проверяем возможность "съедания"
    if (abs(fromRow - toRow) == 2 && abs(fromCol - toCol) == 2) {
        if (!performMultipleCaptures(fromRow, fromCol, toRow, toCol)) {
            return false;
        }
    } else {
        // Проверяем возможность простого перемещения
        if (!canMoveTo(fromRow, fromCol, toRow, toCol)) {
            return false;
        }

        // Перемещаем шашку
        boardState[toRow][toCol] = piece;
        boardState[fromRow][fromCol] = EMPTY;

        // Проверяем превращение в дамку
        promoteToKing(toRow, toCol);
    }

    // Переключаем игрока
    switchPlayer();
    return true;
}

// Проверка корректности позиции
// Возвращает true, если координаты находятся в пределах игрового поля (0–7).
bool GameBoard::isValidPosition(int row, int col) {
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}

// Проверка возможности перемещения
// Возвращает true, если шашка может переместиться на указанную клетку.
bool GameBoard::canMoveTo(int fromRow, int fromCol, int toRow, int toCol) {
    int piece = boardState[fromRow][fromCol];
    bool isKing = (piece == WHITE_KING || piece == BLACK_KING);

    // Направление движения для обычных шашек
    if (!isKing) {
        if (piece == WHITE_PIECE && toRow <= fromRow) {
            return false; // Белые шашки не могут ходить назад
        }
        if (piece == BLACK_PIECE && toRow >= fromRow) {
            return false; // Чёрные шашки не могут ходить назад
        }
    }

    // Проверяем расстояние
    if (abs(fromRow - toRow) != 1 || abs(fromCol - toCol) != 1) {
        return false; // Шашки могут двигаться только на одну клетку по диагонали
    }

    // Проверяем, что целевая клетка пуста
    if (boardState[toRow][toCol] != EMPTY) {
        return false;
    }

    return true;
}

// Выполнение "съедания"
// Удаляет шашку противника и перемещает текущую шашку на новую позицию.
bool GameBoard::performCapture(int fromRow, int fromCol, int toRow, int toCol) {
    int midRow = (fromRow + toRow) / 2;
    int midCol = (fromCol + toCol) / 2;

    int piece = boardState[fromRow][fromCol];
    int midPiece = boardState[midRow][midCol];

    // Проверяем, что между начальной и конечной клетками находится шашка противника
    if (midPiece == EMPTY || midPiece == piece) {
        return false;
    }

    // Удаляем шашку противника
    boardState[midRow][midCol] = EMPTY;

    // Перемещаем шашку
    boardState[toRow][toCol] = piece;
    boardState[fromRow][fromCol] = EMPTY;

    // Проверяем превращение в дамку
    promoteToKing(toRow, toCol);

    return true;
}

// Множественное "съедание"
// Рекурсивно выполняет все возможные шаги для "съедания" нескольких шашек.
bool GameBoard::performMultipleCaptures(int fromRow, int fromCol, int toRow, int toCol) {
    int midRow = (fromRow + toRow) / 2;
    int midCol = (fromCol + toCol) / 2;

    int piece = boardState[fromRow][fromCol];
    int midPiece = boardState[midRow][midCol];

    // Проверяем, что между начальной и конечной клетками находится шашка противника
    if (midPiece == EMPTY || midPiece == piece) {
        return false;
    }

    // Удаляем шашку противника
    boardState[midRow][midCol] = EMPTY;

    // Перемещаем шашку
    boardState[toRow][toCol] = piece;
    boardState[fromRow][fromCol] = EMPTY;

    // Проверяем превращение в дамку
    promoteToKing(toRow, toCol);

    // Проверяем возможность продолжения множественного "съедания"
    bool canContinue = false;
    int directions[4][2] = {{-2, -2}, {-2, 2}, {2, -2}, {2, 2}};
    for (auto& dir : directions) {
        int nextRow = toRow + dir[0];
        int nextCol = toCol + dir[1];
        int nextMidRow = toRow + dir[0] / 2;
        int nextMidCol = toCol + dir[1] / 2;

        if (isValidPosition(nextRow, nextCol) && boardState[nextRow][nextCol] == EMPTY &&
            boardState[nextMidRow][nextMidCol] != EMPTY && boardState[nextMidRow][nextMidCol] != piece) {
            canContinue = true;
            break;
        }
    }

    // Если возможно продолжение, рекурсивно выполняем следующий шаг
    if (canContinue) {
        for (auto& dir : directions) {
            int nextRow = toRow + dir[0];
            int nextCol = toCol + dir[1];
            performMultipleCaptures(toRow, toCol, nextRow, nextCol);
        }
    }

    return true;
}

// Превращение шашки в дамку
// Если шашка достигает последней строки противника, она становится дамкой.
void GameBoard::promoteToKing(int row, int col) {
    int piece = boardState[row][col];
    if (piece == WHITE_PIECE && row == 7) {
        boardState[row][col] = WHITE_KING; // Белая шашка становится дамкой
    } else if (piece == BLACK_PIECE && row == 0) {
        boardState[row][col] = BLACK_KING; // Чёрная шашка становится дамкой
    }
}

// Проверка обязательного "съедания"
// Возвращает true, если у текущей шашки есть возможность "съесть" шашку противника.
bool GameBoard::mustCapture(int row, int col) {
    int piece = boardState[row][col];
    int directions[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    for (auto& dir : directions) {
        int midRow = row + dir[0];
        int midCol = col + dir[1];
        int targetRow = row + 2 * dir[0];
        int targetCol = col + 2 * dir[1];

        if (isValidPosition(targetRow, targetCol) &&
            boardState[midRow][midCol] != EMPTY &&
            boardState[midRow][midCol] != piece &&
            boardState[targetRow][targetCol] == EMPTY) {
            return true;
        }
    }

    return false;
}

// Переключение игрока
// Меняет текущего игрока после выполнения хода.
void GameBoard::switchPlayer() {
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
}