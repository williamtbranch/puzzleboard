#pragma once
float getXTileCoordOnGrid(
    int xTile,
    float boardCenterX,
    int tileWidth,
    int numXTiles);

float getYTileCoordOnGrid(
    int yTile,
    float boardCenterY,
    int tileWidth,
    int numYTiles);

int getXTileColumnOnGrid(
    float input,
    float boardCenterX,
    float tileWidth,
    int numXTiles);

int getYTileRankOnGrid(
    float input,
    float boardCenterY,
    float tileWidth,
    int numYTiles);