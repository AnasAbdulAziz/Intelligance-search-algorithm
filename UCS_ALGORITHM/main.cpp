#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include<stdlib.h>
using namespace std;

using std::vector;
using std::priority_queue;
using std::cout;
using std::endl;


//Constructing the node


struct Node
{
  char name_;
  vector<Node*> connect_;
  vector<int> cost_;

  Node(char name)
  :name_(name), connect_(), cost_()
  {}

  void connectsTo(Node* destination, int cost)
  {
    connect_.push_back(destination);
    cost_.push_back(cost);
  }
};


// Constructing the path


struct Path
{
  int cost_;
  vector<Node*> path_;

    //default constructor
  Path()
  :cost_(0), path_()
  {}

  Path(const Path& rhs)
  :cost_(rhs.cost_), path_()
  {
    vector<Node*>::const_iterator i;

    for (i = rhs.path_.begin(); i != rhs.path_.end(); ++i)
    {
      path_.push_back(*i);
    }
  }

  bool operator>(const Path& rhs) const
  {
    return cost_ > rhs.cost_;
  }

  void append(Node* node)
  {
    path_.push_back(node);
  }
};

void UCS(Node* start, Node* goal);
void displayPath(const Path& path);
void displayFrontier(priority_queue<Path, vector<Path>,
                     std::greater<Path>> frontier);

int main()
{
    //declaring the file
    ifstream infile;
    char x;
    int z,n,b;
    char c1,c2,a;

    infile.open("input.txt");
    infile>>z>>x;
    if(x=='V'){
      n=z;
      cout<<"The number of nodes is: "<<n<<endl;
    }else{
    cout<<"Error opening the file\n";
    }
    //storing the nodes
    Node *nodes[n];
    int j=0;
    while(infile>>a>>c1>>b>>c2){
        cout<<a<<c1<<b<<c2;
       if(c2=='-'){
            nodes[j] = new Node(a);
            cout<<" "<<endl;
            j++;
       }
    }
    cout<<"The goal state is: "<<nodes[4]->name_<<endl;

    //establishing the connections

    nodes[0]->connectsTo(nodes[1],1);
    nodes[0]->connectsTo(nodes[2],4);

    nodes[1]->connectsTo(nodes[4],7);
    nodes[1]->connectsTo(nodes[3],6);
    nodes[1]->connectsTo(nodes[2],3);

    nodes[2]->connectsTo(nodes[3],8);

    nodes[3]->connectsTo(nodes[4],10);

     UCS(nodes[0],nodes[4]);

    return 0;
}

//the uniformed cost search algorithm implementation
void UCS(Node* start, Node* goal)
{
  int iter_number = 0;
  Node* current_node;
  priority_queue<Path, vector<Path>, std::greater<Path>> frontier;

  Path root;
  root.append(start);
  root.cost_ = 0;
  frontier.push(root);

  cout << "Initialisation: ";
  displayFrontier(frontier);
  cout << endl;

  vector<Node*>::iterator i;

  while (!frontier.empty())
  {
    iter_number++;

    Path current_path;
    current_node = frontier.top().path_.back();
    current_path = frontier.top();

    cout << "Iteration " << iter_number << ": ";
    displayFrontier(frontier);
    cout << endl;

    frontier.pop();

    if (current_node == goal)
    {
      cout << endl << "Solution: ";
      displayPath(current_path);
      cout << " costs " << current_path.cost_ << endl;
      return;
    }
    else
    {
      vector<int>::iterator cost_iter;
      cost_iter = current_node->cost_.begin();

      for (i = current_node->connect_.begin();
           i != current_node->connect_.end(); ++i)
      {
        Path temp_path(current_path);
        temp_path.append(*i);
        temp_path.cost_ += *cost_iter;
        cost_iter++;
        frontier.push(temp_path);
      }
    }
  }

  cout << "Solution does not exist." << endl;
}
void displayPath(const Path& path)
{
  vector<Node*>::const_iterator i;

  for (i = path.path_.begin(); i != path.path_.end(); ++i)
      cout << (*i)->name_<<" ";
}

void displayFrontier(priority_queue<Path, vector<Path>,
                     std::greater<Path>> frontier)
{
  cout << "[ {";

  while (frontier.size() > 0)
  {
    displayPath(frontier.top());
    frontier.pop();


    if (frontier.size() > 0)
      cout << "}, {";
    else
      cout << "} ]";
  }
}
