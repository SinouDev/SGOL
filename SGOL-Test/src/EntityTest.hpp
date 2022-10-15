#pragma once

#ifdef __SGOL_TEST_SAMPLE
#undef __SGOL_TEST_SAMPLE

#include <iostream>

class Entity
{
public:

	Entity(uint32_t x, uint32_t y)
		: m_X(x), m_Y(y)
	{
		//std::cout << "Entity created with x: " << x << " y: " << y << std::endl;
	}

	Entity()
		: m_X(20), m_Y(50)
	{
		//std::cout << "Entity created" << std::endl;
	}

	Entity(Entity& ss)
		: m_X(ss.m_X), m_Y(ss.m_Y)
	{
		//std::cout << "Entity copied" << std::endl;
	}

	Entity(Entity&& ss) noexcept
		: m_X(std::move(ss.m_X)), m_Y(std::move(ss.m_Y))
	{
		//std::cout << "Entity moved" << std::endl;
	}

	virtual ~Entity()
	{
		//std::cout << "Entity destroyed" << std::endl;
	}

	virtual void MethodPure() const = 0;

	virtual void Method() const
	{
		//std::cout << "I am a method of Entity" << std::endl;
	}

private:
	uint32_t m_X, m_Y;
};

class Player : public Entity
{
public:

	Player()
		: Entity(0U, 0U)
	{

	}

	Player(uint32_t x, uint32_t y)
		: Entity(x, y)
	{

	}

	virtual void Method() const override
	{
		// Do something
		std::cout << "I am a method of Player" << std::endl;
	}

	virtual void MethodPure() const override
	{
		// Do something
		std::cout << "I am a pure method of Player" << std::endl;
	}
};

#endif // __SGOL_TEST_SAMPLE
