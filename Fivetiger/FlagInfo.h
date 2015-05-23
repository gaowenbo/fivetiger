#pragma once
class FlagInfo
{
private:
	int flag;
	int goal;
	bool isOnTheOffensive;
public:
	FlagInfo(void);
	FlagInfo(const FlagInfo& info);
	~FlagInfo(void);
	bool getIsOnTheOffensive() const { return isOnTheOffensive; }
	void setIsOnTheOffensive(bool val) { isOnTheOffensive = val; }
	int getFlag() const { return flag; }
	void setFlag(int val) { flag = val; }
	int getGoal() const { return goal; }
	void setGoal(int val) { goal = val; }
};

