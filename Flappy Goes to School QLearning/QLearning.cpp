#include "QLearning.h"



QLearning::QLearning(double learningRate, double discount)
{
	mLearningRate = learningRate;
	mDiscount = discount;
	mStateCounter = 0;
	mStateID.clear();
	mStates.clear();
	mActions.clear();
	mRewards.clear();

	for (int i = 0; i < MAX_STATE; i++)
	{
		for (int j = 0; j < MAX_ACTION; j++)
		{
			mQValue[i][j] = 0.0;
		}
	}
}


QLearning::~QLearning()
{
}

int QLearning::getAction(string state)
{
	if (mStateID.find(state) == mStateID.end())
	{
		mStateID[state] = ++mStateCounter;
	}

	int currState = mStateID[state];
	double high = -DBL_MAX;
	int pos = -1;

	for (int i = 0; i < MAX_ACTION; i++)
	{
		if (Helper::validMove(state, i) && mQValue[currState][i] > high)
		{
			high = mQValue[currState][i];
			pos = i;
		}
	}

	mStates.push_back(state);
	mActions.push_back(pos);

	return pos;
}

void QLearning::addReward(int reward)
{
	mRewards.push_back(reward);
}

void QLearning::update()
{
	reverse(mStates.begin(), mStates.end());
	reverse(mActions.begin(), mActions.end());
	reverse(mRewards.begin(), mRewards.end());

	for (int i = 1; i < mStates.size(); i++)
	{
		int currState = mStateID[mStates[i]];
		int currAction = mActions[i];
		int resultState = mStateID[mStates[i - 1]];
		int reward = mRewards[i - 1];

		double resultReward = -DBL_MAX;

		for (int j = 0; j < MAX_ACTION; j++)
		{
			if (Helper::validMove(mStates[i - 1], j))
			{
				resultReward = fmax(resultReward, mQValue[resultState][j]);
			}
		}

		mQValue[currState][currAction] = (1.0 - mLearningRate) * (mQValue[currState][currAction]) + mLearningRate * (reward + mDiscount * resultReward);
	}

	mStates.clear();
	mActions.clear();
	mRewards.clear();
}

void QLearning::readQValue(string path)
{
	ifstream file(path);
	string state;
	mStateID.clear();
	mStateCounter = 0;

	for (int i = 0; i < MAX_STATE; i++)
	{
		for (int j = 0; j < MAX_ACTION; j++)
		{
			mQValue[i][j] = 0.0;
		}
	}

	while (file >> state)
	{
		mStateID[state] = ++mStateCounter;

		for (int i = 0; i < MAX_ACTION; i++)
		{
			double value;
			file >> value;
			mQValue[mStateCounter][i] = value;
		}
	}
}

void QLearning::saveQValue(string path)
{
	ofstream file(path);
	map<string, int>::iterator it;

	for (it = mStateID.begin(); it != mStateID.end(); it++)
	{
		file << it->first;
		int currState = it->second;

		for (int i = 0; i < MAX_ACTION; i++)
		{
			file << " " << mQValue[currState][i];
		}
		file << endl;
	}
}