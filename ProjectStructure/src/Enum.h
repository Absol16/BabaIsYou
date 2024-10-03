#ifndef ENUM_H
#define ENUM_H
#include <string>
#include <iostream>

using namespace std;

namespace Enum {
    /**
     * @brief The Material enum an enumeration of all the different materials that can appear in the game
     */
    enum class Material {
        METAL,
        GRASS,
        WALL,
        NOTHING,
        FLAG,
        ROCK,
        LAVA,
        BABA,
        WATER, //8 -> everything below 8 is a state
        // ------- subject text rules
        ASPECT_BABA,
        ASPECT_WALL,
        ASPECT_ROCK,
        ASPECT_WATER,
        ASPECT_FLAG,
        ASPECT_LAVA,
        //14
        ASPECT_IS,
        //15
        // ------- aspect text rules
        ASPECT_YOU,
        ASPECT_STOP,
        ASPECT_SINK,
        ASPECT_PUSH,
        ASPECT_KILL,
        ASPECT_WIN,
        ASPECT_BEST
        //22
    };
    /**
     * @brief The Aspect enum an enumeration of all the different aspects that can be applied to materials.
     */
    enum class Aspect {
        YOU,
        PUSH,
        STOP,
        KILL,
        SINK,
        WIN,
        NONE,
        BEST
    };

    /**
     * @brief The Direction enum an enumeration of the four cardinal directions.
     */
    enum class Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    class MaterialUtils {
    public:
        /**
        * @brief materialToInt this method takes a Material type and returns an integer representation of it.
        * @param mat the material
        * @return int
        */
       static int materialToInt(Material mat) {
           return static_cast<int>(mat);
       }
       /**
        * @brief materialToAspect this method takes a Material type and returns the corresponding Aspect type based on a switch statement.
        * @param mat
        * @return
        */
       static Aspect materialToAspect(Material mat) {
           switch(mat){
           case Material::ASPECT_YOU:
               return Aspect::YOU;
               break;
           case Material::ASPECT_STOP:
               return Aspect::STOP;
               break;
           case Material::ASPECT_SINK:
               return Aspect::SINK;
               break;
           case Material::ASPECT_BEST:
               return Aspect::BEST;
               break;
           case Material::ASPECT_PUSH:
               return Aspect::PUSH;
               break;
           case Material::ASPECT_KILL:
               return Aspect::KILL;
               break;
           case Material::ASPECT_WIN:
               return Aspect::WIN;
               break;
           default:
               return Aspect::NONE;
           }
       }
       /**
        * @brief materialToState this method takes a Material type and returns a Material type that represents a state based on a switch statement.
        * @param mat
        * @return
        */
       static Material materialToState(Material mat) {
           switch(mat){
           case Material::ASPECT_BABA:
               return Material::BABA;
               break;
           case Material::ASPECT_WALL:
               return Material::WALL;
               break;
           case Material::ASPECT_ROCK:
               return Material::ROCK;
               break;
           case Material::ASPECT_FLAG:
               return Material::FLAG;
               break;
           case Material::ASPECT_LAVA:
               return Material::LAVA;
               break;
           case Material::ASPECT_WATER:
               return Material::WATER;
               break;
           default:
               return Material::NOTHING;
           }
       }
       /**
        * @brief materialToString This method takes a Material type and returns a string representation of it.
        * @param material
        * @return
        */
       static std::string materialToString(Material material){
           switch(material) {
           case Material::BABA:
               return "Baba";
           case Material::WALL:
               return "Wall";
           case Material::LAVA:
               return "Lava";
           case Material::FLAG:
               return "Flag";
           case Material::METAL:
               return "Metal";
           case Material::ROCK:
               return "Rock";
           case Material::NOTHING:
               return "Nothing";
           case Material::GRASS:
               return "Grass";
           case Material::WATER:
               return "water";
           case Material::ASPECT_BABA:
               return "Aspect_Baba";
           case Material::ASPECT_WALL:
               return "Aspect_Wall";
           case Material::ASPECT_LAVA:
               return "Aspect_Lava";
           case Material::ASPECT_FLAG:
               return "Aspect_Flag";
           case Material::ASPECT_ROCK:
               return "Aspect_Rock";
           case Material::ASPECT_WATER:
               return "Aspect_Water";
           case Material::ASPECT_IS:
               return "Aspect_Is";
           case Material::ASPECT_SINK:
               return "Aspect_Sink";
           case Material::ASPECT_STOP:
               return "Aspect_Stop";
           case Material::ASPECT_WIN:
               return "Aspect_Win";
           case Material::ASPECT_YOU:
               return "Aspect_You";
           case Material::ASPECT_KILL:
               return "Aspect_Kill";
           case Material::ASPECT_PUSH:
               return "Aspect_Push";
               default:
                   return "Unknown material";
           }
       }
       /**
        * @brief aspectToString this method takes an Aspect type and returns a string representation of it based on a switch statement.
        * @param aspect
        * @return
        */
       static std::string aspectToString(Aspect aspect){
           switch(aspect) {
           case Aspect::YOU:
               return "You";
           case Aspect::PUSH:
               return "Push";
           case Aspect::STOP:
               return "Stop";
           case Aspect::KILL:
               return "Kill";
           case Aspect::BEST:
               return "Best";
           case Aspect::SINK:
               return "Sink";
           case Aspect::WIN:
               return "Win";
           case Aspect::NONE:
               return "None";
               default:
                   return "Unknown aspect";
           }
       }
    };
}
#endif // ENUM_H
