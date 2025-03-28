#include <SFML/Graphics.hpp>
#include "../include/GameBoard.hpp"

int main() {
    // Создаем окно размером 800x800 пикселей
    sf::RenderWindow window(sf::VideoMode(800, 800), "Checkers Game");

    // Создаем объект игрового поля
    GameBoard gameBoard;

    // Главный цикл программы
    while (window.isOpen()) {
        // Обработка событий
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
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