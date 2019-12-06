#include "../include/board.hpp"
#include <iostream>

void printHappyThanksgiving(std::string name = "") {
    if(name == "") // if there is no name 
        std::cout << "Happy Thanksgiving!" << std::endl;
    else
        std::cout << "Happy Thanksgiving, " << name << "!" << std::endl;
}
int main(){

    int exitValue;
    Board testBoard{8, 8};
    bool playContinue = true;
    Message currentMessage;
    testBoard.setBoardName("Hourglass Challenge \"Do Not Tread Lightly My Friend!\"");
    testBoard.placePiece(WKing, 5, 1);
    testBoard.placePiece(WQueen, 4, 1);
    testBoard.placePiece(WRook, 1, 1);
    testBoard.placePiece(WRook, 8, 1);
    testBoard.placePiece(WKnight, 2, 1);
    testBoard.placePiece(WKnight, 7, 1);
    testBoard.placePiece(WBishop, 3, 1);
    testBoard.placePiece(WBishop, 6, 1);
    testBoard.placePiece(WPawn, 1, 2);
    testBoard.placePiece(WPawn, 2, 2);
    testBoard.placePiece(WPawn, 3, 2);
    testBoard.placePiece(WPawn, 4, 2);
    testBoard.placePiece(WPawn, 5, 2);
    testBoard.placePiece(WPawn, 6, 2);
    testBoard.placePiece(WPawn, 7, 2);
    testBoard.placePiece(WPawn, 8, 2);
    testBoard.placePiece(BKing, 5, 8);
    testBoard.placePiece(BQueen, 4, 8);
    testBoard.placePiece(BRook, 1, 8);
    testBoard.placePiece(BRook, 8, 8);
    testBoard.placePiece(BKnight, 2, 8);
    testBoard.placePiece(BKing, 5, 8);
    testBoard.placePiece(BQueen, 4, 8);
    testBoard.placePiece(BRook, 1, 8);
    testBoard.placePiece(BRook, 8, 8);
    testBoard.placePiece(BKnight, 7, 8);
    testBoard.placePiece(BBishop, 3, 8);
    testBoard.placePiece(BBishop, 6, 8);
    testBoard.placePiece(BPawn, 1, 7);
    testBoard.placePiece(BPawn, 2, 7);
    testBoard.placePiece(BPawn, 3, 7);
    testBoard.placePiece(BPawn, 4, 7);
    testBoard.placePiece(BPawn, 5, 7);
    testBoard.placePiece(BPawn, 6, 7);
    testBoard.placePiece(BPawn, 7, 7);
    testBoard.placePiece(BPawn, 8, 7);
    testBoard.openDisplay();
    Piece selectedPiece = NullPiece;
    int selectedX = 0;
    int selectedY = 0;
    int updateCounter = 0;
    while(playContinue){
        testBoard.updateDisplay();
        updateCounter++;
        currentMessage = testBoard.GetMessage();
        if (currentMessage.boardMessageType == closeBoard){
            testBoard.closeDisplay();
            playContinue = false;
        }
        if (currentMessage.boardMessageType == squareClick){
            int xSquare = currentMessage.boardPosition.x;
            int ySquare = currentMessage.boardPosition.y;
            if (xSquare > 0 && ySquare > 0){
                if (selectedPiece){//} && testBoard.peekTile(xSquare, ySquare)){
                    //order of remove and place piece is important
                    //so that a piece can't remove itself.
                    if (testBoard.peekTile(xSquare, ySquare)){
                        testBoard.removePiece (selectedX, selectedY);
                        testBoard.placePiece (selectedPiece, xSquare, ySquare);
                        testBoard.removeHighlight (selectedX, selectedY);
                        selectedPiece = NullPiece;
                        selectedX = 0;
                        selectedY = 0;
                    }
                }else{
                    if (selectedPiece = testBoard.peekPiece(xSquare, ySquare)){
                        testBoard.placeHighlight(Highlight, xSquare, ySquare);
                        selectedX = xSquare;
                        selectedY = ySquare;
                    }
                }
            }
        }
    }
    std::cout << "Gameover\n";
    printHappyThanksgiving("Jonah");
    return 0;
}

