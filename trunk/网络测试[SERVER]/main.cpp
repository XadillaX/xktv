#include <zmq.hpp>
#include <string>
#include <iostream>
#include <windows.h>

int main()
{
    /** Prepare our context and socket */
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);
    socket.bind("tcp://*:5555");

    while(true)
    {
        zmq::message_t request;

        /** Wait for next request from client */
        socket.recv(&request);
        std::cout << "[" << "]Received " << (char*)request.data() << std::endl;

        /** Pause */
        Sleep(1);

        /** Send reply */
        zmq::message_t reply(6);
        strcpy((char*)reply.data(), "World");
        socket.send(reply);
    }

    return 0;
}
