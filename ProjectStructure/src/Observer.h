#ifndef OBSERVER_H
#define OBSERVER_H

/**
 * The Observer class provides an interface for objects that need to be notified of changes in
 * the subject they are observing.
 */
class Observer
{
public:
    /**
     * Virtual destructor to ensure proper cleanup of any derived classes.
     */
    virtual ~Observer() {}

    /**
     * Called by the subject to notify the observer of changes.
     */
    virtual void update() {}

    /**
     * Compares two observers to see if they are equal.
     * @param observer the observer to compare to.
     * @return true if the observers are the same, false otherwise.
     */
    bool operator==(const Observer* observer) const {
        return this == observer;
    }
};

#endif // OBSERVER_H

