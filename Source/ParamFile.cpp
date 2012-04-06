#include "ParamFile.h"

void ParamFile::Init()
{
    m_file.open("params.cfg", std::ifstream::in);
    //Everything went good.
    if(m_file.fail())
    {
        std::cout << "Failed to load params.cfg." << std::endl;
        return;
    }

    m_windowWidth = GetParamAsInt();
    m_windowHeight = GetParamAsInt();

    m_zoneWidth = GetParamAsInt();
    m_zoneHeight = GetParamAsInt();

    m_playerSpeed = GetParamAsReal();
    m_enemySpeed = GetParamAsReal();

    m_file.close();
}

int ParamFile::GetParamAsInt()
{
    char equalChar;
    std::string param;
    int result = 0;
    m_file >> std::skipws >> param;
    m_file >> std::skipws >> equalChar;

    if(equalChar == '=')
    {
       m_file >> std::skipws >> result;
    }
    else
    {
        std::cout << "Bad syntax in params.cfg.\n";
    }

    return result;
}

bool ParamFile::GetParamAsBool()
{
    char equalChar;
    bool result = false;
    std::string param;
    m_file >> std::skipws >> param;
    m_file >> std::skipws >> equalChar;

    if(equalChar == '=')
    {
       m_file >> std::skipws >> result;
    }
    else
    {
        std::cout << "Bad syntax in params.cfg.\n";
    }

    return result;
}

Real ParamFile::GetParamAsReal()
{
    char equalChar;
    Real result = (Real)0.0;
    std::string param;
    m_file >> std::skipws >> param;
    m_file >> std::skipws >> equalChar;

    if(equalChar == '=')
    {
       m_file >> std::skipws >> result;
    }
    else
    {
        std::cout << "Bad syntax in params.cfg.\n";
    }

    return result;
}

void ParamFile::GetParamAsString(std::string &outPut)
{
    char equalChar;
    std::string param;
    m_file >> std::skipws >> param;
    m_file >> std::skipws >> equalChar;

    if(equalChar == '=')
    {
        m_file >> std::skipws >> outPut;
    }
    else
    {
        std::cout << "Bad syntax in params.cfg.\n";
    }
}