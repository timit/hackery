//
//  main.cpp
//  PairDown
//
//  Created by tim on 12/21/15.
//  Copyright © 2015 tim. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <unistd.h>

int main(int argc, char * argv[]) {
    std::cout << "started !!!" << std::endl;
    //setup
    std::string ipath = "input.csv";
    std::string opath = "output.csv";
    int opt = 0;
    while((opt = getopt(argc, argv, ":i:o")) !=-1) {
        switch(opt) {
            case 'i':
                if(optarg) {
                    ipath = optarg;
                }
                break;
            case 'o':
                if(optarg) {
                    opath = optarg;
                }
                break;
        }
    }
    std::ifstream ifile(ipath);
    std::ofstream ofile;
    ofile.open(opath);
    //process
    std::cout << "input file: " << ipath << std::endl;
    std::cout << "output file: " << opath << std::endl;
    std::string row;
    int rowcount = 1;
    int writecount = 0;
    while(std::getline(ifile,row)) {
        //count columns for rudimentary dataset validation
        std::stringstream lineStream(row);
        std::string col;
        int colcount = 0;
        while(std::getline(lineStream,col,',')) {
            colcount++;
        }
        std::cout << "--- processing row = " << rowcount << " (with " << colcount << " columns)";
        //write every 1000th row
        if(rowcount % 1000 == 0) {
            writecount++;
            ofile << row << std::endl;
            std::cout << " written to file";
        }
        std::cout << std::endl;
        rowcount++;
    }
    std::cout << "finished !!! (processed " << rowcount << " rows, wrote " << writecount << ")" << std::endl;
    //teardown
    ifile.close();
    ofile.close();
    return 0;
}
