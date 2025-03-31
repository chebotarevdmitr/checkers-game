#include <SFML/Graphics.hpp> // Подключаем библиотеку SFML для работы с графикой
#include "../include/GameBoard.hpp" // Подключаем заголовочный файл игрового поля
#include <iostream> // Подключаем библиотеку для вывода отладочных сообщений

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

    // Выводим сообщение о начале игры
    std::cout << "Game started. Click on the board to select and move pieces.\n";

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

                // Выводим позицию мыши в терминал для отладки
                std::cout << "Mouse clicked at screen position: (" << mousePosition.x << ", " << mousePosition.y << ")\n";

                // Вычисляем координаты клетки на игровом поле
                int row = mousePosition.y / gameBoard.getCellSize();
                int col = mousePosition.x / gameBoard.getCellSize();

                // Выводим координаты клетки в терминал для отладки
                std::cout << "Converted to board position: (" << row << ", " << col << ")\n";

                // Проверяем, есть ли шашка на клетке
                std::cout << "isPieceAt(" << row << ", " << col << ") = " << gameBoard.isPieceAt(row, col) << "\n";

                // Если шашка еще не выбрана, выбираем её
                if (!isPieceSelected && gameBoard.isPieceAt(row, col)) {
                    isPieceSelected = true; // Устанавливаем флаг выбора
                    selectedRow = row; // Сохраняем координаты выбранной шашки
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
                        std::cout << "Piece moved successfully.\n";
                    } else {
                        std::cout << "Invalid move.\n";
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