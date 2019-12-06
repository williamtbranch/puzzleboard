#pragma once
//main header for board clase
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <string>
#include <vector>
#include <queue>


enum Piece {
    NullPiece,
    WKing,
    WQueen,
    WRook,
    WKnight,
    WBishop,
    WPawn,
    BKing,
    BQueen,
    BRook,
    BKnight,
    BBishop,
    BPawn,
    BSquare,
    WSquare,
    Highlight,
    Error
};

class Position{
    public:
        int x;
        int y;
        Position();
        Position(int x, int y);
};

class PlacedPiece{
    public:
        Piece puzzlePiece;
        Position piecePosition;
        PlacedPiece();
};

class BoardSetup {
    public:
        int xBoardSize;
        int yBoardSize;
        //Board tiles are also pieces. Makes it simpler. Everything is a piece.
        std::vector <PlacedPiece> boardTiles;
        std::vector <PlacedPiece> boardHighlights;
        std::vector <PlacedPiece> boardPieces;

};

enum MessageType{
    NullMessage,
    closeBoard,
    squareClick
};

class Message {
    public:
        MessageType boardMessageType;
        Position boardPosition;
        Message();

};

class MessageQue {
    private:
        std::queue <Message> messages;
        Message emptyMessage;
    public:
        MessageQue();
        int PushMessage(Message message);
        Message PopMessage();
};

class BoardTextures {
    public:
        sf::Texture BKing;
        sf::Texture BQueen;
        sf::Texture BRook;
        sf::Texture BKnight;
        sf::Texture BBishop;
        sf::Texture BPawn;
        sf::Texture WKing;
        sf::Texture WQueen;
        sf::Texture WRook;
        sf::Texture WKnight;
        sf::Texture WBishop;
        sf::Texture WPawn;
        sf::Texture whiteSquare;
        sf::Texture blackSquare;
        sf::Texture highlight;
        sf::Texture Error;
        BoardTextures();

};

class BoardSprites {
    public:
        BoardTextures boardImages;
        sf::Sprite BKing;
        sf::Sprite BQueen;
        sf::Sprite BRook;
        sf::Sprite BKnight;
        sf::Sprite BBishop;
        sf::Sprite BPawn;
        sf::Sprite WKing;
        sf::Sprite WQueen;
        sf::Sprite WRook;
        sf::Sprite WKnight;
        sf::Sprite WBishop;
        sf::Sprite WPawn;
        sf::Sprite whiteSquare;
        sf::Sprite blackSquare;
        sf::Sprite highlight;
        sf::Sprite Error;
        BoardSprites();

};

class Board {
    private:
        MessageQue boardMessages;
        BoardSprites boardSprites;
        int tileSize;
        int windowWidth;
        int windowHeight;
        sf::RenderWindow window;
        std::string boardName;
        bool lowerLeftBlack;
        BoardSetup boardSetup;
        int DrawSpritesFromVector(std::vector <PlacedPiece> boardPieces);
        //Center location of playing board
        float boardPaneXCenter;
        float boardPaneYCenter;
    public:
        int fillBoardWithTiles();
        int updateDisplay();
        int setBoardSize(int xSize, int ySize);
        int openDisplay();
        int closeDisplay();
        int placePiece( Piece, int xCoord, int yCoord);
        int placeTile( Piece, int xCoord, int yCoord);
        int placeHighlight( Piece, int xCoord, int yCoord);
        int removePiece( int XCoord, int yCoord);
        int removeTile( int XCoord, int yCoord);
        int removeHighlight( int XCoord, int yCoord);
        int setBoardName (std::string);
        Piece peekPiece ( int xCoord, int yCoord );
        Piece peekHighlight ( int xCoord, int yCoord );
        Piece peekTile ( int xCoord, int yCoord );
        Board();
        Board(int xSize, int ySize);
        Board(BoardSetup boardSetup);
        Message GetMessage();
};
