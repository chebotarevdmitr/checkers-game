#include <SFML/Graphics.hpp> // Для работы с графикой SFML
#include <iostream>

int main() {
    // Создаем окно размером 800x800 пикселей
    sf::RenderWindow window(sf::VideoMode(800, 800), "Checkers Game");

    // Устанавливаем частоту обновления экрана (60 FPS)
    window.setFramerateLimit(60);

    // Цвет фона окна (серый)
    sf::Color backgroundColor(128, 128, 128);

    // Основной цикл игры
    while (window.isOpen()) {
        // Обработка событий
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); // Закрыть окно при нажатии на кнопку закрытия
            }
        }

        // Очистка окна цветом фона
        window.clear(backgroundColor);

        // Здесь будет отрисовка игрового поля и фигур

        // Отображение содержимого окна
        window.display();
    }

    return 0;
}