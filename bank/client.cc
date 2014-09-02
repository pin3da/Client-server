using namespace std;
#include <zmqpp/zmqpp.hpp>
#include <bits/stdc++.h>

class user{
public:
  static int _id; // 0 represents no current session
  int id;
  string account;
  user() : id (_id++) {}
  user(int _id, string _account = "") : id(_id) , account(_account) {}

  bool operator < (const user & other) const {
    return id < other.id;
  }
};

set<user> users;

int user::_id = 0;

int go_out(string message, int code = 1) {
  cout << message << endl;
  cin.get(); // to clean buffer
  cout << "Press enter to continue." << endl;
  //cout << "Where is the any key ? : http://tinyurl.com/q8st375" << endl;
  cin.get();

  return code;
}

bool process(zmqpp::socket &socket, user &usr) {
  system("clear");
  string cmd;

  if (usr.id == 0) {
    cout << "Welcome to cool bank S.A !" << endl << "Please enter an option." << endl;
    cout << "1. Register." << endl;
    cout << "2. Log in." << endl;
    cout << "3. Quit." << endl;
    cin >> cmd;
    if (cmd == "1") {
      system("clear");
      user new_user;
      users.insert(new_user);
      usr = new_user;
      zmqpp::message message;
      message << "register" << usr.id;
      socket.send(message);
      string response;
      socket.receive(response);
      //ss << "The new user has been created, your id is : " << new_user.id;
      return go_out(response);
    } else if (cmd == "2") {
      cout << "Please enter your id : " << endl;
      int cur_id;
      cin >> cur_id;
      if (users.count(user(cur_id)) == 0) {
        return go_out("The user is not in the data base");
      } else {
        return go_out("Welcome !!");
      }

    } else if (cmd == "3") {
      return go_out("Bye !!", 0);
    } else {
      return go_out("Invalid Option");
    }

  } else {
    cout << "Welcome " << usr.id << " !! "<< endl;
    cout << "1. Enter 'check' to view the amount of funds in account" << endl;
    cout << "2. Enter 'add' and an amount to add funds to your account" << endl;
    cout << "3. Enter 'withdraw' and an amount to remove funds from your account" << endl;
    cout << "4. Enter 'transfer', an amount, and another account to transfer funds" << endl;
    cout << "5. Enter 'quit' to finish" << endl;
    cin >> cmd;
    if (cmd == "quit") {
      return go_out("Bye !!", 0);
    } else {
      zmqpp::message message;
      message << cmd << usr.id;
      if (cmd == "check") {
        //message << user.id;
      } else if (cmd == "add" or cmd == "withdraw") {
        cout << "Enter the desired amount" << endl;
        int amount;
        cin >> amount;
        message << amount;
      } else if (cmd == "transfer") {
        int amount, second_id;
        cin >> amount >> second_id;
        message << amount << second_id;
      } else {
        return go_out("Invalid option");
      }
      cout << "Sending message" << endl;
      socket.send(message);
      string answer;
      socket.receive(answer); // Should return an string
      return go_out("Answer received: " + answer + "\n\n");
    }
  }
  return go_out("");
}

int main(int argc, char *argv[]) {
  const string endpoint = "tcp://localhost:4242";
  zmqpp::context context;
  zmqpp::socket socket (context, zmqpp::socket_type::request);
  cout << "Connecting with the bank server : " << endpoint << "..." << endl;
  socket.connect(endpoint);

  user current_user;

  while (process(socket, current_user)) {
    //dispatching
  }

  cout << "Finished." << endl;
  return 0;
}
