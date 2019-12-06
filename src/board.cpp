#include "../include/board.hpp"
#include <vector>
#include <iostream>
#include "../include/geometry.hpp"

//a position on the board
Position::Position(){
    x = 1;
    y = 1;
}

Position::Position(int x, int y) : x{x}, y{y} {

}

PlacedPiece::PlacedPiece(){
    puzzlePiece = NullPiece;
}

BoardTextures::BoardTextures(){
    //Load textures

    //BKing.loadFromFile("./assets/pieces/KingB.png");
    BKing.loadFromFile("./assets/pieces/KingB.png");
    BQueen.loadFromFile("./assets/pieces/QueenB.png");
    BRook.loadFromFile("./assets/pieces/RookB.png");
    BKnight.loadFromFile("./assets/pieces/KnightB.png");
    BBishop.loadFromFile("./assets/pieces/BishopB.png");
    BPawn.loadFromFile("./assets/pieces/PawnB.png");
    WKing.loadFromFile("./assets/pieces/KingW.png");
    WQueen.loadFromFile("./assets/pieces/QueenW.png");
    WRook.loadFromFile("./assets/pieces/RookW.png");
    WKnight.loadFromFile("./assets/pieces/KnightW.png");
    WBishop.loadFromFile("./assets/pieces/BishopW.png");
    WPawn.loadFromFile("./assets/pieces/PawnW.png");
    whiteSquare.loadFromFile("./assets/board/white_square.png");
    blackSquare.loadFromFile("./assets/board/black_square.png");
    highlight.loadFromFile("./assets/board/highlight.png");
    Error.loadFromFile("./assets/pieces/Error.png");

}

BoardSprites::BoardSprites(){
    BKing.setTexture(boardImages.BKing);
    BQueen.setTexture(boardImages.BQueen);
    BBishop.setTexture(boardImages.BBishop);
    BRook.setTexture(boardImages.BRook);
    BKnight.setTexture(boardImages.BKnight);
    BPawn.setTexture(boardImages.BPawn);
    WKing.setTexture(boardImages.WKing);
    WQueen.setTexture(boardImages.WQueen);
    WBishop.setTexture(boardImages.WBishop);
    WRook.setTexture(boardImages.WRook);
    WKnight.setTexture(boardImages.WKnight);
    WPawn.setTexture(boardImages.WPawn);
    whiteSquare.setTexture(boardImages.whiteSquare);
    blackSquare.setTexture(boardImages.blackSquare);
    highlight.setTexture(boardImages.highlight);
    Error.setTexture(boardImages.Error);
}

MessageQue::MessageQue(){
    //Set empty message values
    emptyMessage.boardMessageType = NullMessage;
    emptyMessage.boardPosition.x = 0;
    emptyMessage.boardPosition.y = 0;
}

int MessageQue::PushMessage(Message newMessage){
    messages.push(newMessage);
    return 1;
}

Message::Message(){
    boardMessageType = NullMessage;
    boardPosition.x = 0;
    boardPosition.y = 0;
}

Message MessageQue::PopMessage(){
    Message returnMessage;
    if (!messages.empty()){
        returnMessage = messages.front();
        messages.pop();
    }
    else{
        returnMessage = emptyMessage;
    }
    return returnMessage;
}

Board::Board(int xSize, int ySize){
        tileSize = 80;
        windowWidth = 700;
        windowHeight  = 800;
        lowerLeftBlack = true;
        boardName = "Chess Board";
        //setup default layout
        //This size is number of squares
        boardSetup.xBoardSize = xSize;
        boardSetup.yBoardSize = ySize;
        boardPaneXCenter = windowWidth / 2.0;
        boardPaneYCenter = windowHeight / 2.0;
        fillBoardWithTiles();



}

Board::Board(BoardSetup boardSetup){
}

Board::Board (): Board{8,8}{
}


int Board::closeDisplay(){
    window.close();
    return 1;
}

int Board::placePiece( Piece piece, int xCoord, int yCoord){
    PlacedPiece newPiece;
    newPiece.puzzlePiece = piece;
    newPiece.piecePosition.x = xCoord;
    newPiece.piecePosition.y = yCoord;
    //check if piece already there and delete it
    if (peekPiece (xCoord, yCoord)){
        removePiece (xCoord, yCoord);
    }
    //must be placed on tiled piece.
    if (peekTile (xCoord, yCoord)){
        boardSetup.boardPieces.push_back(newPiece);
        return 1;
    }
    return 0;

}

