#include<vector>
#include<iostream>
#include<fstream>
using namespace std;

string lastword(string filename)
{
    ifstream file;
    file.open(filename);

    vector<string> str;
    while (!file.eof())
    {
        string temp;
        getline(file, temp);
        // cout << temp << endl;
        str.push_back(temp);
    }
    file.close(); 

    int lastwordpos = str[str.size() - 2].find_last_of(" ");
    string lastword = str[str.size() - 2].substr(lastwordpos, (str.size() - lastwordpos));
    return lastword;
    cin.get();
}

int main()
{
    cout << "Degree \t Kruskals \t Prims \t\t Ratio" << endl;
    string fname,str1,str2;
    for(int graphnum = 0;graphnum<15;graphnum++)
    {
        cout <<  "Graph Number: " << graphnum << endl;
        for(int i=3;i<=7;i++)
        {
            cout << i << '\t' << ' ';
            fname = "wtd/graph"+to_string(graphnum)+"/kruskal_out"+to_string(i)+".txt";
            str1 = lastword(fname);
            cout << lastword(fname) << '\t' << ' ';
            fname = "wtd/graph"+to_string(graphnum)+"/prim_out"+to_string(i)+".txt";
            str2 = lastword(fname);
            cout << lastword(fname) << '\t' << ' ';
            cout << stod(str2)/stod(str1);
            cout << endl;
        }
        
    }
}