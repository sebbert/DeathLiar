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
* Copyright � 2012 Emil Sandst�, Sebastian Reinhard
* 
*/
#ifndef PARAM_FILE_H_
#define PARAM_FILE_H_

#include <iostream>
#include <fstream>
#include <string>
#include "MathUtil.h"

class ParamFile
{
public:
    void Init();

    Real m_playerSpeed;
    Real m_enemySpeed;

    int m_windowWidth;
    int m_windowHeight;

    int m_zoneWidth;
    int m_zoneHeight;
private:
    int GetParamAsInt();
    bool GetParamAsBool();
    Real GetParamAsReal();

    void GetParamAsString(std::string &output);

    std::ifstream m_file;
};

#endif