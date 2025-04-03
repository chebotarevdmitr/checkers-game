#include <SFML/Graphics.hpp>
#include "../include/GameBoard.hpp"

int main() {
    // Создаем окно
    sf::RenderWindow window(sf::VideoMode(800, 800), "Checkers Game");
    window.setFramerateLimit(60);

    // Создаем объект игрового поля
    GameBoard gameBoard;

    // Переменные для хранения координат выделенной шашки
    int selectedRow = -1;
    int selectedCol = -1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Обработка кликов мыши
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                int clickedRow = mouseY / gameBoard.getCellSize();
                int clickedCol = mouseX / gameBoard.getCellSize();

                if (gameBoard.isPieceAt(clickedRow, clickedCol)) {
                    selectedRow = clickedRow;
                    selectedCol = clickedCol;
                    gameBoard.setHighlightedPiece(selectedRow, selectedCol);
                } else {
                    if (selectedRow != -1 && selectedCol != -1) {
                        if (gameBoard.movePiece(selectedRow, selectedCol, clickedRow, clickedCol)) {
                            selectedRow = -1;
                            selectedCol = -1;
                        }
                    }
                }
            }
        }

        // Отрисовка
        window.clear(sf::Color::White);
        gameBoard.draw(window);
        window.display();
    }

    return 0;
}