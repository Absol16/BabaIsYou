#include <catch2/catch_test_macros.hpp>
#include "../src/board.h"

TEST_CASE("Test Board methods") {
    Board board;
    ObjectGame obj;



    SECTION("setTabGame") {
        std::vector<ObjectGame> element;
        Position pos(0, 0);
        board.setTabGame(element, pos);
        REQUIRE(std::equal(board.getTabBoard()[0][0].begin(), board.getTabBoard()[0][0].end(), element.begin(), element.end()));
    }

    SECTION("isInside") {
        Position pos(-1, -1);
        REQUIRE_FALSE(board.isInside(pos));

        pos = Position(0, 0);
        REQUIRE(board.isInside(pos));

        pos = Position(17, 17);
        REQUIRE(board.isInside(pos));

        pos = Position(18, 18);
        REQUIRE_FALSE(board.isInside(pos));
    }

    SECTION("Test gameIsWin") {

        Position p(0,0);
        obj.setTypeObject(Material::FLAG);
        obj.setAspectObject(Aspect::WIN);
        obj.setCoordonnee(p);
        Rules ruleYou(Material::ASPECT_BABA,Material::ASPECT_IS,Material::ASPECT_YOU);
        Rules ruleWin(Material::ASPECT_FLAG,Material::ASPECT_IS,Material::ASPECT_WIN);
        vector<Rules> listRule;
        listRule.push_back(ruleYou);
        listRule.push_back(ruleWin);
        board.setRule(listRule);
        ObjectGame objectYou(p,Material::BABA,Aspect::YOU);
        std::vector<ObjectGame> listObj;
        listObj.push_back(obj);
        listObj.push_back(objectYou);
        board.setTabGame(listObj, p);
        board.checkBuildRule();
        REQUIRE(board.gameIsWin());
    }

    SECTION("clearRule") {
        std::vector<Rules> rules;
        Rules rule1(Material::ASPECT_WALL,Material::ASPECT_IS,Material::ASPECT_STOP);
        Rules rule2(Material::ASPECT_ROCK,Material::ASPECT_IS,Material::ASPECT_PUSH);
        rules.push_back(rule1);
        rules.push_back(rule2);

        board.setRule(rules);
        board.clearRule();
        REQUIRE(board.getRule().empty());
    }


    SECTION("checkBuildRule() for ROCK"){
        std::vector<Rules> rules;
        vector<ObjectGame> listObj;
        Position pos=Position(0,0);

        Rules rule(Material::ASPECT_ROCK,Material::ASPECT_IS,Material::ASPECT_PUSH);

        ObjectGame rock2(Position(3, 3), Material::ROCK ,Aspect::NONE);

        listObj.push_back(rock2);


        rules.push_back(rule);

        board.setRule(rules);


        board.setTabGame(listObj,pos);

        board.checkBuildRule();

        REQUIRE(board.getTabBoard()[pos.getX()][pos.getY()][0].getAspectObject()==Aspect::PUSH);
    }



    SECTION("checkBuildRule() for WALL"){
        std::vector<Rules> rules;
        vector<ObjectGame> listObj;
        Position pos=Position(0,0);

        Rules rule(Material::ASPECT_WALL,Material::ASPECT_IS,Material::ASPECT_STOP);

        ObjectGame wall(Position(3, 3), Material::WALL ,Aspect::NONE);

        listObj.push_back(wall);


        rules.push_back(rule);

        board.setRule(rules);


        board.setTabGame(listObj,pos);

        board.checkBuildRule();

        REQUIRE(board.getTabBoard()[pos.getX()][pos.getY()][0].getAspectObject()==Aspect::STOP);
    }

    SECTION("checkBuildRule() for BABA"){
        std::vector<Rules> rules;
        vector<ObjectGame> listObj;
        Position pos=Position(0,0);

        Rules rule(Material::ASPECT_BABA,Material::ASPECT_IS,Material::ASPECT_YOU);

        ObjectGame baba(Position(3, 3), Material::BABA ,Aspect::NONE);

        listObj.push_back(baba);


        rules.push_back(rule);

        board.setRule(rules);


        board.setTabGame(listObj,pos);

        board.checkBuildRule();

        REQUIRE(board.getTabBoard()[pos.getX()][pos.getY()][0].getAspectObject()==Aspect::YOU);
    }


    SECTION("move"){
        vector<ObjectGame*> listObj;
        Position pos;
        Rules ruleYou(Material::ASPECT_BABA,Material::ASPECT_IS,Material::ASPECT_YOU);

        ObjectGame you(Position(2,3), Material::BABA ,Aspect::YOU);
        ObjectGame rock1(Position(1, 3), Material::ROCK ,Aspect::PUSH);
        ObjectGame rock2(Position(3, 3), Material::ROCK ,Aspect::PUSH);
        ObjectGame wall1(Position(1,2), Material::WALL ,Aspect::STOP);
        ObjectGame wall2(Position(3,2), Material::WALL ,Aspect::STOP);
        ObjectGame sink1(Position(1,1), Material::WATER ,Aspect::SINK);
        ObjectGame sink2(Position(3,1), Material::WATER ,Aspect::SINK);
        ObjectGame nothing1(Position(2,2), Material::NOTHING,Aspect::NONE);
        ObjectGame nothing2(Position(2,4), Material::NOTHING,Aspect::NONE);
        ObjectGame nothing3(Position(1,3), Material::NOTHING,Aspect::NONE);
        ObjectGame nothing4(Position(3,3), Material::NOTHING,Aspect::NONE);

        listObj.push_back(&you);
        listObj.push_back(&rock1);
        listObj.push_back(&rock2);
        listObj.push_back(&wall1);
        listObj.push_back(&wall2);
        listObj.push_back(&sink1);
        listObj.push_back(&sink2);
        listObj.push_back(&nothing1);
        listObj.push_back(&nothing2);

        listObj.push_back(&nothing3);
        listObj.push_back(&nothing4);

        for (auto &o : listObj) {
            vector<ObjectGame> list;
            list.push_back(*o);
            pos = o->getCoordonnee();
            board.setTabGame(list,pos);
        }
        vector<Rules> listRule;
        listRule.push_back(ruleYou);
        board.setRule(listRule);

        board.checkBuildRule();
        vector<ObjectGame*> objectYou = board.testObjectYou(board);

        // Test moving in all directions
        board.move(Direction::UP);
        REQUIRE(objectYou[0]->getCoordonnee().getX() == 2);
        REQUIRE(objectYou[0]->getCoordonnee().getY() == 2);

        board.checkBuildRule();
        board.move(Direction::DOWN);
        REQUIRE(objectYou[0]->getCoordonnee().getX() == 2);
        REQUIRE(objectYou[0]->getCoordonnee().getY() == 3);

        board.checkBuildRule();
        board.move(Direction::LEFT);
        REQUIRE(objectYou[0]->getCoordonnee().getX() == 1);
        REQUIRE(objectYou[0]->getCoordonnee().getY() == 3);

        board.checkBuildRule();
        board.move(Direction::RIGHT);
        REQUIRE(objectYou[0]->getCoordonnee().getX() == 2);
        REQUIRE(objectYou[0]->getCoordonnee().getY() == 3);

        board.checkBuildRule();
        // Test pushing a rock
        board.move(Direction::LEFT);
        REQUIRE(objectYou[0]->getCoordonnee().getX() == 1);
        REQUIRE(objectYou[0]->getCoordonnee().getY() == 3);

        board.checkBuildRule();
        // Test pushing two rocks
        board.move(Direction::LEFT);
        REQUIRE(rock1.getCoordonnee().getX() == 1);
        REQUIRE(objectYou[0]->getCoordonnee().getY() == 3);
        REQUIRE(rock2.getCoordonnee().getX() == 3);
        REQUIRE(objectYou[0]->getCoordonnee().getY() == 3);

        board.checkBuildRule();
        // Test stopping at a wall
        board.move(Direction::LEFT);
        REQUIRE(objectYou[0]->getCoordonnee().getX() == 1);
        REQUIRE(objectYou[0]->getCoordonnee().getY() == 3);

        board.checkBuildRule();
        // Test sinking in water
        board.move(Direction::UP);
        REQUIRE(objectYou[0]->getCoordonnee().getX() == 1);
        REQUIRE(objectYou[0]->getCoordonnee().getY() == 3);
        REQUIRE(board.gameIsLoose());

        // Test losing by being killed
        ObjectGame you2(Position(2,2), Material::BABA, Aspect::YOU);
        ObjectGame kill1(Position(2,1), Material::LAVA, Aspect::KILL);
        listObj.clear();
        listObj.push_back(&you2);
        listObj.push_back(&kill1);
        for (auto& o : listObj) {
            vector<ObjectGame> list;
            list.push_back(*o);
            Position pos = o->getCoordonnee();
            board.setTabGame(list,pos);
        }

        board.checkBuildRule();
        REQUIRE(!board.gameIsLoose());

    }
}
