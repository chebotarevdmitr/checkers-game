#include "../include/GameBoard.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Checkers Game");
    GameBoard gameBoard;

    sf::Vector2i mousePosition;
    bool isPieceSelected = false;
    int selectedRow = -1, selectedCol = -1;
    int currentPlayer = 1;

    std::cout << "Game started. Player 1 (White) moves first.\n";

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                mousePosition = sf::Mouse::getPosition(window);
                int row = mousePosition.y / gameBoard.getCellSize();
                int col = mousePosition.x / gameBoard.getCellSize();

                if (!isPieceSelected && gameBoard.isPieceAt(row, col)) {
                    if (gameBoard.getPieceAt(row, col) != currentPlayer) {
                        std::cout << "It's not your piece! Current player: " << currentPlayer << "\n";
                        continue;
                    }

                    if (gameBoard.hasMandatoryCapture(currentPlayer)) {
                        std::cout << "You must capture an opponent's piece!\n";
                        if (!gameBoard.canCaptureFrom(row, col)) {
                            std::cout << "You must select a piece that can capture.\n";
                            continue;
                        }
                    }

                    isPieceSelected = true;
                    selectedRow = row;
                    selectedCol = col;
                    gameBoard.setHighlightedPiece(row, col);
                    std::cout << "Piece selected at (" << row << ", " << col << ")\n";
                } else if (isPieceSelected) {
                    std::cout << "Attempting to move piece from (" << selectedRow << ", " << selectedCol
                              << ") to (" << row << ", " << col << ")\n";

                    if (gameBoard.movePiece(selectedRow, selectedCol, row, col)) {
                        isPieceSelected = false;
                        gameBoard.setHighlightedPiece(-1, -1);
                        currentPlayer = (currentPlayer == 1) ? 2 : 1;
                        std::cout << "Player " << currentPlayer << "'s turn.\n";
                    } else {
                        std::cout << "Invalid move. Try again.\n";
                    }
                }
            }
        }

        window.clear();
        gameBoard.draw(window);
        window.display();
    }

    return 0;
}