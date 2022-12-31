using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Runner {
    public class StreamEndedPrematurely : Exception {
        // intentionally left blank
    }

    public interface MessagesConnection {
        void send(byte[] data);
        byte[] recv();
    }

    public class MessagesConnectionImpl : MessagesConnection {
        public const int HEADER_SIZE = 4;

        private Stream stream;

        public MessagesConnectionImpl(Stream stream) {
            this.stream = stream;
        }

        public byte[] recv() {
            int size = BitConverter.ToInt32(recvAll(HEADER_SIZE), 0);
            return recvAll(size);
        }

        private byte[] recvAll(int size) {
            int bytesRecv = 0;
            byte[] buffer = new byte[size];

            while (bytesRecv < size) {
                int currBytesRecv = stream.Read(buffer, bytesRecv, size - bytesRecv);
                if (currBytesRecv == 0) {
                    throw new StreamEndedPrematurely();
                }
                bytesRecv += currBytesRecv;
            }

            return buffer;
        }

        public void send(byte[] data) {
            sendAll(BitConverter.GetBytes(data.Length));
            sendAll(data);
        }

        private void sendAll(byte[] buffer) {
            stream.Write(buffer, 0, buffer.Length);
        }
    }
}