int Board::placeTile( Piece piece, int xCoord, int yCoord){
    PlacedPiece newPiece;
    newPiece.puzzlePiece = piece;
    newPiece.piecePosition.x = xCoord;
    newPiece.piecePosition.y = yCoord;
    //check if piece already there and delete it
    if (peekTile (xCoord, yCoord)){
        removeTile (xCoord, yCoord);
    }
    boardSetup.boardTiles.push_back(newPiece);
    return 1;

}

int Board::placeHighlight( Piece piece, int xCoord, int yCoord){
    PlacedPiece newPiece;
    newPiece.puzzlePiece = piece;
    newPiece.piecePosition.x = xCoord;
    newPiece.piecePosition.y = yCoord;
    //check if piece already there and delete it
    if (peekHighlight (xCoord, yCoord) != NullPiece){
        removeHighlight (xCoord, yCoord);
    }
    //place only on tiled squares.
    if (peekTile (xCoord, yCoord)){
        boardSetup.boardHighlights.push_back(newPiece);
    } else{
        return 0;
    }
    return 1;
}

int Board::removePiece( int xCoord, int yCoord ){
    for (int i = 0; i < boardSetup.boardPieces.size(); i++){
        if (boardSetup.boardPieces[i].piecePosition.x == xCoord &&
            boardSetup.boardPieces[i].piecePosition.y == yCoord)
        {
            boardSetup.boardPieces.erase(boardSetup.boardPieces.begin()+i);
            i--;
        }
    }
    return 1;
}

int Board::removeTile( int xCoord, int yCoord ){
    for (int i = 0; i < boardSetup.boardTiles.size(); i++){
        if (boardSetup.boardTiles[i].piecePosition.x == xCoord &&
            boardSetup.boardTiles[i].piecePosition.y == yCoord)
        {
            boardSetup.boardTiles.erase(boardSetup.boardTiles.begin()+i);
            i--;
        }
    }
    return 1;
}

int Board::removeHighlight( int xCoord, int yCoord ){
    for (int i = 0; i < boardSetup.boardHighlights.size(); i++){
        if (boardSetup.boardHighlights[i].piecePosition.x == xCoord &&
            boardSetup.boardHighlights[i].piecePosition.y == yCoord)
        {
            boardSetup.boardHighlights.erase(boardSetup.boardHighlights.begin()+i);
            i--;
        }
    }
    return 1;
}

int Board::setBoardName (std::string newBoardName){
    boardName = newBoardName; 
    window.setTitle(boardName);
    return 1;
}

int Board::setBoardSize(int xSize, int ySize){
    boardSetup.xBoardSize = xSize;
    boardSetup.yBoardSize = ySize;
    boardSetup.boardPieces.clear();
    boardSetup.boardTiles.clear();
    boardSetup.boardHighlights.clear();
    fillBoardWithTiles();

    return 1;
}

    Piece Board::peekPiece ( int xCoord, int yCoord ){
        for (int i = 0; i < boardSetup.boardPieces.size(); i++){
            if (boardSetup.boardPieces[i].piecePosition.x == xCoord &&
                boardSetup.boardPieces[i].piecePosition.y == yCoord)
            {
                return boardSetup.boardPieces[i].puzzlePiece;
            }
        }
        return NullPiece;
    }

    Piece Board::peekHighlight ( int xCoord, int yCoord ){
        for (int i = 0; i < boardSetup.boardHighlights.size(); i++){
            if (boardSetup.boardHighlights[i].piecePosition.x == xCoord &&
                boardSetup.boardHighlights[i].piecePosition.y == yCoord)
            {
                return boardSetup.boardHighlights[i].puzzlePiece;
            }
        }
        return NullPiece;
    }

    Piece Board::peekTile ( int xCoord, int yCoord ){
        for (int i = 0; i < boardSetup.boardTiles.size(); i++){
            if (boardSetup.boardTiles[i].piecePosition.x == xCoord &&
                boardSetup.boardTiles[i].piecePosition.y == yCoord)
            {
                return boardSetup.boardTiles[i].puzzlePiece;
            }
        }
        return NullPiece;

    }

