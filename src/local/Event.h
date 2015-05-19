#ifndef LOCAL_EVENT_H
#define LOCAL_EVENT_H

#include <functional>
#include <map>
#include <vector>

/**
  * @ingroup base
  */
typedef uint64_t EventType;

#define INVALID_EVENT 0

/**
  * @ingroup base
  */
constexpr EventType Hash(const char *str, std::size_t sz) {
  return sz == 0 ? 0xcbf29ce484222325 : (str[0] ^ Hash(str + 1, sz - 1)) * 0x100000001b3;
}

/**
  * @ingroup base
  */
inline EventType Hash(const std::string& str) {
  return Hash(str.c_str(), str.size());
}


/**
  * @ingroup base
  */
struct Event {
  static const EventType type = INVALID_EVENT;
};

/**
  * @ingroup base
  */
enum class EventStatus {
  KEEP, /**< The handler must be kept */
  DIE,  /**< The handler can be removed */
};

/**
  * @ingroup base
  */
typedef std::function<EventStatus(EventType, Event *)> EventHandler;

/**
  * @ingroup base
  */
class EventManager {
public:

  void registerHandler(EventType type, EventHandler handler);

  template<typename E>
  void registerHandler(EventHandler handler) {
    static_assert(std::is_base_of<Event, E>::value, "E must be an Event");
    static_assert(E::type != INVALID_EVENT, "E must define its type");
    registerHandler(E::type, handler);
  }

  template<typename E, typename R, typename T>
  void registerHandler(R T::*pm, T *obj) {
    static_assert(std::is_base_of<Event, E>::value, "E must be an Event");
    static_assert(E::type != INVALID_EVENT, "E must define its type");
    registerHandler(E::type, std::bind(pm, obj, std::placeholders::_1, std::placeholders::_2));
  }

  void triggerEvent(EventType type, Event *event);

  template<typename E>
  void triggerEvent(E *event) {
    static_assert(std::is_base_of<Event, E>::value, "E must be an Event");
    static_assert(E::type != INVALID_EVENT, "E must define its type");
    triggerEvent(E::type, event);
  }

private:
  std::map<EventType, std::vector<EventHandler>> m_handlers;
};


constexpr EventType operator"" _type(const char *str, std::size_t sz) {
  return Hash(str, sz);
}

#endif // LOCAL_EVENT_H
