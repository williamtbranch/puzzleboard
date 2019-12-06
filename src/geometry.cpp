#include "../include/geometry.hpp"
#include <iostream>

float getXTileCoordOnGrid(
    int xTile,
    float boardCenterX,
    int tileWidth,
    int numXTiles)
{
    float boardXSize = tileWidth * numXTiles;
    float boardLeftEdge = boardCenterX - (boardXSize / 2.0);
    return boardLeftEdge + (xTile - 1) * tileWidth;
}

float getYTileCoordOnGrid(
    int yTile,
    float boardCenterY,
    int tileWidth,
    int numYTiles)
{
    float boardYSize = tileWidth * numYTiles;
    float boardTopEdge = boardCenterY - (boardYSize / 2.0);
    return boardTopEdge + (numYTiles - yTile) * tileWidth;
}

int getXTileColumnOnGrid(
    float input,
    float boardCenterX,
    float tileWidth,
    int numXTiles)
    {
        float paneWidth = tileWidth * numXTiles;
        float leftEdge = boardCenterX - paneWidth / 2.0;
        int squareOffset = ((input - leftEdge) / tileWidth) + 1;
        if (squareOffset < 1 || squareOffset > numXTiles){
            squareOffset = 0;
        }
        return squareOffset;
    }

int getYTileRankOnGrid(
    float input,
    float boardCenterY,
    float tileWidth,
    int numYTiles)
    {
        float paneWidth = tileWidth * numYTiles;
        float topEdge = boardCenterY - paneWidth / 2.0;
        int squareOffset = ((input - topEdge) / tileWidth);
        //invert Y number due to board numbering
        //moving from bottom to top
        squareOffset = numYTiles - squareOffset;
        if (squareOffset < 1 || squareOffset > numYTiles){
            squareOffset = 0;
        }
        return squareOffset;
    }