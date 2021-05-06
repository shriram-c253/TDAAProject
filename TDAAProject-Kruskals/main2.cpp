#include<iostream>
#include<cstdlib>
#include<vector> 
#include<algorithm>
#include<utility>
#include<cmath>
#include<map>
#include <fstream>
#include"Kruskals.hpp"

int main(int argc,char** argv)
{
    int d = std::stoi(std::string(argv[1]));
    for(int num = 0;num<15;num++)
    {
        std::string graphnum = std::to_string(num);
        std::string outfilename = "./../wtd/graph"+graphnum+"/kruskal_out"+std::to_string(d)+".txt";
        std::ofstream fout;
        fout.open(outfilename);

        double expected_ratio = 0;
        bool fail = false;
        for(int k = 0;k<25;k++)
        {
            fout << std::endl;
            std::string filename = "./../wtd/graph"+graphnum+"/pert"+std::to_string(k)+"_graph"+graphnum;
            std::ifstream fin;

            fout << filename << std::endl;

            fin.open(filename);

            int n;
            fin >> n;
            
            std::map<int,std::map<int,double>> graph;
            double wt;

            for(int i=0;i<n;i++)
            {
                for(int j=0;j<n;j++)
                {
                    fin >> wt;

                    if(wt>0)
                    graph[i][j] = wt;
                }
            }

            fin.close();

            fout << "BOUNDED MST" << std::endl;
            std::pair<double,std::map<int,std::map<int,double>>> sp_tree_d = bdd_kruskals(graph,d);

            bool thisfail = false;
            if(sp_tree_d.first==-1)
            {
                fout << "FAILED!!!" << std::endl;
                fail = true;
                thisfail = true;
            }

            if(!thisfail)
            {
                fout << "BOUNDED SPANNING TREE CONNECTED" << std::endl;
                fout << sp_tree_d.first << std::endl;


                fout << "ACTUAL MST" << std::endl;
                std::pair<double,std::map<int,std::map<int,double>>> sp_tree = kruskals(graph);
                fout << sp_tree.first << std::endl;


                fout << "APPROX RATIO = " << sp_tree_d.first/sp_tree.first << std::endl;

                expected_ratio += sp_tree_d.first/sp_tree.first;
            }
            fout << std::endl;
            std::cout << k << ' ';
        }
        
        expected_ratio/=25;
        fout << std::endl << "EXPECTED RATIO = " << expected_ratio << std::endl;

        fout.close();
        std::cout << std::endl << "DONE" << num << std::endl;
    }
}