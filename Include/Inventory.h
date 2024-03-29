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

#ifndef INVENTORY_H
#define INVENTORY_H

#include "Weapon.h"

class Inventory
{
public:
    Inventory();

    void AddItem(Weapon *item);
    void RemoveItem(Weapon *item);
    void Clear();

    Weapon **GetItems()
    {
        return m_items;
    }

    Weapon *GetItem(int index)
    {
        return m_items[index];
    }

    Weapon *GetSelected()
    {
        return m_items[m_index];
    }

    int GetIndex()
    {
        return m_index;
    }

    Weapon *Next();
    Weapon *Previous();

    int NextIndex();
    int PreviousIndex();

private:
    Weapon *m_items[5];

    int m_index;
};

#endif /* INVENTORY_H */