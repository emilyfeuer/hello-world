#include <iostream>

#include <iomanip>

#include <string>

using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::getline;
using std::find;
using std::to_string;
using std::istringstream;
using std::size_t;

int get_line_sum(string ca_line) {
  int sum = 0;
  for (int i = 0; i < static_cast < int > (ca_line.size()); i++) { // for each digit in line
    int line_int = (int)((ca_line[i]) - '0');
    sum += line_int;
  }
  return sum;
}

char get_next_state(string neighborhood, string rules) {
  string line = "";
  istringstream str(rules);
  char cell_state = '0';
  while (getline(str, line)) { // for each line
    size_t in_line = line.find(neighborhood); // see if specific neighborhood is found in line
    if (in_line != string::npos) {
      cell_state = (line[7]); // if neighborhood is found, set cell state equal to what is in rules
    }
  }
  return cell_state;
}

string set_neighborhood(int i,
  const string initial_row, string cell_row, string rules) {
  string neighborhood = "";
  if (i == 0) { // only for 1st neighborhood
    neighborhood.push_back(initial_row[cell_row.size() - 1]); // add 3 digits to neighborhood str
    neighborhood.append(initial_row, 0, 2);
  } else if (i == (static_cast < int > (cell_row.size() - 1))) { // only for last neighborhood
    neighborhood.append(initial_row, (i - 1), 2);
    neighborhood.push_back(initial_row[0]);
  } else { // all other neighborhoods
    neighborhood = initial_row.substr(i - 1, 3);
  }
  return neighborhood;
}

void update_line(string & cell_row, string & rules) {
  string initial_row = cell_row; // so initial values can be used after cell_row is modified
  for (int i = 0; i < static_cast < int > (cell_row.size()); i++) { // for each neighborhood
    bool is_in_rules = false;
    string neighborhood = set_neighborhood(i, initial_row, cell_row, rules);
    string line;
    istringstream ss(rules);
    while (getline(ss, line)) { // get each line of rules and try to find neighborhood in line
      size_t in_line = line.find(neighborhood);
      if (in_line != string::npos) { // if neighborhood was specified in rules
        cell_row[i] = line[7];
        is_in_rules = true;
      }
      if (is_in_rules == false) { // if neighborhood not specified in rules, set to 0
        cell_row[i] = '0';
      }
    }
  }
}

string run_cellular_automata(string rules, int iterations, string start_state) {
  string ca_string = "";
  for (int i = 1; i <= iterations; i++) { // for each iteration of the cellular automata
    int sum = get_line_sum(start_state);
    string sum_string = to_string(sum);
    ca_string.append(start_state); // append each state of CA and its sum to string
    ca_string.append(" sum = ");
    ca_string.append(sum_string);
    ca_string.append("\n");
    update_line(start_state, rules);
  }
  return ca_string; // return string with all iterations in it
}

int main() {
  string rules = "";
  int number_of_lines;
  string starting_line = "";
  while (true) { // loops through input of rules until loop is broken
    string rules_input = "";
    cin >> rules_input;
    size_t end_of_rules = rules_input.find(".");
    if (end_of_rules != string::npos) {
      break; // loop breaks if "." is input in a line
    } else {
      rules.append(rules_input); // each input is appended to a string of all the rules
      rules.append(" ");
    }
    if (rules_input.size() == 1) { // new line after rule ends
      rules.append("\n");
    }
  }
  cin >> number_of_lines;
  cin >> starting_line;
  cout << run_cellular_automata(rules, number_of_lines, starting_line);
  return 0;
}