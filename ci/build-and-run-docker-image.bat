docker rm driver-tester-uts-cont
docker build -t driver-tester-uts .
docker run --name driver-tester-uts-cont -it driver-tester-uts
