#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>

int main() {
    // Отладка: вывод текущей рабочей директории
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

    // Создаем окно размером 800x600 пикселей
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    // Загружаем шрифт
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        std::cerr << "Ошибка: не удалось загрузить шрифт!" << std::endl;
        return -1; // Выход из программы, если шрифт не загружен
    }

    // Создаем текстовый объект
    sf::Text text;
    text.setFont(font); // Устанавливаем шрифт
    text.setString("HELLO, Checkers!"); // Устанавливаем строку текста
    text.setCharacterSize(40); // Размер шрифта
    text.setFillColor(sf::Color::White); // Цвет текста
    text.setStyle(sf::Text::Bold); // Стиль текста (жирный)

    // Центрируем текст в окне
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        (800 - textBounds.width) / 2,  // Горизонтальное центрирование
        (600 - textBounds.height) / 2  // Вертикальное центрирование
    );

    // Главный цикл программы
    while (window.isOpen()) {
        // Обработка событий
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Очистка окна и отрисовка фона
        window.clear(sf::Color::Black);

        // Отрисовка текста
        window.draw(text);

        // Отображение содержимого окна
        window.display();
    }

    return 0;
}