Message Board::GetMessage(){
    Message newMessage;
    sf::Event event;
    if (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed){
            newMessage.boardMessageType = closeBoard;
        }
        if (event.type == sf::Event::MouseButtonPressed){
            if (event.mouseButton.button == sf::Mouse::Left){
                //figure out which square if any was clicked on
                int xSquare = getXTileColumnOnGrid (
                    event.mouseButton.x,
                    boardPaneXCenter,
                    tileSize,
                    boardSetup.xBoardSize);

                int ySquare = getYTileRankOnGrid (
                    event.mouseButton.y,
                    boardPaneYCenter,
                    tileSize,
                    boardSetup.yBoardSize);

                newMessage.boardMessageType = squareClick;
                newMessage.boardPosition.x = xSquare;
                newMessage.boardPosition.y = ySquare;
            }
        }
    }
    return newMessage;

}

int Board::fillBoardWithTiles(){
        PlacedPiece tempPiece;
        //Generate board tiles - data structure should support odd shaped puzzles, thus
        //the reason for dealing with tiles individually
        for (int y = 1; y <= boardSetup.yBoardSize; y++){
            for (int x = 1; x <= boardSetup.xBoardSize; x++){
                tempPiece.piecePosition.x = x;
                tempPiece.piecePosition.y = y;
                if ((x + y) % 2 == 0){
                    tempPiece.puzzlePiece = BSquare;
                }
                else{
                    tempPiece.puzzlePiece = WSquare;
                }
                boardSetup.boardTiles.push_back(tempPiece);
            }
        } 

}

int Board::openDisplay (){
    window.create(sf::VideoMode(windowWidth, windowHeight), boardName);
    updateDisplay();
    return 1;
}

int Board::DrawSpritesFromVector(std::vector <PlacedPiece> boardPieces){
    sf::Sprite sprite;
    for (PlacedPiece i : boardPieces){
            float xCoord = getXTileCoordOnGrid(i.piecePosition.x, boardPaneXCenter, tileSize, boardSetup.xBoardSize); 
            float yCoord = getYTileCoordOnGrid(i.piecePosition.y, boardPaneYCenter, tileSize, boardSetup.yBoardSize);
            switch (i.puzzlePiece){
                case BSquare:
                    sprite = boardSprites.blackSquare;
                    break;
                case WSquare:
                    sprite = boardSprites.whiteSquare;
                    break;
                case BKing:
                    sprite = boardSprites.BKing;
                    break;
                case BQueen:
                    sprite = boardSprites.BQueen;
                    break;
                case BRook:
                    sprite = boardSprites.BRook;
                    break;
                case BBishop:
                    sprite = boardSprites.BBishop;
                    break;
                case BKnight:
                    sprite = boardSprites.BKnight;
                    break;
                case BPawn:
                    sprite = boardSprites.BPawn;
                    break;
                case WKing:
                    sprite = boardSprites.WKing;
                    break;
                case WQueen:
                    sprite = boardSprites.WQueen;
                    break;
                case WRook:
                    sprite = boardSprites.WRook;
                    break;
                case WBishop:
                    sprite = boardSprites.WBishop;
                    break;
                case WKnight:
                    sprite = boardSprites.WKnight;
                    break;
                case WPawn:
                    sprite = boardSprites.WPawn;
                    break;
                case Highlight:
                    sprite = boardSprites.highlight;
                    break;
                case Error:
                    sprite = boardSprites.Error;
                    break;
                default:
                    sprite = boardSprites.Error;
                    break;
            }
            sprite.setPosition(sf::Vector2f(xCoord, yCoord));
            window.draw(sprite);
    }

}

int Board::updateDisplay (){

    int centoffx = (windowWidth - tileSize*8)/2; // center offset for x
    int centoffy = (windowHeight - tileSize*8)/2; // center offset for y
    float boardXCenter = windowWidth / 2.0;
    float boardYCenter = windowHeight / 2.0;


    if (window.isOpen())
    {

        window.clear();
        //Draw board sprites
        //The order is important since these classes of sprites can overlap
        DrawSpritesFromVector(boardSetup.boardTiles);
        DrawSpritesFromVector(boardSetup.boardHighlights);
        DrawSpritesFromVector(boardSetup.boardPieces);

        window.display();
    }
    return 1;
}
    
