#ifndef NPC_H
#define NPC_H

#include <string>
#include <fstream>
#include "Image.h"

class NPC: public Game_Object
{
public:
    NPC(const char * npc_filename)
    {
        std::string image_file;
        std::ifstream npc_file;
        npc_file.open(npc_filename);
        std::getline(npc_file, image_file);
        image.load(image_file);
        std::getline(npc_file, dialogue);
    }


    void talk()
    {
        std::cout << "npc: " << dialogue << std::endl;
    }

    void draw()
    {
        int x;
    }


private:
    std::string dialogue;
    Image image;
};

#endif
