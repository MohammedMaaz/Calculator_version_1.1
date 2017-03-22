#ifndef SCIENTIFIC_CALC_H
#define SCIENTIFIC_CALC_H

#include <SFML/Graphics.hpp>
#include <fstream>

void loadFile(const char* fileName, sf::Font& font)
{
    std::ifstream file;
    char* buffer=nullptr;

    file.open(fileName, std::ifstream::binary);

    file.seekg(0, file.end);
    unsigned int len = file.tellg();
    file.seekg(0, file.beg);
    buffer = new char [len];
    file.read(buffer,len);

    font.loadFromMemory(&buffer[0],len);

    file.close();
    //delete buffer;
}

void loadFile(const char* fileName, sf::SoundBuffer& buff)
{
    std::ifstream file;
    char* buffer=nullptr;

    file.open(fileName, std::ifstream::binary);

    file.seekg(0, file.end);
    unsigned int len = file.tellg();
    file.seekg(0, file.beg);
    buffer = new char [len];
    file.read(buffer,len);

    buff.loadFromMemory(&buffer[0],len);

    file.close();
    //delete buffer;
}

void loadFile(const char* fileName, sf::Texture& texture)
{
    std::ifstream file;
    char* buffer=nullptr;

    file.open(fileName, std::ifstream::binary);

    file.seekg(0, file.end);
    unsigned int len = file.tellg();
    file.seekg(0, file.beg);
    buffer = new char [len];
    file.read(buffer,len);

    texture.loadFromMemory(&buffer[0],len);

    file.close();
    //delete buffer;
}

/*

class Buffer
{
public:
    Buffer(const char* fileName)
    {
        file.open(fileName, std::ifstream::binary);
        buffer = new char [length()];
        file.read(buffer,length()); //constructor
    }

    Buffer(void)
    {
        //overloaded constructor
    }

    void updateFile(const char* fileName)
    {
        file.close();
        file.open(fileName, std::ifstream::binary);
        buffer = new char [length()];
        file.read(buffer,length());
    }

    unsigned int length()
    {
        file.seekg(0, file.end);
        unsigned int len = file.tellg();
        file.seekg(0, file.beg);
        return len;
        file.close();
    }

    char* memoryLoc()
    {
        return &buffer[0];
    }

    ~Buffer()
    {
        file.close(); //destructor
        delete buffer;
    }

private:
    std::ifstream file;
    char * buffer;

};

*/




#endif
