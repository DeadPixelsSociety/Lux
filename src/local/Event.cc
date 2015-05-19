#include "Event.h"

#include <cassert>

void EventManager::registerHandler(EventType type, EventHandler handler) {
  assert(handler);
  auto it = m_handlers.find(type);

  if (it == m_handlers.end()) {
    bool inserted;
    std::tie(it, inserted) = m_handlers.insert(std::make_pair(type, std::vector<EventHandler>()));
    assert(inserted);
  }

  it->second.push_back(handler);
}

void EventManager::triggerEvent(EventType type, Event *event) {
  auto it = m_handlers.find(type);

  if (it == m_handlers.end()) {
    return;
  }

  std::vector<EventHandler> kept;

  for (auto handler : it->second) {
    if (handler(type, event) == EventStatus::KEEP) {
      kept.push_back(handler);
    }
  }

  std::swap(it->second, kept);
}

