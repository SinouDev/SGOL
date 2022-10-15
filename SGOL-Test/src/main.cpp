#define __SGOL_TEST_SAMPLE
#define __SGOL_ENABLE_MEM_TRACKER
#include "SGOL/Reference.hpp"
#include "SGOL/Array2D.hpp"

#include "EntityTest.hpp"

#include <memory>

int main(void)
{
    using namespace SGOL;

	//a();
		
	{
		auto a = Reference::MakeShared<Player>(545U, 2441U);

		std::cout << g_MemUse;
		Reference::Shared<Entity> fd = Reference::MakeShared<Player>(54U, 64U);
		
		{
			auto b = std::make_shared<Player>(5151U, 648U);
			std::shared_ptr<Entity> fb = b;
			std::cout << g_MemUse;
			Reference::Shared<Entity> vecPtr = Reference::MakeShared<Player>(54U, 42U);
			Reference::Unique<Entity> vecPtr1 = Reference::MakeUnique<Player>(100U, 114U);
			//Reference::Unique<Entity> sss = vecPtr1;

			std::cout << g_MemUse;

			{
				Reference::Shared<Entity> vecPtr2 = vecPtr;

				{
					Reference::Weak<Entity> vecPtrWeak = a;
				}
			}

			std::cout << g_MemUse;

			Reference::Unique<Entity> player = Reference::MakeUnique<Player>(100U, 510U);
		}

		std::cout << g_MemUse;
		//player->Method();
		//player->MethodPure();
		//Reference::Unique<Entity> entity = player;
		//entity->Method();

		//std::unique_ptr<Entity> player1 = std::make_unique<Player>(528U, 245U);
		//player1->Method();
		//player1->MethodPure();
		//std::unique_ptr<Entity> entity1 = player1;

		//Player pl(10U, 50U);
		
		//std::cin.get();
		SGOL::Array2D<Player> array(400, 400);
		std::cout << g_MemUse;
		
	}

	std::cout << g_MemUse;

    return 0;
}