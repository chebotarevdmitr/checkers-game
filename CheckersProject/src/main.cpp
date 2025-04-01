#include <SFML/Graphics.hpp> // Подключаем библиотеку SFML для работы с графикой
#include "../include/GameBoard.hpp" // Подключаем заголовочный файл класса GameBoard
#include <iostream> // Для вывода отладочных сообщений

int main() {
    // Создаем окно размером 800x800 пикселей с заголовком "Checkers Game"
    sf::RenderWindow window(sf::VideoMode(800, 800), "Checkers Game");

    // Создаем объект игрового поля
    GameBoard gameBoard;

    // Переменные для хранения позиции мыши
    sf::Vector2i mousePosition;

    // Флаг, указывающий, выбрана ли шашка
    bool isPieceSelected = false;

    // Координаты выбранной шашки
    int selectedRow = -1, selectedCol = -1;

    // Текущий игрок (1 — белые, 2 — чёрные)
    int currentPlayer = 1;

    // Выводим сообщение о начале игры
    std::cout << "Game started. Player 1 (White) moves first.\n";

    // Главный цикл программы
    while (window.isOpen()) {
        sf::Event event; // Объект события SFML

        // Обработка событий
        while (window.pollEvent(event)) {
            // Обработка закрытия окна
            if (event.type == sf::Event::Closed) {
                std::cout << "Window closed by user.\n";
                window.close(); // Закрываем окно
            }

            // Обработка нажатия левой кнопки мыши
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Получаем позицию мыши в экранных координатах
                mousePosition = sf::Mouse::getPosition(window);

                // Вычисляем координаты клетки на игровом поле
                int row = mousePosition.y / gameBoard.getCellSize();
                int col = mousePosition.x / gameBoard.getCellSize();

                // Проверяем, есть ли шашка на клетке
                if (!isPieceSelected && gameBoard.isPieceAt(row, col)) {
                    // Проверяем, что шашка принадлежит текущему игроку
                    if (gameBoard.getPieceAt(row, col) != currentPlayer) {
                        std::cout << "It's not your piece! Current player: " << currentPlayer << "\n";
                        continue;
                    }

                    // Проверяем, есть ли обязательные ходы
                    if (gameBoard.hasMandatoryCapture(currentPlayer)) {
                        std::cout << "You must capture an opponent's piece!\n";

                        // Проверяем, можно ли "съесть" шашку из текущей позиции
                        if (!gameBoard.canCaptureFrom(row, col)) {
                            std::cout << "You must select a piece that can capture.\n";
                            continue;
                        }
                    }

                    // Выбираем шашку
                    isPieceSelected = true;
                    selectedRow = row;
                    selectedCol = col;
                    gameBoard.setHighlightedPiece(row, col); // Устанавливаем выделение
                    std::cout << "Piece selected at (" << row << ", " << col << ")\n";
                } 
                // Если шашка уже выбрана, пытаемся переместить её
                else if (isPieceSelected) {
                    std::cout << "Attempting to move piece from (" << selectedRow << ", " << selectedCol
                              << ") to (" << row << ", " << col << ")\n";

                    // Пытаемся переместить шашку
                    if (gameBoard.movePiece(selectedRow, selectedCol, row, col)) {
                        isPieceSelected = false; // Снимаем выбор
                        gameBoard.setHighlightedPiece(-1, -1); // Снимаем выделение

                        // Переключаем игрока
                        currentPlayer = (currentPlayer == 1) ? 2 : 1;
                        std::cout << "Player " << currentPlayer << "'s turn.\n";
                    } else {
                        std::cout << "Invalid move. Try again.\n";
                    }
                }
            }
        }

        // Очистка окна перед отрисовкой нового кадра
        window.clear();

        // Отрисовка игрового поля
        gameBoard.draw(window);

        // Отображение содержимого окна
        window.display();
    }

    return 0; // Завершаем программу
}