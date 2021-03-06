// ItemMinecart.h

// Declares the various minecart ItemHandlers





#pragma once

#include "../Entities/Minecart.h"





class cItemMinecartHandler :
	public cItemHandler
{
	typedef cItemHandler super;
	
public:
	cItemMinecartHandler(int a_ItemType) :
		super(a_ItemType)
	{
	}
	
	
	
	virtual bool OnItemUse(cWorld * a_World, cPlayer * a_Player, const cItem & a_Item, int a_BlockX, int a_BlockY, int a_BlockZ, eBlockFace a_Dir) override
	{
		if (a_Dir < 0)
		{
			return false;
		}
		
		// Check that there's rail in there:
		BLOCKTYPE Block = a_World->GetBlock(a_BlockX, a_BlockY, a_BlockZ);
		switch (Block)
		{
			case E_BLOCK_MINECART_TRACKS:
			case E_BLOCK_POWERED_RAIL:
			case E_BLOCK_DETECTOR_RAIL:
			case E_BLOCK_ACTIVATOR_RAIL:
			{
				// These are allowed
				break;
			}
			default:
			{
				LOGD("Used minecart on an unsuitable block %d (%s)", Block, ItemTypeToString(Block).c_str());
				return false;
			}
		}
		
		double x = (double)a_BlockX + 0.5;
		double y = (double)a_BlockY + 0.5;
		double z = (double)a_BlockZ + 0.5;
		cMinecart * Minecart = NULL;
		switch (m_ItemType)
		{
			case E_ITEM_MINECART:             Minecart = new cRideableMinecart     (x, y, z, cItem(), 1); break;
			case E_ITEM_CHEST_MINECART:       Minecart = new cMinecartWithChest    (x, y, z); break;
			case E_ITEM_FURNACE_MINECART:     Minecart = new cMinecartWithFurnace  (x, y, z); break;
			case E_ITEM_MINECART_WITH_TNT:    Minecart = new cMinecartWithTNT      (x, y, z); break;
			case E_ITEM_MINECART_WITH_HOPPER: Minecart = new cMinecartWithHopper   (x, y, z); break;
			default:
			{
				ASSERT(!"Unhandled minecart item");
				return false;
			}
		}  // switch (m_ItemType)
		Minecart->Initialize(a_World);

		if (!a_Player->IsGameModeCreative())
		{
			a_Player->GetInventory().RemoveOneEquippedItem();
		}
		return true;
	}
	
} ;




