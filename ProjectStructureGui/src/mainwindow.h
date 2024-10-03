#include <QMainWindow>
#include <QGraphicsProxyWidget>
#include <filesystem>
#include "qpushbutton.h"
#include "level.h"
#include "gamegrid.h"
#include <QtWidgets/QGraphicsScene.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Level *facade, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /**
     * @brief Slot for the left button click event.
     */
    void leftClicked();

    /**
     * @brief Slot for the right button click event.
     */
    void rightClicked();

    /**
     * @brief Slot for the up button click event.
     */
    void upClicked();

    /**
     * @brief Slot for the down button click event.
     */
    void downClicked();

    /**
     * @brief Slot for the restart button click event.
     */
    void restartClicked();

private:
    Ui::MainWindow* ui;
    Level* game;
    QGraphicsScene _scene; // the scene of the QGraphicsView
    GameGrid* gameGrid ;

    /**
     * @brief Handles the key press event.
     * @param event The key event (QKeyEvent).
     */
    void handleKeyPress(QKeyEvent* event);

    /**
     * @brief Filters events for the specified object.
     * @param object The object to filter events for (QObject).
     * @param event The event to filter (QEvent).
     * @return True if the event was filtered, false otherwise.
     */
    bool eventFilter(QObject* object, QEvent* event);

    /**
     * @brief Initializes the user interface.
     */
    void initUI();

    /**
     * @brief Hides the buttons.
     */
    void hideButton();

    /**
     * @brief Applies a button style with a specified background color.
     * @param button The button to apply the style to (QPushButton).
     * @param backgroundColor The background color for the button (QString).
     */
    void applyButtonStyle(QPushButton* button, const QString& backgroundColor);

    /**
     * @brief Connects all the slots.
     */
    void connectAllSlot();

    /**
     * @brief Hides the menu.
     */
    void hideMenu();

};
