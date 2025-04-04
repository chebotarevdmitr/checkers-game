#include <SFML/Graphics.hpp>
#include "../include/GameBoard.hpp"

// Главная функция программы
int main() {
    // Создаем окно размером 800x800 пикселей с заголовком "Checkers Game"
    sf::RenderWindow window(sf::VideoMode(800, 800), "Checkers Game");
    window.setFramerateLimit(60); // Устанавливаем ограничение на частоту кадров (60 FPS)

    // Создаем объект игрового поля
    GameBoard gameBoard;

    // Переменные для хранения координат выделенной шашки
    int selectedRow = -1; // Строка выбранной шашки (-1 означает, что ничего не выбрано)
    int selectedCol = -1; // Столбец выбранной шашки

    // Основной цикл игры
    while (window.isOpen()) {
        sf::Event event;
        // Обработка событий (например, закрытие окна или клики мыши)
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); // Закрываем окно, если пользователь нажал на кнопку закрытия
            }

            // Обработка кликов мыши
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                int mouseX = event.mouseButton.x; // Получаем координаты X клика
                int mouseY = event.mouseButton.y; // Получаем координаты Y клика

                // Преобразуем координаты клика в индексы клетки на игровом поле
                int clickedRow = mouseY / gameBoard.getCellSize();
                int clickedCol = mouseX / gameBoard.getCellSize();

                // Если на клетке есть шашка, запоминаем её координаты
                if (gameBoard.isPieceAt(clickedRow, clickedCol)) {
                    selectedRow = clickedRow;
                    selectedCol = clickedCol;
                    gameBoard.setHighlightedPiece(selectedRow, selectedCol); // Выделяем шашку
                } else {
                    // Если выбранная шашка уже существует, пытаемся переместить её
                    if (selectedRow != -1 && selectedCol != -1) {
                        if (gameBoard.movePiece(selectedRow, selectedCol, clickedRow, clickedCol)) {
                            selectedRow = -1; // Сбрасываем выделение после успешного хода
                            selectedCol = -1;
                        }
                    }
                }
            }
        }

        // Отрисовка
        window.clear(sf::Color::White); // Очищаем окно (заливаем белым цветом)
        gameBoard.draw(window);         // Отрисовываем игровое поле и шашки
        window.display();               // Отображаем всё на экране
    }

    return 0; // Завершаем программу
}