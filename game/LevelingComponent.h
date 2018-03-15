#pragma once

#include"libs.h"

class LevelingComponent
{
private:
	//Variables
	unsigned long level;
	unsigned long experience;
	unsigned long experience_next;

	//Private functions
	bool checkLevelUp()
	{
		while (this->experience >= this->experience_next)
		{
			this->level++;

			this->experience -= this->experience_next;

			this->updateExperienceNext();

			if (this->experience < 0)
				this->experience = 0;

			return true;
		}

		return false;
	}

	void updateExperienceNext()
	{
		this->experience_next = (50 * pow(this->level, 3) - 150 * pow(this->level, 2) + 400 * this->level) / 3;
	}

public:
	//Constructors/Destructors
	LevelingComponent(const unsigned long level = 1)
	{
		this->level = level;
		if (this->level <= 0)
			this->level = 1;

		this->experience = 0;
		this->experience_next = 0;

		this->updateExperienceNext();
	}
	~LevelingComponent() {}
	
	//Operators

	//Accessors
	inline const unsigned long& getLevel() const 
	{
		return this->level;
	}
	inline const unsigned long& getExperience() const
	{
		return this->experience;
	}
	inline const unsigned long& getExperienceNext() const
	{
		return this->experience_next;
	}

	//Modifiers

	//Functions
	bool gainExperience(const unsigned long& experience)
	{
		this->experience += experience;

		if (this->checkLevelUp())
			return true;

		return false;
	}

	const unsigned long& removeExperience(const unsigned long& experience)
	{
		this->experience -= experience;

		if (this->experience < 0)
			this->experience = 0;

		return experience;
	}
};
