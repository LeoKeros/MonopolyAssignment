#include "CMonopoly.h"

/*
Set up the game by declaring the number of rounds and setting up the players.
*/
CMonopoly::CMonopoly()
{
	mNumRounds = 20;

	for (ushort count = 1; count <= mNumPlayers; count++)
	{
		mPlayers.push_back(t_playerpointer(new CPlayer(count)));
	}
}

CMonopoly::~CMonopoly()
{
}

/*
Rarely used, due to how often << is used in outputs.
Couldn't figure out how to use this function with this in mind.
Outputs the message it is passed.
*/
void CMonopoly::Output(const string &message)
{
	cout << message << endl;
}

/*
Starts the game by outputting the welcome message.
The game lasts until it reaches the round limit, or until all but one player has gone bankrupt.
Each round consists of each player taking a turn.
A turn consists of:
- Check if player can afford to unmortgage any of their properties.
- Roll Dice to move.
- Land on space and trigger it's effect.
- Output balance.
*/
void CMonopoly::Play()
{
	Output(WELCOME_MESSAGE);
	cout << endl;

	for (ushort round = 0; round < mNumRounds && mPlayers.size() != 1; round++)
	{
		for (auto it = mPlayers.begin(); it != mPlayers.end(); it++)
		{
			(*it)->Unmortgage();
			(*it)->RollDice();
			cout << (*it)->GetID() << LAND_MESSAGE << mBoard[(*it)->GetLocation()]->GetName() << endl;
			mBoard[(*it)->GetLocation()]->LandOn((*it));
			
			//If the player has negative funds at this stage, it means they have no properties left
			//to mortgage, and are bankrupt. Remove them from the game.
			if ((*it)->GetMoneyTotal() < 0)
			{
				cout << (*it)->GetID() << BANKRUPT_MESSAGE;
				mPlayers.erase(it);
			}
			else
			{
				(*it)->OutputBalance();
			}
			cout << endl;
		}
		//Draw a line between rounds to make them easier to tell apart.
		Output(ROUND_SPLITTER);
	}

	//If there is only one player left, they are the winner.
	//If there is more than one player, the one with the most money wins.
	//If they have the same amount of money, add them to the tie list.
	//If the tie list has any players in it after all players have been checked, a tie has occurred; Output accordingly.
	if (mPlayers.size() == 1)
	{
		cout << mPlayers.front()->GetID() << WIN_MESSAGE << endl;
	}
	else
	{
		CPlayer* winner = mPlayers.front().get();
		vector <EPlayerPiece> tiesDetected; //If players are detected with the same money total as the "winner", add them to this list.

		for (auto it = mPlayers.begin() + 1; it != mPlayers.end(); it++)
		{
			if (winner->GetMoneyTotal() < (*it)->GetMoneyTotal())
			{
				winner = (*it).get();
				tiesDetected.clear(); //Clears the tie list.
			}
			else if (winner->GetMoneyTotal() == (*it)->GetMoneyTotal()) tiesDetected.push_back((*it)->GetID());
		}

		//If a tie wasn't detected, output the winner.
		//Otherwise, output the names of each of the players involved in the tie (Accounts for more than 2 players)
		if (tiesDetected.size() == 0)
		{
			cout << winner->GetID() << WIN_MESSAGE << endl;
		}
		else
		{
			cout << TIE_MESSAGE[0] << winner->GetID();
			for (auto player : tiesDetected)
			{
				cout << TIE_MESSAGE[1] << player;
			}
			cout << endl;
		}
	}
}

// Use a file stream to read the monopoly and seed files.
// If reading fails, return false.
// If reading is successful, return true.
bool CMonopoly::LoadFiles()
{

	ifstream fileReader(SETUP_FILE);
	if (fileReader)
	{
		ushort jailLocation; //This is stored so that the value can be passed to the GoToJail space.
		ushort goToJailLocation; //This is stored so that it's local jail location can be set after loading is finished.
		ushort spaceType; //The number at the start of each line is loaded into this for identification.
		string sInput; //Used for any multi-part names. Stores parts of names.
		string name; //The name of the space is the second part of the line, composed of multiple parts. Read into sInput and append.
		ushort propertyData[3]; //Cost, rent, group

		//Read until the end of the file is reached.
		while (!fileReader.eof())
		{
			fileReader >> spaceType; //Space type
			fileReader >> name; //The first word in any name
			//Read data based on the type of space, then create and add to the board.
			switch (spaceType)
			{
			case STProperty:
				fileReader >> sInput; //Properties all have 2 words in their name.
				fileReader >> propertyData[0]; //Cost
				fileReader >> propertyData[1]; //Rent
				fileReader >> propertyData[2]; //Group

				mBoard.push_back(t_spacepointer(new CProperty(name + " " + sInput, mBoard.size(), propertyData[0], propertyData[1], propertyData[2])));
				break;
			case STAirport:
				fileReader >> sInput; //Airports all have 2 words in their name.
				mBoard.push_back(t_spacepointer(new CAirport(name + " " + sInput, mBoard.size())));
				break;
			case STGo:
				mBoard.push_back(t_spacepointer(new CGo(name, mBoard.size())));
				break;
			case STBonus:
				mBoard.push_back(t_spacepointer(new CBonus(name, mBoard.size())));
				break;
			case STJail:
				jailLocation = mBoard.size(); //Record where the jail is located.
				mBoard.push_back(t_spacepointer(new CJail(name, mBoard.size())));
				break;
			case STFreeParking:
				fileReader >> sInput; //"Free Parking" is two words.
				mBoard.push_back(t_spacepointer(new CFreeParking(name + " " + sInput, mBoard.size())));
				break;
			case STPenalty:
				mBoard.push_back(t_spacepointer(new CPenalty(name, mBoard.size())));
				break;
			case STGoToJail:
				goToJailLocation = mBoard.size(); //Record where the "GoToJail" space is in the board vector.
				fileReader >> sInput; //"to"
				name.append(" " + sInput); //Frees up sInput for the next part of the name.
				fileReader >> sInput;//"Jail"
				mBoard.push_back(t_spacepointer(new CGoToJail(name + " " + sInput, mBoard.size())));
				break;
			}
		}
		//Tell the "Go To Jail" space where the Jail is.
		static_cast<CGoToJail*>(mBoard[goToJailLocation].get())->SetJailLocation(jailLocation);
	}
	else
	{
		return false; //If the file failed to open.
	}
	fileReader.close();

	fileReader.open(RANDOM_SEED_FILE);
	if (fileReader)
	{
		unsigned int seed;
		fileReader >> seed;
		srand(seed); //Seed the random number generator. 
	}
	else
	{
		return false; //File failed to open
	}

	return true; //All files were read successfully.
}
