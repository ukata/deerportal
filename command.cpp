#include "game.h"
#include "command.h"

Command::Command(efc::Game &currentGame) :
    game(currentGame)
{

}

void Command::removeCard(int playerNumber)
{
    /*! This should works as following:
     * - iterate over BoardDiamondSeq
     * - find diamonds belonging to the playerNumber
     * - create an array from the aboves
     * - get a random element
     * - remove from the board - set not active
     */

    std::vector<int> diamonds;
    for (auto&& i: game.boardDiamonds.diamonds)
    {
        int fieldNumber = i.playerNumber;
        if ((fieldNumber==playerNumber) && (i.boardPosition>-1)
                && (i.idNumber<4))
        {
            diamonds.push_back(i.boardPosition);
        }
    }
    int numberDiamonds = diamonds.size();
    if (numberDiamonds>=0)
    {
        int elemToRemove = rand() %  numberDiamonds;
        game.boardDiamonds.collectField(diamonds[elemToRemove]);
    }


}
void Command::removeDiamond(int playerNumber)
{
    /*! This should works as following:
     * - iterate over BoardDiamondSeq
     * - find diamonds belonging to the playerNumber
     * - create an array from the aboves
     * - get a random element
     * - remove from the board - set not active
     */

    std::vector<int> diamonds;
    for (auto&& i: game.boardDiamonds.diamonds)
    {
        int fieldNumber = i.playerNumber;
        if ((fieldNumber==playerNumber) && (i.boardPosition>-1)
                && (i.idNumber==4))
        {
            diamonds.push_back(i.boardPosition);
        }
    }
    int numberDiamonds = diamonds.size();
    if (numberDiamonds>=0)
    {
        int elemToRemove = rand() %  numberDiamonds;
        game.boardDiamonds.collectField(diamonds[elemToRemove]);
    }


}

void Command::freezePlayer(int playerNumber)
{
    game.players[playerNumber].frozenLeft += 1;
}

void Command::processField(int pos)
{
    if (game.boardDiamonds.ifFieldIsEmpty(pos)==false)
    {
        game.sfx.playCollect();
        if (game.boardDiamonds.getNumberForField(pos)==4)
        {
            game.players[game.turn].cash += 1;

        } else if (game.boardDiamonds.getNumberForField(pos)<4)
        {
            processCard(pos);
        }

        game.boardDiamonds.collectField(pos);
    }
}

void Command::processCard(int pos)
{
    int tokenNumber = game.boardDiamonds.getNumberForField(pos);
    std::string cardType = game.cardsDeck.getTitle(tokenNumber);
    if (tokenNumber!=game.turn)
    {
        if (cardType == "diamond")
        {
            removeDiamond(game.boardDiamonds.getNumberForField(pos));

        } else if (cardType == "stop")
        {
            freezePlayer(tokenNumber);
        } else if (cardType == "card")
        {
            removeCard(game.boardDiamonds.getNumberForField(pos));

        }
    }
    game.cardsDeck.nextCard(tokenNumber);
    game.sfx.playCard();
}
