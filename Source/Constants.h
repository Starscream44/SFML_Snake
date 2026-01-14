#pragma once

namespace SnakeGame
{
    constexpr int CellSize = 32;
    constexpr int GridW = 25;
    constexpr int GridH = 18;

    constexpr int HudHeight = 64;                //HUD
    constexpr int WindowWidth = GridW * CellSize;
    constexpr int WindowHeight = HudHeight + GridH * CellSize;

    static constexpr int DefaultAppleCount = 10;

    constexpr float MoveInterval = 0.12f;

    constexpr const char* RecordsFileName = "records.txt";
    constexpr std::size_t RecordsMaxCount = 10;      // Y (top 10)
	constexpr std::size_t RecordsPopupCount = 5;     // X (топ 5 for popup)
}