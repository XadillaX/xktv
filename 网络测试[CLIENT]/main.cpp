#include <zmq.hpp>
#include <string>
#include <iostream>
#include "cktvnetwork121.h"

int main()
{
    /** Prepare our context and socket */
    //zmq::context_t context(1);
    //zmq::socket_t socket(context, ZMQ_REQ);

    //std::cout << "Connecting to test server..." << std::endl;
    //socket.connect("tcp://localhost:5555");

    //while(true)
    //{
    //    std::cout << "Input some words: ";
    //    std::string tmp;
    //    std::getline(std::cin, tmp);

    //    zmq::message_t request(tmp.length() + 1);
    //    strcpy((char*)request.data(), tmp.c_str());
    //    std::cout << "Sending <" << tmp << "> ..." << std::endl;
    //    socket.send(request);

    //    /** Get reply */
    //    zmq::message_t reply;
    //    socket.recv(&reply);
    //    std::cout << "Received <" << (char*)reply.data() << ">" << std::endl;
    //}

    //CKTVNetwork121 net("tcp://*:5323", "tcp://localhost:5555");
    CKTVNetwork121 net("tcp://*:5323", "tcp://192.168.137.1:5555");

    while(true)
    {
        std::cout << "Input some words: ";
        std::string tmp;
        std::getline(std::cin, tmp);

        net.SendMsg(1, 1, tmp.c_str(), tmp.length() + 1);
    }
    
    return 0;
}
