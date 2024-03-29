﻿using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using Moq;
using System.IO;
using System.Linq;
using System.Linq.Expressions;

namespace Runner.Tests {
    [TestClass]
    public class MessagesConnectionTest {
        private readonly Expression<Func<Stream, int>> ReadCall = 
            stream => stream.Read(It.IsAny<byte[]>(), It.IsAny<int>(), It.IsAny<int>());
        private readonly Expression<Action<Stream>> WriteCall =
            stream => stream.Write(It.IsAny<byte[]>(), It.IsAny<int>(), It.IsAny<int>());

        [TestMethod]
        public void Recv_SanityTest() {
            byte[] message = { 1, 2, 3, 101, 2, 11, 7, 13, 13, 15, 15 };
            byte[] messageHeader = getMessageHeader(message);
            bool isReadingHeader = true;
            const int blockSize = 2;

            var streamMock = new Mock<Stream>();
            streamMock.Setup(ReadCall)
                .Returns((byte[] buffer, int offset, int count) => {
                    byte[] currBuffer = isReadingHeader ? messageHeader : message;
                    Assert.AreEqual(buffer.Length, currBuffer.Length);
                    Assert.IsTrue(offset + count <= currBuffer.Length);

                    int actualCount = Math.Min(blockSize, count);
                    Array.Copy(currBuffer, offset, buffer, offset, actualCount);

                    if (isReadingHeader && actualCount + offset == currBuffer.Length) {
                        isReadingHeader = false;
                    }

                    return actualCount;
                });

            MessagesConnectionImpl connection = new MessagesConnectionImpl(streamMock.Object);
            var result = connection.recv();
            Assert.IsTrue(result.SequenceEqual(message));
        }

        [TestMethod]
        public void Recv_StreamEndedWhileReadingHeaderTest() {
            var streamMock = new Mock<Stream>();
            streamMock.SetupSequence(ReadCall)
                .Returns(MessagesConnectionImpl.HEADER_SIZE / 2)
                .Returns(0);

            MessagesConnectionImpl connection = new MessagesConnectionImpl(streamMock.Object);
            Assert.ThrowsException<StreamEndedPrematurely>(() => connection.recv());
        }

        [TestMethod]
        public void Recv_StreamEndedWhileReadingDataTest() {
            byte[] message = { 1, 100, 12, 51 };
            byte[] messageHeader = getMessageHeader(message);
            bool isReadingHeader = false;

            var streamMock = new Mock<Stream>();
            streamMock.Setup(ReadCall)
                .Returns((byte[] buffer, int offset, int count) => {
                    if (!isReadingHeader) {
                        return 0;
                    }
                    Array.Copy(messageHeader, offset, buffer, offset, count);
                    return messageHeader.Length; 
                });

            MessagesConnectionImpl connection = new MessagesConnectionImpl(streamMock.Object);
            Assert.ThrowsException<StreamEndedPrematurely>(() => connection.recv());
        }

        [TestMethod]
        public void Send_SanityTest() {
            byte[] message = { 0, 202, 79, 88, 2, 1, 102 };
            byte[] messageHeader = getMessageHeader(message);
            bool isReadingHeader = true;

            var streamMock = new Mock<Stream>();
            streamMock.Setup(WriteCall)
                .Callback((byte[] buffer, int offset, int count) => {
                    byte[] currBuffer = isReadingHeader ? messageHeader : message;
                    Assert.AreEqual(buffer.Length, currBuffer.Length);
                    Assert.AreEqual(count, currBuffer.Length);
                    Assert.AreEqual(offset, 0);
                    Assert.IsTrue(buffer.SequenceEqual(currBuffer));

                    if (isReadingHeader) {
                        isReadingHeader = false;
                    }
                });

            MessagesConnectionImpl connection = new MessagesConnectionImpl(streamMock.Object);
            connection.send(message);
            streamMock.Verify(WriteCall, Times.Exactly(2));
        }

        private byte[] getMessageHeader(byte[] message) {
            byte[] messageHeader = BitConverter.GetBytes(message.Length);
            Assert.AreEqual(messageHeader.Length, MessagesConnectionImpl.HEADER_SIZE);
            return messageHeader;
        }
    }
}
