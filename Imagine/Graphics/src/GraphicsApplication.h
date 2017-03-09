#ifndef IMAGINE_GRAPHICS_GRAPHICSAPPLICATION_H
#define IMAGINE_GRAPHICS_GRAPHICSAPPLICATION_H

#include <QApplication>
#include <QMutex>
#include <QList>

#include "UserThread.h"

namespace Imagine {

    class GraphicsApplication : public QApplication
    {
        Q_OBJECT

    public:
        GraphicsApplication(int& argc, char **argv);

    public slots:
        void createWindow(int w, int h,
                          const QList<QString>& tabsNames,
                          const QList<WindowType>& tabsTypes,
                          const QString& name="Imagine++",
                          int x=-1, int y=-1);
        void setActiveWindow(Window w, int subWin=0);
        void showWindow(Window w, int subWin=0);
        void closeWindow(Window w);

        void createBitmap(int w, int h);
        void deleteBitmap(QPixmap* pm);
        void drawBitmap(QPixmap* pm, int x,int y, const QImage& image);
        void display(QPixmap* pm, int x,int y, bool xorMode, double fact);

    public: /* connection to listen to keyboard and mouse events. */
        void connectWindowIOEventsToUserThread(QWidget* w);

    public:
        QPixmap* createdPixmap; /* Last created pixmap */
        UserThread userThread;
        QList<Window> createdWindows;
        Window activeWindow;

        QMutex mutex;
    };
} /* namespace Imagine */

#endif /* IMAGINE_GRAPHICS_GRAPHICSAPPLICATION_H */
