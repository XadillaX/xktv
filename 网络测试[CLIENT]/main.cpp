#include <zmq.hpp>
#include <string>
#include <iostream>

int main()
{
    /** Prepare our context and socket */
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);

    std::cout << "Connecting to test server..." << std::endl;
    socket.connect("tcp://localhost:5555");

    while(true)
    {
        std::cout << "Input some words: ";
        std::string tmp;
        std::getline(std::cin, tmp);

        zmq::message_t request(tmp.length() + 1);
        strcpy((char*)request.data(), tmp.c_str());
        std::cout << "Sending <" << tmp << "> ..." << std::endl;
        socket.send(request);

        /** Get reply */
        zmq::message_t reply;
        socket.recv(&reply);
        std::cout << "Received <" << (char*)reply.data() << ">" << std::endl;
    }
    
    return 0;
}
