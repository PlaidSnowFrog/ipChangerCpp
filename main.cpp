#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>
#include <chrono>
#include <thread>

using namespace std::this_thread;
using namespace std::chrono;

using std::cout;
using std::cin;
using std::string;
using std::to_string;

string getIP();
void changeToIP(const string IP);

int main(void) 
{
    srand(time(NULL));

    string IP;
    string interface;

    cout << "What internet interface are you using:     ";
    cin >> interface;

    while (true)
    {
        IP = getIP();
        changeToIP(IP);
        sleep_for(seconds(10));
    }

    return 0;
}

string getIP()
{
    unsigned int sectors[4];
    string command;
    string ip;
    int res;

    do 
    {
        for (int i = 0; i <= 3; i++)
        {
            sectors[i] = (rand() % 255) + 1;
        } 
        command = "ping -c 3" + to_string(sectors[0]) + to_string(sectors[1]) + to_string(sectors[2]) + to_string(sectors[3]) + "> /dev/null";
        
        res = system(command.c_str());
    } while (res != 1);

    for (int i : sectors)
    {
        ip.append(to_string(i));
    }

    return ip;
}

void changeToIP(const string IP, const string INTERFACE)
{
    string command = "sudo ifconfig" + INTERFACE + " " + IP + "netmask 255.255.255.0 up";
}