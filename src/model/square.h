#ifndef SQUARE_H
#define SQUARE_H

class Square {
    private:
        //checks if square is bomb or not
        bool isBomb;
        //checks if square has been revealed or not
        bool isRevealed;
        //checks if square has been flagged or not
        bool isFlagged;
        // number of adjacent bombs around a square
        int adjacentBombs;
    public:
        //constructor for default square
        Square();
        //sets bombs surrounding a square 
        void setAdjacentBomb(int num);
        //returns the number of bombs surrounding a square 
        void getAdjacentBomb(); const
        //places or removes flag on a square
        void toggleFlag();
        //returns if a square as a bomb
        bool getisBomb(); const
        //returns if square has already been revealed(prevents clicking the same tile again) 
        bool getisRevealed(); const
        //returns if square has been flagged or not
        bool getisFlagged(); const
        
};