#include <gmock/gmock.h>

#include "Defs.h"

#include "TcpSocket.h"

struct FakeExceptionForMockPosixSocket : std::exception {
    // left blank intentionally
};

class FakePosixSocketTraits {
public:
    using ExceptionType = FakeExceptionForMockPosixSocket;
    int close(SOCKET) { return 0; }
};

class MockPosixTcpSocketAllTraits {
public:
    MOCK_METHOD(SOCKET, create, (int, int, int));
    MOCK_METHOD(int, bind, (SOCKET, const sockaddr_in*, int));
    MOCK_METHOD(int, listen, (SOCKET, int));
    MOCK_METHOD(SOCKET, accept, (SOCKET, sockaddr*, int*));

    MOCK_METHOD(int, recv, (SOCKET, char*, int, int));
    MOCK_METHOD(int, send, (SOCKET, const char*, int, int));
};

class MoveableMockPosixTcpSocketAllTraits {
public:
    using ExceptionType = FakePosixSocketTraits::ExceptionType;

    MoveableMockPosixTcpSocketAllTraits()
        : m_mock(std::make_unique<testing::StrictMock<MockPosixTcpSocketAllTraits>>()) {}

    SOCKET create(int af, int type, int protocol) {
        return m_mock->create(af,type, protocol);
    }

    int close(SOCKET socket) {
        return m_fake.close(socket);
    }

    int bind(SOCKET socket, const sockaddr_in* addr, int namelen) {
        return m_mock->bind(socket, addr, namelen);
    }

    int listen(SOCKET socket, int backlog) {
        return m_mock->listen(socket, backlog);
    }

    SOCKET accept(SOCKET socket, sockaddr* addr, int* namelen) {
        return m_mock->accept(socket, addr, namelen);
    }

    int recv(SOCKET socket, char* buf, int len, int flags) {
        return m_mock->recv(socket, buf, len, flags);
    }

    int send(SOCKET socket, const char* buf, int len, int flags) {
        return m_mock->send(socket, buf, len, flags);
    }

    testing::StrictMock<MockPosixTcpSocketAllTraits>& getMock() {
        return *m_mock;
    }

private:
    std::unique_ptr<testing::StrictMock<MockPosixTcpSocketAllTraits>> m_mock;
    FakePosixSocketTraits m_fake;
};
