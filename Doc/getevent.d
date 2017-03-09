/*! \page getEventPage How to use GetEvent

    Keyboard and mouse events are handled by the structure \c Event.

  \section ge1 I. What is inside a structure Event?
  
  Here is the structure defining Event:
  \dontinclude Graphics/src/Imagine/Graphics/Events.h
  \skipline All the info
  \until ...
	\subsection ge11 1. Types
    The \c type variable indicates the nature of the event. There are 6 types of events:
    \dontinclude Graphics/src/Imagine/Graphics/Events.h
    \skipline - EVT_NONE
    \line EVT_BUT_ON
    \line EVT_BUT_OFF
    \line EVT_MOTION
    \line EVT_KEY_ON
    \line EVT_KEY_OFF
    \until };
    - Button events indicate whether a mouse button was pressed or released (in which case the \c pix field indicates the mouse position and \c button the button number, 1 for left, 2 for middle and 3 for right);
    - the motion type indicates a mouse motion (the \c pix field indicates the new mouse position);
    - key events indicate whether a keyboard key was pressed or released.
    - The \c EVT_NONE type indicates a non-event, that is, nothing happened.

	\subsection ge12 2. Mouse Tracking
    By default, mouse motion events are only registered while a mouse button is kept pressed (mouse drag). If you want to be notified of mouse motion events even when no button is pressed, use
		\code
		enableMouseTracking(true);
		\endcode
		To deactivate, use
		\code
		enableMouseTracking(false);
		\endcode
	\section ge2 II. How to handle events
    There is an event queue that registers all events. Each time a new event occurs, it is appended in the queue, independently of the user's code running.
    	
	\image html newEvent.png "New event registered in the event queue"
	
	\subsection ge21 1. GetEvent
    To extract the first event of the queue (the least recent one), you call the \c getEvent function, which fills its second argument.
	
	\image html getEvent.png "When calling getEvent, the structure \c Event contains the information \"Key A pressed\", which is extracted from the queue."
	
	\code
	// Get event.
    // Gets next event in the queue. Wait for (approx) ms milliseconds before timeout.
    // param ms Number of milliseconds before timeout. If ms==-1, waits until an event.
    // param ev The event. If timeout, ev.type is EVT_NONE
	
    void getEvent(int ms, Event &ev);
	\endcode
	
	The parameters of getEvent are:
		- ms: The time (int milliseconds) to wait to have a chance of registering a new event. A value of -1 implies that we wait indefinitely until the queue is not empty.
		- ev: the filled-out structure.
	
    When the queue is empty, \c ev gets type \c EVT_NONE to indicate that.
	
	\subsection ge22 2. unGetEvent
	
    It is possible to append manually a user created event with the function \c unGetEvent.
	
	\code 
	// Unget event.
    // Push back event at end of queue.
    // param: ev The event.
    void unGetEvent(const Event &ev);
	\endcode
	
	\subsection ge23 3. flushEvents
    You can decide to discard all waiting events and make the queue empty with this function.	
	
	\section ge3 III. Examples
	\subsection ge31 1. Graphical buttons
    To have a nice effect, it is good to have mouse tracking enabled to provide the user with some feedback. Use \c enableMouseTracking(true) for that.
    The code studies the mouse cursor position and determines if it is inside a "button".
		
		\dontinclude Graphics/test/test.cpp \skip events2()
		\skipline Menu
		\until ...
		\image html getEvent.gif "A game's menu"
		
	\subsection ge32 2. Moving a ball with the keyboard
    We examine the value of \c ev.key to know the pressed key. Printable characters are identified by their ASCII code (for example 'A', '0', '?'). Non-printable keys are identified by a specific code in this list:
		
		\code
		// Keyboard codes.
		// Codes assigned to most non alpha-numeric keys.
		// (alpha-numeric keys are represented by their ASCII code: 'A', '0'...)
    enum KeyCode {
        KEY_BACK=16777219,KEY_TAB=16777217,KEY_RETURN=16777220,
        KEY_ESCAPE=16777216,KEY_SPACE=32,KEY_DELETE=16777223,KEY_START=16777250,
        KEY_SHIFT=16777248,KEY_ALT=16777251,KEY_CONTROL=16777249,
        KEY_MENU=16777301,KEY_PAUSE=16777224,KEY_CAPITAL=16777252,
        KEY_END=16777233,KEY_HOME=16777232,
        KEY_LEFT=16777234,KEY_UP=16777235,KEY_RIGHT=16777236,KEY_DOWN=16777237,
        KEY_INSERT=16777222,
        KEY_NUMPAD0=48, KEY_NUMPAD1, KEY_NUMPAD2, KEY_NUMPAD3, KEY_NUMPAD4,
        KEY_NUMPAD5, KEY_NUMPAD6, KEY_NUMPAD7, KEY_NUMPAD8, KEY_NUMPAD9,
        KEY_MULTIPLY=42,KEY_ADD,KEY_SEPARATOR,KEY_SUBTRACT,KEY_DECIMAL,
        KEY_DIVIDE,
        KEY_F1=16777264, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8,
        KEY_F9, KEY_F10, KEY_F11, KEY_F12,
        KEY_NUMLOCK=16777253, KEY_SCROLL=16777254, KEY_PAGEUP=16777238,
        KEY_PAGEDOWN, KEY_NUMPAD_ENTER=16777221
    };
		\endcode
        To have a readable source code, you must never use the actual numeric values in this list, but only their code.

		\dontinclude Graphics/test/test.cpp \skip events2()
		\skipline Ball
		\until ...
	\image html testEvent.gif "A keyboard controlled ball"

	\subsection ge33 3. Keyboard auto-repeat
    When a key, other than <tt>Shift</tt>, <tt>Ctrl</tt>, or <tt>Alt</tt>, is maintained pressed longer than some minimal time (tunable by the system), auto-repeatition occurs. In that case, the sequence of events is the following:
    - EVT_KEY_ON
    - EVT_KEY_ON
    - ...
    - EVT_KEY_OFF

    That is, it behaves as if the key was pressed multiple times, but only the final key release event is registered.
*/
