#ifndef RULES_H
#define RULES_H
#include"Enum.h"
#endif // RULES_H
#include <iostream>

using namespace block;

class Rules{

    Material subject;
    Material is;
    Material aspect;

public:
/**
* @brief Constructor for the Rules class.
* @param subject The material.
* @param is The material being compared to.
* @param aspect The aspect of the materials.
*/
Rules(Material subject, Material is, Material aspect);
/**
 * @brief Getter method for the subject material.
 * @return The subject material.
 */
Material getSubject();
/**
 * @brief Getter method for the aspect material.
 * @return The aspect material.
 */
Material getRuleAspect();

};
