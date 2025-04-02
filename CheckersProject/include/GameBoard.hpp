#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <SFML/Graphics.hpp>
#include <array>

class GameBoard {
public:
    GameBoard();

    void draw(sf::RenderWindow& window);
    bool isPieceAt(int row, int col);
    bool movePiece(int fromRow, int fromCol, int toRow, int toCol);
    int getCellSize() const;
    int getPieceAt(int row, int col);
    void setHighlightedPiece(int row, int col);
    bool hasMandatoryCapture(int player);
    bool canCaptureFrom(int row, int col);

    enum PieceType {
        EMPTY = 0,
        WHITE_PIECE = 1,
        BLACK_PIECE = 2,
        WHITE_KING = 3,
        BLACK_KING = 4
    };

    void promoteToKing(int row, int col);

private:
    void drawCells(sf::RenderWindow& window);
    void drawPieces(sf::RenderWindow& window);
    static constexpr int cellSize = 100;
    sf::Color lightColor;
    sf::Color darkColor;
    std::array<std::array<int, 8>, 8> boardState;
    sf::Vector2i highlightedPiece;
    bool isValidPosition(int row, int col);
};

#endif // GAMEBOARD_HPP