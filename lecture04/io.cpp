#include <string>
#include <iostream>
#include <fstream>

int main(){
    std::string s = "This is a string\n";
    s = s + "Second line\n";
    std::cout << s;
    int x;
    std::cin >> x;
    std::cout << x << std::endl; // same as << "\n" << std::flush;
    std::ofstream outfile("out.txt"); // outfile.open("out.txt");
    outfile << s << std::flush;
    std::ifstream infile("out.txt");
    s =  "";
    infile >> s;
    std::cout << s << std::endl; //Reads only one word. Skips whitespace like %s in scanf
    std::getline(infile, s);
    std::cout << s << "\n";
    return 0;
}