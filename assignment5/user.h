/*
 * CS106L Assignment 5: TreeBook
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */

#include <iostream>
#include <string>

class User {
  friend std::ostream &operator<<(std::ostream &os, const User &user);

public:
  User(const std::string &name);
  void add_friend(const std::string &name);
  std::string get_name() const;
  size_t size() const;
  void set_friend(size_t index, const std::string &name);

  /**
   * STUDENT TODO:
   * Your custom operators and special member functions will go here!
   */
  User(const User &user);
  User &operator=(const User &user);
  ~User();
  void swap(User &user) noexcept {
    using std::swap;
    swap(_name, user._name);
    swap(_friends, user._friends);
    swap(_size, user._size);
    swap(_capacity, user._capacity);
  }

  User(User &&user) = delete;
  User &operator=(User &&user) = delete;

  User &operator+=(User &user);
  bool operator<(const User &rhs) const;

private:
  std::string _name;
  std::string *_friends;
  size_t _size;
  size_t _capacity;
};
