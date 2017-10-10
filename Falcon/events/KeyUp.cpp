#include "KeyUp.hpp"
#include "EventHandler.hpp"

namespace Falcon::Events
{

KeyUp::KeyUp (const SDL_Event & event)
: KeyEvent (EventType::KeyUp, Key (event.key.keysym.sym))
{

}

void KeyUp::accept (EventHandler & handler) const
{
  handler.handleKeyUp (*this);
}

} // namespace Falcon::Events