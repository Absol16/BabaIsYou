#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <vector>
#include <iostream>
#include "observer.h"

class Observable
{
   private:
       std::vector<Observer*> m_observers; // array of observer pointers

   public:
     /**
     * Notifies all observers that a change has occurred.
     */
     void notify()
    {
        unsigned int i = 0;
        for (i = 0; i < m_observers.size(); i++)
        {
            m_observers[i]->update();
        }
    }

     void notifyUi()
    {
        unsigned int i = 0;
        for (i = 0; i < m_observers.size(); i++)
        {
            m_observers[i]->updateUi();
        }
    }

    /**
     * Adds an observer to the list of observers.
     * @param obs The observer to be added.
     */
    void addObserver(Observer& obs)
    {
        m_observers.push_back(&obs);
    }

    /**
     * Removes an observer from the list of observers.
     * @param obs The observer to be removed.
     */
    void removeObserver(Observer &obs)
    {
        std::vector<Observer*> copy_tab = m_observers;
        m_observers.clear();
        unsigned int i = 0;

        for (i = 0; i < copy_tab.size(); i++)
        {
            if (copy_tab[i] != &obs)
            {
                m_observers.push_back(&obs);
            }
        }
    }
};

#endif // OBSERVABLE_H
