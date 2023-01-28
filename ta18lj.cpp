//Tristan Arana Charlebois
//6680672

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

int main(){

	string name; // filename
    bool adj[20][20]; // adjacency matrix
    string labels[20]; // labels of courses
    int indegree[20]; // indegree of vertex
    int numnodes; // total number of nodes
	
	cout<<"Graph filename:";
	cin>>name;
	cout<<"Using " + name<<endl;

	ifstream file(name.c_str()); // ppen file

	for (int i = 0; i < 20; i++){ // initialize arrays

		for (int j = 0; j < 20; j++){

			adj[i][j] = 0;

		}

        indegree[i] = 0;

	}

	if (file){ // valid file

		cout<<"File loaded."<<endl;
		cout<<"Loaded graph."<<endl;

		numnodes = 0;
		file >> numnodes;

		char label;
        string course;

		cout<<endl;

		cout<<"Vertices:"<<endl;

		for (int i = 0; i < numnodes; i++){ // add vertices to array and print

            for (int j = 0; j < 8; j++){

			    file >> label;
                course += label;

            }

			labels[i] = course; // formatting
            course = "";

			cout<<"["<<i;
			cout<<":"<<labels[i];
			cout<< "]";

			if (i + 1 != numnodes){

			cout<<", ";

			}

		}

		cout<<"\n\n";


		int numedges = 0;
		file >> numedges;

		int to;
		int from;

		cout<<"Edges:"<<endl;

		for (int i = 0; i < numedges; i++){ // add edges to array
				
			file >> from;
			file >> to;
			adj[from][to] = true; 
			indegree[to] += 1;
			
		}

		for (int i = 0; i < numnodes; i++){ // print edges

			cout<<labels[i];
			cout<<" -> ";

			for (int j = 0; j < numnodes; j++){

				if (adj[i][j] == 1 && i != j){
				
					cout<<labels[j] + " ";

				}

			}

			cout<<endl;
		
		}

		cout<<endl;
	}

    queue<int> q; // holds vertices with indegree 0
    int num = 0; // count for cycle comparison
    stringstream sort; // final sort print

    for (int i = 0; i < numnodes; i++){ // add 0 indegree to queue

        if (indegree[i] == 0){

            q.push(i);

        }

    }

    while (q.empty() == false){ // no more 0 indegree

        int next = q.front(); // get next vertex 
        q.pop();
        sort << labels[next] << " ";

        for (int i = 0; i < numnodes; i++){ // check adjacent vertices, -1 to degree and add to queue if 0

            if (adj[next][i] == 1){

                if (--indegree[i] == 0){

                    q.push(i);

                }

            }

        }

        num++; // next vertex

    }

    if (num != numnodes){ // Cyclic

        cout<<"Cyclic dependencies; no topological sort possible."<<endl;
        return 0;

    }

    cout<<"Topological Sort found!"<<endl; 
    cout<<sort.str(); // print topological sort

}