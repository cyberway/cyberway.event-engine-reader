#include <string>
#include <iostream>
#include <signal.h>

#include <boost/asio.hpp>

static volatile bool done = false;
const std::string DEFAULT_SOCKET_NAME = "/tmp/queue";

boost::asio::io_service io_service;
boost::asio::local::stream_protocol::endpoint ep(DEFAULT_SOCKET_NAME);
boost::asio::local::stream_protocol::socket socket_stream(io_service);

static void sig_int_term_handler(int signum) {
    if (signum == SIGINT) {
        std::cerr << "Interrupt signal (" << signum << ") received." << std::endl;
    } else if (signum == SIGTERM) {
        std::cerr << "Termination signal (" << signum << ") received." << std::endl;
    }
    done = true;
}

int main(int argc, char** argv) {
    std::cerr << "Read socket messages" << std::endl;

    signal(SIGINT,  sig_int_term_handler);
    signal(SIGTERM, sig_int_term_handler);

    try {
        // connect to the UNIX socket
        socket_stream.connect(ep);
        if (socket_stream.native_non_blocking()) {
            socket_stream.native_non_blocking(false);
        }
    } catch (const boost::system::system_error &err) {
        std::cout << DEFAULT_SOCKET_NAME << std::endl;
        std::cerr << "Failed to connect to event-engine socket: " << err.what() << std::endl;
        return 1;
    }

    boost::asio::streambuf socket_buf;
    boost::system::error_code error;

    while (!done) {
        boost::asio::read_until(socket_stream, socket_buf, "\n", error);
        if (error) {
            std::cerr << "Receive failed: " << error.message() << std::endl;
            break;
        }

        std::string msg;
        std::istream data_stream(&socket_buf);
        std::getline(data_stream, msg);

        std::cout << msg << std::endl;
    }

    return 0;
}
