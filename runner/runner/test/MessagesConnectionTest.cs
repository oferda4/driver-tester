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
            byte[] arbitraryMessage = { 1, 2, 3, 101, 2, 11, 7, 13, 13, 15, 15 };
            byte[] arbitraryMessageHeader = BitConverter.GetBytes(arbitraryMessage.Length);
            Assert.AreEqual(arbitraryMessageHeader.Length, MessageConnectionImpl.HEADER_SIZE);
            
            bool isReadingHeader = true;
            const int blockSize = 2;

            var streamMock = new Mock<Stream>();
            streamMock.Setup(stream => stream.Read(It.IsAny<byte[]>(), It.IsAny<int>(), It.IsAny<int>()))
                .Returns((byte[] buffer, int offset, int count) => {
                    byte[] currBuffer = isReadingHeader ? arbitraryMessageHeader : arbitraryMessage;
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
            Assert.IsTrue(result.SequenceEqual(arbitraryMessage));
        }
    }
}
