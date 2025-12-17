#include "user.h"

/**
 * Creates a new User with the given name and no friends.
 */
User::User(const std::string &name)
    : _name(name), _friends(nullptr), _size(0), _capacity(0) {}

/**
 * Adds a friend to this User's list of friends.
 * @param name The name of the friend to add.
 */
void User::add_friend(const std::string &name) {
  if (_size == _capacity) {
    _capacity = 2 * _capacity + 1;
    std::string *newFriends = new std::string[_capacity];
    for (size_t i = 0; i < _size; ++i) {
      newFriends[i] = _friends[i];
    }
    delete[] _friends;
    _friends = newFriends;
  }

  _friends[_size++] = name;
}

/**
 * Returns the name of this User.
 */
std::string User::get_name() const { return _name; }

/**
 * Returns the number of friends this User has.
 */
size_t User::size() const { return _size; }

/**
 * Sets the friend at the given index to the given name.
 * @param index The index of the friend to set.
 * @param name The name to set the friend to.
 */
void User::set_friend(size_t index, const std::string &name) {
  _friends[index] = name;
}

/**
 * STUDENT TODO:
 * The definitions for your custom operators and special member functions will
 * go here!
 */

User::User(const User &user) {
  _name = user._name;
  _capacity = user._capacity;
  _size = user._size;
  if (_capacity > 0) {
    _friends = new std::string[_capacity];
    for (size_t i = 0; i < _size; i++) {
      _friends[i] = user._friends[i];
    }
  } else {
    _friends = nullptr;
  }
}

User &User::operator=(const User &user) {
  if (this != &user) {
    User temp(user);
    temp.swap(*this);
  }
  return *this;
}

User::~User() { delete[] _friends; }

std::ostream &operator<<(std::ostream &os, const User &user) {
  os << "User(name=" << user._name << ", friends=[";
  if (user._size > 0) {
    os << user._friends[0];
  }
  for (size_t i = 1; i < user._size; i++) {
    os << ", " << user._friends[i];
  }
  os << "])";
  return os;
}

User &User::operator+=(User &user) {
  if (this == &user) {
    return *this;
  }

  this->add_friend(user._name);
  user.add_friend(this->_name);

  return *this;
}

bool User::operator<(const User &rhs) const { return _name < rhs._name; }
