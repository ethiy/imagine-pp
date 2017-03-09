#ifndef IMAGINE_GRAPHICS_USERTHREAD_H
#define IMAGINE_GRAPHICS_USERTHREAD_H

#include <queue>
#include <QThread>
#include <QMutex>
#include <QEvent>
#include "Imagine/Graphics/Events.h"

namespace Imagine {
    
    class UserThread : public QThread
    {
        Q_OBJECT

    public:
        UserThread(QObject* parent = 0);
        void registerUserMain(int (*userMain)(int, char**), int new_argc, char** new_argv) { userMain_ = userMain; argc = new_argc; argv = new_argv; }

    public: /* timing methods */
        void milliSleep(int msec) { msleep(msec); }
        void microSleep(int usec) { usleep(usec); }

    public: /* I/O handling methods */
        int getMouse(int& x,int& y, Window& win,int& subWin, bool currentonly);
        int getKey(Window& win,int& subWin, bool currentonly);

        void getEvent(int ms, Event& ev);
        void unGetEvent(const Event& ev);
        void flushEvents();

        bool IsEvent() { return (theEventQueue.size()>0); }
        Event NextEvent() {
            Event e=theEventQueue.front(); theEventQueue.pop(); return e; }
        void PushEvent(const Event& e) { 
            if(theEventQueue.size()==theEventQueueMaxSize) theEventQueue.pop();
            theEventQueue.push(e);
        }

    public slots: /* I/O handling slot methods */
        void clicked(int x, int y, Qt::MouseButtons buttons, QEvent::Type type, Qt::KeyboardModifiers modifier, Window win, int subWin);
        void pressedKey(int key, QEvent::Type type, Qt::KeyboardModifiers modifier, Window win, int subWin);
        void pressedKey(int key, QEvent::Type type, Qt::KeyboardModifiers modifier) { pressedKey(key, type, modifier, 0, 0); }

    protected:
        void run();

    private:
        int (*userMain_)(int, char**);
        int argc;
        char** argv;

        QMutex mutex_;
        std::queue<Event> theEventQueue;
        static const unsigned int theEventQueueMaxSize=10000;
    };

} /* namespace Imagine */

#endif /* IMAGINE_GRAPHICS_USERTHREAD_H */
