/**
* This file is part of
* 
* 8888888b.                    888    888      888      d8b                  
* 888  "Y88b                   888    888      888      Y8P                  
* 888    888                   888    888      888                           
* 888    888  .d88b.   8888b.  888888 88888b.  888      888  8888b.  888d888 
* 888    888 d8P  Y8b     "88b 888    888 "88b 888      888     "88b 888P"   
* 888    888 88888888 .d888888 888    888  888 888      888 .d888888 888     
* 888  .d88P Y8b.     888  888 Y88b.  888  888 888      888 888  888 888     
* 8888888P"   "Y8888  "Y888888  "Y888 888  888 88888888 888 "Y888888 888   
* 
* Copyright © 2012 Emil Sandstø, Sebastian Reinhard
* 
*/

#include "Inventory.h"
#include <string.h>

Inventory::Inventory()
{
    Clear();
}

void Inventory::AddItem(Weapon *item)
{
         if(!m_items[0]) m_items[0] = item;
    else if(!m_items[1]) m_items[1] = item;
    else if(!m_items[2]) m_items[2] = item;
    else if(!m_items[3]) m_items[3] = item;
    else if(!m_items[4]) m_items[4] = item;
}

void Inventory::RemoveItem(Weapon* item)
{
         if(m_items[0] == item) m_items[0] = 0;
    else if(m_items[1] == item) m_items[1] = 0;
    else if(m_items[2] == item) m_items[2] = 0;
    else if(m_items[3] == item) m_items[3] = 0;
    else if(m_items[4] == item) m_items[4] = 0;
}

void Inventory::Clear()
{
    memset(m_items, 0, 5 * sizeof(Weapon *));
}