#include "fileLoader.h"

Material getMaterialType(std::string materialStr) {
    if (materialStr == "baba") {
        return Material::BABA;
    } else if (materialStr == "wall") {
        return Material::WALL;
    } else if (materialStr == "lava") {
        return Material::LAVA;
    } else if (materialStr == "flag") {
        return Material::FLAG;
    } else if (materialStr == "metal") {
        return Material::METAL;
    } else if (materialStr == "rock") {
        return Material::ROCK;
    } else if (materialStr == "nothing") {
        return Material::NOTHING;
    } else if (materialStr == "grass") {
        return Material::GRASS;
    } else if (materialStr == "water") {
        return Material::WATER;
    } else if (materialStr == "text_baba") {
        return Material::ASPECT_BABA;
    } else if (materialStr == "text_wall") {
        return Material::ASPECT_WALL;
    } else if (materialStr == "text_best") {
        return Material::ASPECT_BEST;
    } else if (materialStr == "text_rock") {
        return Material::ASPECT_ROCK;
    } else if (materialStr == "text_flag") {
        return Material::ASPECT_FLAG;
    } else if (materialStr == "text_lava") {
        return Material::ASPECT_LAVA;
    } else if (materialStr == "text_water") {
        return Material::ASPECT_WATER;
    } else if (materialStr == "is") {
        return Material::ASPECT_IS;
    } else if (materialStr == "you") {
        return Material::ASPECT_YOU;
    } else if (materialStr == "stop") {
        return Material::ASPECT_STOP;
    } else if (materialStr == "sink") {
        return Material::ASPECT_SINK;
    } else if (materialStr == "push") {
        return Material::ASPECT_PUSH;
    } else if (materialStr == "kill") {
        return Material::ASPECT_KILL;
    } else if (materialStr == "win") {
        return Material::ASPECT_WIN;
    } else {
        return Material::NOTHING;
    }
}

string materialToText(Material m) {
    if (m == Material::BABA) {
        return "baba";
    } else if (m == Material::WALL) {
        return "wall";
    } else if (m == Material::LAVA) {
        return "lava";
    } else if (m == Material::FLAG) {
        return "flag";
    } else if (m == Material::METAL) {
        return "metal";
    } else if (m == Material::ROCK) {
        return "rock";
    } else if (m == Material::NOTHING) {
        return "nothing";
    } else if (m == Material::GRASS) {
        return "grass";
    } else if (m == Material::WATER) {
        return "water";
    } else if (m == Material::ASPECT_BABA) {
        return "text_baba";
    } else if (m == Material::ASPECT_WALL) {
        return "text_wall";
    } else if (m == Material::ASPECT_BEST) {
        return "text_best";
    } else if (m == Material::ASPECT_ROCK) {
        return "text_rock";
    } else if (m == Material::ASPECT_FLAG) {
        return "text_flag";
    } else if (m == Material::ASPECT_LAVA) {
        return "text_lava";
    } else if (m == Material::ASPECT_WATER) {
        return "text_water";
    } else if (m == Material::ASPECT_IS) {
        return "is";
    } else if (m == Material::ASPECT_YOU) {
        return "you";
    } else if (m == Material::ASPECT_STOP) {
        return "stop";
    } else if (m == Material::ASPECT_SINK) {
        return "sink";
    } else if (m == Material::ASPECT_PUSH) {
        return "push";
    } else if (m == Material::ASPECT_KILL) {
        return "kill";
    } else if (m == Material::ASPECT_WIN) {
        return "win";
    } else
        return "unknown";
}

std::vector<ObjectGame> FileLoader::loadFile(int level, bool isSave) {
    // Construction du nom de fichier pour le niveau donné
    std::string filename;
    // std::filesystem::path working_directory { std::filesystem::current_path() };
    if (!isSave){

        filename = "../../ProjectStructureGui/src/level_" + std::to_string(level) + ".txt";

    }else filename = "../../ProjectStructure/src/save.txt";

    // Ouverture du fichier en lecture
    std::ifstream file(filename);

    // Vérification de l'ouverture du fichier
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier " + filename);
    }
    // Lecture du fichier ligne par ligne
    std::vector<ObjectGame> objectList;
    std::string line;
    while (std::getline(file, line)) {
        // Traitement de chaque ligne
        std::istringstream iss(line);
        std::string material;
        int x, y;
        if (iss >> material >> x >> y) {
            Aspect aspect = Aspect::NONE;
            if (material.substr(0, 4) == "text" || material == "is" || material == "win" || material == "you" || material == "push" || material == "stop" || material == "kill" || material == "sink"  ){
                aspect = Aspect::PUSH;
            }
            objectList.emplace_back(Position(x, y), getMaterialType(material), aspect);
        }
    }

    file.close();

    // Retour de la liste d'objets
    return objectList;
}

void FileLoader::writeToFile(vector<vector<vector<ObjectGame>>> tabBoard) {
    std::string filename = "../../ProjectStructureGui/src/save.txt";
    ofstream outfile(filename);

    if(outfile.is_open()) {
        for(int x = 0; x < tabBoard.size(); x++) {
            for(int y = 0; y < tabBoard[x].size(); y++) {
                for(ObjectGame& o :tabBoard[y][x]) {
                    if(o.getTypeObject() != Material::NOTHING){
                        outfile <<materialToText(o.getTypeObject()) << " " << y << " " << x << endl;
                    }
                }
            }
        }

        outfile.close();
    }
    else {
        cerr << "Error: cannot write to file " << filename << endl;
    }
}


