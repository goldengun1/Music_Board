FROM    ubuntu:latest
ENV     DEBIAN_FRONTEND=noninteractive
RUN     apt update -y && apt install -y git g++ cmake qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools qtmultimedia5-dev

RUN     mkdir /usr/src/muzickatabla

WORKDIR /usr/src/muzickatabla
RUN     git clone https://gitlab.com/matf-bg-ac-rs/course-rs/projects-2022-2023/05-muzicka-tabla.git . && mkdir build

WORKDIR /usr/src/muzickatabla/build
RUN     cmake ..

RUN     make

RUN     ./05-muzicka-tabla
