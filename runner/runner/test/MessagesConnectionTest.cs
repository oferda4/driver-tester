using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using Moq;
using System.IO;
using System.Linq;

namespace Runner.Tests {
    [TestClass]
    public class MessagesConnectionTest {
        [TestMethod]
        public void recvTest() {
            byte[] message = { 1, 2, 3, 101, 2, 11, 7, 13, 13, 15, 15 };
            byte[] messageHeader = getMessageHeader(message);
            bool isReadingHeader = true;
            const int blockSize = 2;

            var streamMock = new Mock<Stream>();
            streamMock.Setup(stream => stream.Read(It.IsAny<byte[]>(), It.IsAny<int>(), It.IsAny<int>()))
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

            MessageConnectionImpl connection = new MessageConnectionImpl(streamMock.Object);
            var result = connection.recv();
            Assert.IsTrue(result.SequenceEqual(message));
        }

        [TestMethod]
        public void sendTest() {
            byte[] message = { 0, 202, 79, 88, 2, 1, 102 };
            byte[] messageHeader = getMessageHeader(message);
            bool isReadingHeader = true;

            var streamMock = new Mock<Stream>();
            streamMock.Setup(stream => stream.Write(It.IsAny<byte[]>(), It.IsAny<int>(), It.IsAny<int>()))
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

            MessageConnectionImpl connection = new MessageConnectionImpl(streamMock.Object);
            connection.send(message);
            streamMock.Verify(stream => stream.Write(It.IsAny<byte[]>(), It.IsAny<int>(), It.IsAny<int>()), Times.Exactly(2));
        }

        private byte[] getMessageHeader(byte[] message) {
            byte[] messageHeader = BitConverter.GetBytes(message.Length);
            Assert.AreEqual(messageHeader.Length, MessageConnectionImpl.HEADER_SIZE);
            return messageHeader;
        }
    }
}
