#include <SFML/Graphics.hpp>
#include "../include/GameBoard.hpp"
#include <iostream> // Для отладочных сообщений

int main() {
    // Создаем окно размером 800x800 пикселей
    sf::RenderWindow window(sf::VideoMode(800, 800), "Checkers Game");

    // Создаем объект игрового поля
    GameBoard gameBoard;

    // Переменные для хранения позиции мыши
    sf::Vector2i mousePosition;
    bool isPieceSelected = false; // Флаг, указывающий, выбрана ли шашка
    int selectedRow = -1, selectedCol = -1; // Координаты выбранной шашки

    std::cout << "Game started. Click on the board to select and move pieces.\n";

    // Главный цикл программы
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Обработка закрытия окна
            if (event.type == sf::Event::Closed) {
                std::cout << "Window closed by user.\n";
                window.close();
            }

            // Обработка нажатия левой кнопки мыши
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                mousePosition = sf::Mouse::getPosition(window); // Получаем позицию мыши

                std::cout << "Mouse clicked at screen position: (" << mousePosition.x << ", " << mousePosition.y << ")\n";

                // Вычисляем координаты клетки по позиции мыши
                int row = mousePosition.y / gameBoard.getCellSize();
                int col = mousePosition.x / gameBoard.getCellSize();

                std::cout << "Converted to board position: (" << row << ", " << col << ")\n";

                // Проверяем, есть ли шашка на клетке
                std::cout << "isPieceAt(" << row << ", " << col << ") = " << gameBoard.isPieceAt(row, col) << "\n";

                // Если шашка еще не выбрана, выбираем её
                if (!isPieceSelected && gameBoard.isPieceAt(row, col)) {
                    isPieceSelected = true;
                    selectedRow = row;
                    selectedCol = col;
                    std::cout << "Piece selected at (" << row << ", " << col << ")\n";
                }
                // Если шашка уже выбрана, пытаемся переместить её
                else if (isPieceSelected) {
                    std::cout << "Attempting to move piece from (" << selectedRow << ", " << selectedCol
                              << ") to (" << row << ", " << col << ")\n";

                    if (gameBoard.movePiece(selectedRow, selectedCol, row, col)) {
                        isPieceSelected = false; // Снимаем выбор
                        std::cout << "Piece moved successfully.\n";
                    } else {
                        std::cout << "Invalid move.\n";
                    }
                }
            }
        }

        // Очистка окна
        window.clear();

        // Отрисовка игрового поля
        gameBoard.draw(window);

        // Отображение содержимого окна
        window.display();
    }

    return 0;
}