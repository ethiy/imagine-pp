#include "UserThread.h"
#include "GraphicsUtilities.h"
#include <QtGui>

namespace Imagine {
    UserThread::UserThread(QObject* parent)
    : QThread(parent)
    , userMain_(0)
    {}

    static const int theEventDelay=15; // Milliseconds

    int UserThread::getMouse(int& x,int& y, Window& win,int& subWin,
                             bool currentonly)
    {
        bool ok=false;
        Event ev;
        Window target = guiApp()->activeWindow;
        while (true) {
            mutex_.lock();
            while( IsEvent() ) {
                ev = NextEvent();
                if(ev.type==EVT_BUT_ON &&
                   (!currentonly ||
                    (ev.win==target && ev.subWin==target->activeWin))) {
                    ok=true;
                    break;
                }
            }
            mutex_.unlock();
            if(ok)
                break;
            milliSleep(theEventDelay);
        }
        x = ev.pix.x();
        y = ev.pix.y();
        win = ev.win;
        subWin = ev.subWin;
        return ev.button;
    }

    // Fix various key codes, some platform specific
    static void fixKey(Event& e) {
        // Put lowercase letter if shift key is not pressed
        if(e.state==EVS_NONE && 'A'<=e.key && e.key<='Z')
            e.key = 'a' + (e.key-'A');
        // Keypad Enter -> return
        if(e.key==Qt::Key_Enter)
            e.key = KEY_RETURN;
#if __APPLE__ && __MACH__
        if(e.key==Qt::Key_Meta)
            e.key = KEY_CONTROL;
        else if(e.key==Qt::Key_Control)
            e.key = KEY_CMD;
#else
        if(e.key==Qt::Key_Meta)
            e.key = KEY_CMD;
#endif
    }

    int UserThread::getKey(Window& win,int& subWin,bool currentonly)
    {
        bool ok=false;
        Event ev;
        Window target = guiApp()->activeWindow;
        while (true) {
            mutex_.lock();
            while( IsEvent() ) {
                ev = NextEvent();
                if(ev.type==EVT_KEY_ON &&
                   (!currentonly ||
                    (ev.win==target && ev.subWin==target->activeWin))) {
                    ok=true;
                    break;
                }
            }
            mutex_.unlock();
            if(ok)
                break;
            milliSleep(theEventDelay);
        }
        win=ev.win;
        subWin=ev.subWin;
        fixKey(ev);
        return ev.key;
    }

    void UserThread::getEvent(int ms, Event& ev)
    {
        int time=0;
        ev.type=EVT_NONE;
        while(true) {
            mutex_.lock();
            if( IsEvent() ) {
                ev = NextEvent();
                mutex_.unlock();
                break;
            }
            mutex_.unlock();
            if(ms==0)
                break;
            milliSleep(theEventDelay);
            time += theEventDelay;
            if(ms!=-1 && time>ms)
                break;
        }
        if(ev.type==EVT_KEY_ON || ev.type==EVT_KEY_OFF)
            fixKey(ev);
    }

    void UserThread::unGetEvent(const Event& ev)
    {
        mutex_.lock();
        PushEvent(ev);
        mutex_.unlock();
    }

    void UserThread::flushEvents()
    {
        std::queue<Event> Q;
        mutex_.lock();
        theEventQueue = Q;
        mutex_.unlock();
    }

    // Convert from Qt to Imagine type
    EventState getState(Qt::KeyboardModifiers modifier) {
        EventState state=EVS_NONE;
        if(modifier & Qt::ShiftModifier)
            state = EventState(state + EVS_SHIFT);
        if(modifier & Qt::ControlModifier)
            state = EventState(state + EVS_CONTROL);
        if(modifier & Qt::AltModifier)
            state = EventState(state + EVS_ALT);
        return state;
    }

    void UserThread::clicked(int x, int y, Qt::MouseButtons buttons,
                             QEvent::Type type, Qt::KeyboardModifiers modifier,
                             Window win, int subWin)
    {
        Event ev;
        int tmp = static_cast<int>(type);
        ev.type = static_cast<EventType>(tmp);
        ev.pix.x() = x;
        ev.pix.y() = y;
        ev.button = 0;
        if(buttons == Qt::LeftButton)
            ev.button = 1;
#if QT_VERSION < 0x040700
        else if(buttons == Qt::MidButton)
#else
        else if(buttons == Qt::MiddleButton)
#endif
            ev.button = 2;
        else if(buttons == Qt::RightButton)
            ev.button = 3;
        ev.key = 0;
        ev.state = getState(modifier);
        ev.win = win;
        ev.subWin = subWin;
        
        mutex_.lock();
        PushEvent(ev);
        mutex_.unlock();
    }

    void UserThread::pressedKey(int key, QEvent::Type type,
                                Qt::KeyboardModifiers modifier,
                                Window win, int subWin)
    {
        Event ev;
        int tmp = static_cast<int>(type);
        ev.type = static_cast<EventType>(tmp);
        ev.pix.x() = ev.pix.y() = -1;
        ev.button = -1;
        ev.key = key;
        ev.state = getState(modifier);
        ev.win = win;
        ev.subWin = subWin;

        mutex_.lock();
        PushEvent(ev);
        mutex_.unlock();
    }

    void UserThread::run()
    {
        if (!userMain_)
        {
            qFatal("No registered user main!");
            return;
        }
        userMain_(argc, argv);
        return;
    }
} /* namespace Imagine */
