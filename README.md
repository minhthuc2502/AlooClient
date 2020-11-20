# Client Aloo <!-- omit in toc -->
- [1. Introduction](#1-introduction)
- [2. What you need](#2-what-you-need)
- [3. build](#3-build)
  - [3.1. Build with QMake](#31-build-with-qmake)
  - [3.2. Build with GNU Make](#32-build-with-gnu-make)
- [4. Note](#4-note)
## 1. Introduction
This is a client which is built by Qt Framework run on Transport Layer with protocol TCP using for a chat application. This client can connect to server to participate chat room. We can chat in room and user's identification is saved by server.

we can connect to server by multiple ip address (localhost, IP local, IP on Internet).
## 2. What you need
- qt5
```bash
sudo apt-get install qt5-default
```

## 3. build
### 3.1. Build with QMake
If you want to build this application with qmake, open file ``*.pro`` in QtCreator and ``Run qmake`` and then ``Run``.

### 3.2. Build with GNU Make
If you use GNU Make:
```Bash
# From root path of project
make all 
# Run application
make run
```

## 4. Note
- If you build with GNU Make, please change ``imagePath`` in ``formLogin.cpp`` to ``/../../img/avatar-anonyme.jpg``.
- You can get sever application from this [repo](https://github.com/minhthuc2502/Aloo)